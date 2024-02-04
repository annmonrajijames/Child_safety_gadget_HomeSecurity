#include <Keypad.h>
// #define Buzzer D1
// #define GreenLed D0
// #define RedLed D2
const byte ROWS = 3; // Three rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},

  {'*','0','#'}
};
byte rowPins[ROWS] = {D3, D4, D5}; // Connect keypad ROW0, ROW1 and ROW3 to these pins respectively.
byte colPins[COLS] = {D6, D7, D8}; // Connect keypad COL0, COL1 and COL2 to these pins respectively.
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Initialize the keypad
String v_passcode="";
void setup() {
Serial.begin(9600); // Start serial communication at 9600 baud rate
/*pinMode(Buzzer, OUTPUT); // Buzzer
pinMode(GreenLed, OUTPUT); // Green LED
pinMode(RedLed, OUTPUT); // Red LED*/
}

void loop() {
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
       Serial.println("Access Granted");
       // digitalWrite(Buzzer, HIGH); // Turn on buzzer
       // digitalWrite(GreenLed, HIGH); // Turn on green LED
        delay(3000); // Wait for 3 seconds
       // digitalWrite(Buzzer, LOW);  // Turn off buzzer
       // digitalWrite(GreenLed, LOW);  // Turn off green LED

      } else if (v_passcode == "123#") { 
      /* Pseudo-password [From outside of the device it will show correct, 
      but it signals SOS to parents]*/
       // digitalWrite(Buzzer, HIGH); // Output from device is same as correct password 
      //digitalWrite(GreenLed, HIGH); 
        delay(3000); 
       // digitalWrite(Buzzer, LOW);  
       // digitalWrite(GreenLed, LOW);  
      } else { // Password is wrong
        Serial.println("Access Denied");
        /* for (int i = 0; i < 3; i++) {
          digitalWrite(Buzzer, HIGH);
          delay(50);
          digitalWrite(Buzzer, LOW);
          delay(50);
        }
          digitalWrite(RedLed,HIGH);
          delay(2000);
          digitalWrite(RedLed,LOW); */
      } 
      Serial.println("The entered password is " + v_passcode);
    }
  }
  
}