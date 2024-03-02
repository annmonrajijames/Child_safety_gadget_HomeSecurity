#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Connect to the row pinouts of the keypad
byte rowPins[ROWS] = {D0, D1, D2, D3};
// Connect to the column pinouts of the keypad
byte colPins[COLS] = {D4, D5, D6};

// Initialize the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String password = "1234"; // Example password
String enteredPassword;

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  // If a key is pressed, append it to the enteredPassword
  if (key != NO_KEY){
    Serial.print(key);
    enteredPassword += key;

    // Check if the entered password is correct after reaching the password length
    if (enteredPassword.length() == password.length()) {
      if (enteredPassword == password) {
        Serial.println("\nPassword Correct");
        // Add actions here (unlock door, turn on light, etc.)
      } else {
        Serial.println("\nPassword Incorrect");
      }
      enteredPassword = ""; // Reset entered password after each attempt
    }
  }
}