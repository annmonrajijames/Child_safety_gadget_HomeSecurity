#define BLYNK_TEMPLATE_ID "TMPL3smJ6LQi_"
#define BLYNK_TEMPLATE_NAME "ChildSafetyHomeSecurity"
#define BLYNK_AUTH_TOKEN "2VPCT_E0rvrpHUH5fFuuG2925vhQU7jg"
#define BLYNK_PRINT Serial

#define SolenoidLock D5
#define Buzzer D6
#define GREEN D7
#define RED D8
//#define flameSensor D0

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Annmon"; // WiFi network name
char pass[] = "childsafe"; // WiFi password

#include <String.h>

#define I2CADDR         0x20       // matrix keypad address
#include <ESP8266WiFi.h>
#include <Keypad.h>               //library for matrix keypad
#include <Wire.h>                 //library for I2C communication
#include <Keypad_I2C.h>           //library for matrix keypad I2C communication
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte ROWS = 4;              // 4 rows in matrix keypad
const byte COLS = 4;              // 4 columns in matrix keypad

char hexaKeys[ROWS][COLS] = { //define a character for every button
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {0, 1, 2, 3}; // row pins connected to I2C module 
byte colPins[COLS] = {4, 5, 6, 7}; // column pins connected to I2C module 

// object for matrix keypad
Keypad_I2C customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 
String passwords[3] = {"1234", "5678", "5454"}; // Default passwords for Secret 1, 2, and 3

String enteredPassword;
bool verifyMode = false; // Indicates if the system is in verification mode
int changePasswordStep = 0; // Tracks the step in the change password sequence
String randomPassword = "";
BlynkTimer timer; // timer object created, BlynkTimer is a class.

const char* ap_ssid = "Annmon_ESP_Hotspot";
const char* ap_password = "childsafe";
WiFiServer server(80);

void setup(){
  Blynk.begin(auth, ssid, pass); // Start Blynk using WiFi credentials
  Serial.begin(9600);                     // initialize serial communication
  customKeypad.begin( );                  // initialize matrix keypad
  pinMode(SolenoidLock, OUTPUT); // Pin connected to the relay controlling the solenoid lock
  digitalWrite(SolenoidLock, LOW); // Start with the solenoid lock in locked state
  pinMode(Buzzer, OUTPUT); // Buzzer
  pinMode(GREEN, OUTPUT); // Green LED
  pinMode(RED, OUTPUT); // Red LED
  randomSeed(analogRead(0)); // Initialize random number generator
  timer.setInterval(1L, emailsetup); // Set timer to call emailsetup function every 1 second
  WiFi.softAP(ap_ssid, ap_password); 
  server.begin();
  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  //pinMode(flameSensor, INPUT); // Set the flame sensor pin as an input
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.display();
}
/*bool isFlameDetected() {
  int flameDetected = digitalRead(flameSensor); // Read the flame sensor value
  return flameDetected == LOW; // Return true if flame is detected
}*/  
void emailsetup() {
  char key = customKeypad.getKey();  // save character pressed 

  if (key != NO_KEY) {
    if (key == 'A') {
      enteredPassword = "";
      Serial.println("\nEnter password:");
      display.clearDisplay();
      char text[] = "Enter password";
      OledDisplay(text);
    } else if (key == '0' && !verifyMode && changePasswordStep == 0) {
      randomPassword = String(random(1000, 10000));
      String SecretMessage= "OTP (One time password) is " + String(randomPassword);
      Blynk.logEvent("childhomeemail", SecretMessage);
      Serial.print("\nEnter the OTP (One Time Password): ");
      verifyMode = true;
      enteredPassword = "";
    } else if (verifyMode) {
      verifyRandomPassword(key);
    } else if (changePasswordStep > 0) {
      setNewPasswords(key);
    } else {
      checkPasswords(key);
    }
  }
  /*if (isFlameDetected()) {
    Blynk.logEvent("childhomeemail", "Door is on Fire");
    Serial.println("Flame detected!");    // Flame is detected
    display.clearDisplay();
    char text[] = "Door is on Fire";
    OledDisplay(text);
  }*/
}

void verifyRandomPassword(char key) {
  if (key != 'D') {
    enteredPassword += key;
  } else {
    if (enteredPassword == randomPassword) {
      Serial.println("\nNumber Verified. Proceed to set new passwords.");
      verifyMode = false;
      changePasswordStep = 1; // Proceed to change passwords for Secret 1
    } else {
      Serial.println("\nVerification Failed. Try again.");
      verifyMode = false;
    }
    enteredPassword = "";
  }
}

void setNewPasswords(char key) {
  if (key != 'D') {
    enteredPassword += key;
  } else {
    passwords[changePasswordStep - 1] = enteredPassword;
    Serial.print("\nNew password for Secret ");
    Serial.print(changePasswordStep);
    Serial.println(" set.");
    enteredPassword = "";
    changePasswordStep++;
    if (changePasswordStep > 3) {
      changePasswordStep = 0; // Reset after setting all new passwords
      Serial.println("\nAll new passwords are set.");
    }
  }
}

void checkPasswords(char key) {
  if (key == 'D') {
    bool passwordMatched = false;

      if (enteredPassword == passwords[0]) {
        Blynk.logEvent("childhomeemail", "Your child reached home"); // correct password entry
        Serial.print("\nPassword Correct");
        passwordMatched = true;
        digitalWrite(SolenoidLock, HIGH); // Unlock the solenoid lock
        digitalWrite(Buzzer, HIGH); // Turn on buzzer
        digitalWrite(GREEN, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
        digitalWrite(Buzzer, LOW);  // Turn off buzzer
        digitalWrite(GREEN, LOW);  // Turn off green LED
        display.clearDisplay();
        char text[] = "Correct password";
        OledDisplay(text);
      }
      if (enteredPassword == passwords[1]) {
        Blynk.logEvent("childhomeemail", "Your Child is in danger"); // Child entered SOS code
        Serial.print("\nPassword Correct");
        passwordMatched = true;
        digitalWrite(SolenoidLock, HIGH); // Unlock the solenoid lock
        digitalWrite(Buzzer, HIGH); // Output from device is same as correct password 
        digitalWrite(GREEN, HIGH); 
        delay(3000); 
        digitalWrite(Buzzer, LOW);  
        digitalWrite(GREEN, LOW);
        display.clearDisplay();
        char text[] = "Correct password";
        OledDisplay(text);  
      }
      if (enteredPassword == passwords[2]) {
        Blynk.logEvent("childhomeemail", "Door Locked");      
        Serial.print("\nDoor Locked");
        passwordMatched = true;
        digitalWrite(SolenoidLock, LOW); // Lock the solenoid lock
        digitalWrite(GREEN, HIGH); // Turn on green LED
        delay(100); // Wait for 1/10 second
        digitalWrite(GREEN, LOW);  // Turn off green LED
        delay(100); // Wait for 1/10 second
        digitalWrite(RED, HIGH); // Red LED On
        delay(100); // Wait for 1/10 second
        digitalWrite(RED, LOW); // Red LED Off 
        display.clearDisplay();
        char text[] = "Door Locked";
        OledDisplay(text);
      }

    if (!passwordMatched) {
      Blynk.logEvent("childhomeemail", "Someone entered wrong password"); 
      Serial.println("\nPassword Incorrect");
    }
    enteredPassword = ""; // Reset entered password
  } else {
    enteredPassword += key;
  }
}
void OledDisplay(char text[]) {
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Child safety-Home security");
  display.println("---------------------");
  display.setCursor(0,27);
  display.setTextSize(1);
  display.print(text);
  display.display();
}
void loop() {
  Blynk.run(); // Run Blynk process
  timer.run(); // checks if it's time to call any function scheduled by the timer.
   String all_command = "";

  WiFiClient client = server.available();

  if (client) {
    String request = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (c == '\r') {
          // End of line reached, check if next character is newline

          Serial.println(request);  // full HTTP command line including GET  and HTTP 1

          // Extract command from request string
          int start = request.indexOf("GET /") + 5;
          int end = request.indexOf("HTTP/");
          String command = request.substring(start, end);

          //Purify the command
          command.replace("\n", "");
          command.replace("\r", "");
          command.replace(" ", ""); // removes all space characters
          command.replace("\t", ""); // removes all tab characters
          command.trim();

          Serial.println(command);

          all_command =  command + " is on";  // green is on 


          if (command.equals("red")) {
            digitalWrite(SolenoidLock, HIGH);
            display.clearDisplay();
            char text[] = "Door unlocked by App";
            OledDisplay(text);
            delay(5000); // To prevent OLED ON for infinite time 
            display.clearDisplay();
            display.display();
          }

          if (command.equals("green")) {
            digitalWrite(SolenoidLock, LOW);
            display.clearDisplay();
            char text[] = "Door locked by App";
            OledDisplay(text);
            delay(5000); // To prevent OLED ON for infinite time 
            display.clearDisplay();
            display.display();
          }

          if (client.peek() == '\n') {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            String commandWithTags = "<html><body>" + all_command + "</body></html>";
            client.println(commandWithTags);
            break;

          }
        }
      }
    }
  } 
}