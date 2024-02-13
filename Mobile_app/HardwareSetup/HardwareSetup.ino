#define BLYNK_TEMPLATE_ID "TMPL3gxKbEIS5" // Blynk template and authentication information
#define BLYNK_TEMPLATE_NAME "HomeSecurity"
#define BLYNK_AUTH_TOKEN "RDs-5TaFIsxVHn6VEC483jSQKw_JjJ0q"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <Keypad.h>
#include <BlynkSimpleEsp8266.h>

#include <WiFiClient.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Annmon"; // WiFi network name
char pass[] = "childsafe"; // WiFi password

#include <String.h>

#define ROW0 D0
#define ROW1 D1
#define ROW3 D2
#define COL0 D3
#define COL1 D4
#define COL2 D5
#define SolenoidLock D6
#define GREEN D7
#define RED D8
const byte ROWS = 3; // Three rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},

  {'*','0','#'}
};
byte rowPins[ROWS] = {ROW0, ROW1, ROW3}; // Connect keypad ROW0, ROW1 and ROW3 to these pins respectively.
byte colPins[COLS] = {COL0, COL1, COL2}; // Connect keypad COL0, COL1 and COL2 to these pins respectively.
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Initialize the keypad
String v_passcode="";
BlynkTimer timer; // timer object created, BlynkTimer is a class.

const char* ap_ssid = "Annmon_ESP_Hotspot";
const char* ap_password = "childsafe";
WiFiServer server(80);

void setup() {
Blynk.begin(auth, ssid, pass); // Start Blynk using WiFi credentials
Serial.begin(9600);
pinMode(SolenoidLock, OUTPUT); // Pin connected to the relay controlling the solenoid lock
digitalWrite(SolenoidLock, LOW); // Start with the solenoid lock in locked state
pinMode(GREEN, OUTPUT); // Green LED
pinMode(RED, OUTPUT); // Red LED
timer.setInterval(1L, emailsetup); // Set timer to call emailsetup function every 1 second


  WiFi.softAP(ap_ssid, ap_password); 
  server.begin();
  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());  //  

  pinMode(SolenoidLock, OUTPUT);

  digitalWrite(SolenoidLock, LOW);
}
// emailsetup being scheduled to be called repeatedly by the BlynkTimer object.
// emailsetup() is scheduled to run every 1 millisecond, almost every time loop() runs, timer.run() will execute emailsetup().
void emailsetup() {
char key = keypad.getKey(); // Read the key that is pressed
    if (key != NO_KEY) { // If a key is pressed, add it to the passcode string, NO_KEY is predefined in they keypad library
    v_passcode = v_passcode + key; // Append the pressed key to the passcode

    if (key == '*') { // Check if '*' is pressed to reset passcode entry
      Serial.println("Enter Password");
      v_passcode = ""; // Reset the passcode
    }

    if (key == '#') {  // Check if '#' is pressed to validate the passcode
      Serial.println("Validate the Password");
      if (v_passcode == "1234#") { // Password is correct
       Blynk.logEvent("password_entry", "Your child reached home"); // correct password entry
       Serial.println("Access Granted");
        digitalWrite(SolenoidLock, HIGH); // Unlock the solenoid lock
        digitalWrite(GREEN, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
        digitalWrite(GREEN, LOW);  // Turn off green LED

      } else if (v_passcode == "123#") { 
      /* Pseudo-password [From outside of the device it will show correct, 
      but it signals SOS to parents]*/
       Blynk.logEvent("password_entry", "Your Child is in danger"); // Child entered SOS code
        digitalWrite(SolenoidLock, HIGH); // Unlock the solenoid lock
        digitalWrite(GREEN, HIGH); // Turn on green LED
        delay(3000);  
        digitalWrite(GREEN, LOW);  // Turn on green LED
      } else if (v_passcode == "4321#") { // To Unlock the door
        Blynk.logEvent("password_entry", "Door is Locked now");
        Serial.println("\nDoor is Locked");
        digitalWrite(SolenoidLock, LOW); // Lock the solenoid lock
        digitalWrite(GREEN, HIGH); // Turn on green LED
        delay(100); // Wait for 1/10 second
        digitalWrite(GREEN, LOW);  // Turn off green LED
        delay(100); // Wait for 1/10 second
        digitalWrite(RED, HIGH); // Red LED On
        delay(100); // Wait for 1/10 second
        digitalWrite(RED, LOW); // Red LED Off 
      } else { // Password is wrong
      Blynk.logEvent("password_entry", "Wrong Passcode Entered"); // Wrong password entry
        Serial.println("Access Denied");
          digitalWrite(RED,HIGH); // RED led
          delay(2000);
          digitalWrite(RED,LOW); // RED led
      }
      Serial.println("The entered password is " + v_passcode);
      v_passcode = ""; // Reset the passcode string
    }
  }
  
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


          }

          if (command.equals("green")) {
            digitalWrite(SolenoidLock, LOW);


          }


          if (command.equals("blue")) {
            digitalWrite(SolenoidLock, LOW);
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