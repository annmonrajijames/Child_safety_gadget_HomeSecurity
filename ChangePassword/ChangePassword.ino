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
byte rowPins[ROWS] = {D0, D1, D2, D3}; // Adjust pins according to your setup
// Connect to the column pinouts of the keypad
byte colPins[COLS] = {D4, D5, D6}; // Adjust pins according to your setup

// Initialize the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String password = "1234"; // Default password
String enteredPassword;
bool changePasswordMode = false;

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    // If '*' is pressed, reset the entered password
    if(key == '*') {
      enteredPassword = "";
      Serial.println("\nEnter password:");
    }
    // If '#' is pressed, check or set the password
    else if(key == '#') {
      if(changePasswordMode) {
        // Set the new password and exit change password mode
        password = enteredPassword;
        changePasswordMode = false;
        enteredPassword = "";
        Serial.println("\nNew password set.");
      } else {
        // Check the entered password
        if(enteredPassword == password) {
          Serial.println("\nPassword Correct");
          // Add action here (unlock door, turn on light, etc.)
        } else {
          Serial.println("\nPassword Incorrect");
        }
        enteredPassword = ""; // Reset entered password
      }
    }
    else {
      // Enter change password mode if '0' is pressed
      if(key == '0' && enteredPassword.isEmpty()) {
        changePasswordMode = true;
        Serial.println("\nEnter new password followed by '#'.");
      } else {
        // Append the pressed key to the entered password
        enteredPassword += key;
      }
    }
  }
}