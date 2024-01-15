#include <Keypad.h>

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
void setup() {
Serial.begin(9600); // Start serial communication at 9600 baud rate
pinMode(D6, OUTPUT); // Buzzer
pinMode(D7, OUTPUT); // Green LED
pinMode(D8, OUTPUT); // Red LED
}

void loop() {
char key = keypad.getKey(); // Read the key that is pressed
  if (key) { // The pressed key will shown as output
    Serial.println(key);
  }
}