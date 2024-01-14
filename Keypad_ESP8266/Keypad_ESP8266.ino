#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

void setup() {
Serial.begin(9600); // Initialize serial communication
}

void loop() {

}