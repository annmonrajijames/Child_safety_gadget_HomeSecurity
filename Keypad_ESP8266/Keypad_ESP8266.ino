#include <Keypad.h>

const byte ROWS = 3; // Three rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},

  {'*','0','#'}
};
byte rowPins[ROWS] = {D0, D1, D2}; // Connect keypad ROW0, ROW1 and ROW3 to these pins.
byte colPins[COLS] = {D3, D4, D5}; // Connect keypad COL0, COL1 and COL2 to these pins.

void setup() {
Serial.begin(9600); // Initialize serial communication
}

void loop() {

}