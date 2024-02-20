#define BLYNK_TEMPLATE_ID "TMPL3gxKbEIS5" // Blynk template and authentication information
#define BLYNK_TEMPLATE_NAME "HomeSecurity"
#define BLYNK_AUTH_TOKEN "RDs-5TaFIsxVHn6VEC483jSQKw_JjJ0q"
#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Annmon"; // WiFi network name
char pass[] = "childsafe"; // WiFi password

#define I2CADDR         0x20       // matrix keypad address
#include <ESP8266WiFi.h>
#include <Keypad.h>               //library for matrix keypad
#include <Wire.h>                 //library for I2C communication
#include <Keypad_I2C.h>           //library for matrix keypad I2C communication
#include <BlynkSimpleEsp8266.h>

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
String v_passcode="";
BlynkTimer timer; // timer object created, BlynkTimer is a class.

void setup(){
  Blynk.begin(auth, ssid, pass); // Start Blynk using WiFi credentials
  Serial.begin(9600);                     // initialize serial communication
  customKeypad.begin( );                  // initialize matrix keypad
  pinMode(D6, OUTPUT); // Buzzer
  pinMode(D7, OUTPUT); // Green LED
  pinMode(D8, OUTPUT); // Red LED
  timer.setInterval(1L, emailsetup); // Set timer to call emailsetup function every 1 second
}
  
void emailsetup() {
  char key = customKeypad.getKey();  // save character pressed 
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
        digitalWrite(D6, HIGH); // Turn on buzzer
        digitalWrite(D7, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
        digitalWrite(D6, LOW);  // Turn off buzzer
        digitalWrite(D7, LOW);  // Turn off green LED

      } else if (v_passcode == "123#") { 
      /* Pseudo-password [From outside of the device it will show correct, 
      but it signals SOS to parents]*/
        Blynk.logEvent("password_entry", "Your Child is in danger"); // Child entered SOS code
        digitalWrite(D6, HIGH); // Output from device is same as correct password 
        digitalWrite(D7, HIGH); 
        delay(3000); 
        digitalWrite(D6, LOW);  
        digitalWrite(D7, LOW);  
      } else { // Password is wrong
        Blynk.logEvent("password_entry", "Wrong Passcode Entered"); // Wrong password entry
        Serial.println("Access Denied");
         for (int i = 0; i < 3; i++) {
          digitalWrite(D6, HIGH);
          delay(50);
          digitalWrite(D6, LOW);
          delay(50);
        }
          digitalWrite(D8,HIGH);
          delay(2000);
          digitalWrite(D8,LOW);
      }
      Serial.println("The entered password is " + v_passcode);
    }
  }
}
void loop() {
  Blynk.run(); // Run Blynk process
  timer.run(); // checks if it's time to call any function scheduled by the timer.
}