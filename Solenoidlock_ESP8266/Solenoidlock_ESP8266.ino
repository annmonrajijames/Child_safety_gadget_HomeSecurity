#define BLYNK_TEMPLATE_ID "TMPL3gxKbEIS5" // Blynk template and authentication information
#define BLYNK_TEMPLATE_NAME "HomeSecurity"
#define BLYNK_AUTH_TOKEN "RDs-5TaFIsxVHn6VEC483jSQKw_JjJ0q"
#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Annmon"; // WiFi network name
char pass[] = "childsafe"; // WiFi password

#include <ESP8266WiFi.h>
#include <Keypad.h>
#include <BlynkSimpleEsp8266.h>

const byte ROWS = 3; // Three rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},

  {'*','0','#'}
};
byte rowPins[ROWS] = {D0, D1, D2}; // Connect keypad ROW0, ROW1 and ROW3 to these pins respectively.
byte colPins[COLS] = {D3, D4, D5}; // Connect keypad COL0, COL1 and COL2 to these pins respectively.
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Initialize the keypad
String v_passcode="";
BlynkTimer timer; // timer object created, BlynkTimer is a class.

void setup() {
Blynk.begin(auth, ssid, pass); // Start Blynk using WiFi credentials
Serial.begin(9600); // Start serial communication at 9600 baud rate
pinMode(D6, OUTPUT); // Pin connected to the relay controlling the solenoid lock
digitalWrite(D6, LOW); // Start with the solenoid lock in locked state
pinMode(D7, OUTPUT); // Green LED
pinMode(D8, OUTPUT); // Red LED
timer.setInterval(1L, emailsetup); // Set timer to call emailsetup function every 1 second
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
        digitalWrite(D6, LOW); // Unlock the solenoid lock
        digitalWrite(D6, HIGH); // Turn on buzzer
        digitalWrite(D7, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
        digitalWrite(D6, LOW);  // Turn off buzzer
        digitalWrite(D7, LOW);  // Turn off green LED

      } else if (v_passcode == "123#") { 
      /* Pseudo-password [From outside of the device it will show correct, 
      but it signals SOS to parents]*/
       Blynk.logEvent("password_entry", "Your Child is in danger"); // Child entered SOS code
        digitalWrite(D6, LOW); // Unlock the solenoid lock
        digitalWrite(D7, HIGH); // Turn on green LED
        delay(3000);  
        digitalWrite(D7, LOW);  // Turn on green LED
      } else if (v_passcode == "4321#") { // To Unlock the door
        Blynk.logEvent("password_entry", "Door is Locked now");
        Serial.println("\nDoor is Locked");
        digitalWrite(D6, HIGH); // Lock the solenoid lock
        digitalWrite(D7, HIGH); // Turn on green LED
        delay(100); // Wait for 1/10 second
        digitalWrite(D7, LOW);  // Turn off green LED
        delay(100); // Wait for 1/10 second
        digitalWrite(D8, HIGH); // Red LED On
        delay(100); // Wait for 1/10 second
        digitalWrite(D8, LOW); // Red LED Off 
      } else { // Password is wrong
      Blynk.logEvent("password_entry", "Wrong Passcode Entered"); // Wrong password entry
        Serial.println("Access Denied");
          digitalWrite(D8,HIGH); // RED led
          delay(2000);
          digitalWrite(D8,LOW); // RED led
      }
      Serial.println("The entered password is " + v_passcode);
      v_passcode = ""; // Reset the passcode string
    }
  }
  
}
void loop() {
  Blynk.run(); // Run Blynk process
  timer.run(); // checks if it's time to call any function scheduled by the timer.
}
