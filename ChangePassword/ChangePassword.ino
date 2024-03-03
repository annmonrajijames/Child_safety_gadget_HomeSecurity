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

String password = "1234"; // Default password
String enteredPassword;
bool changePasswordMode = false;

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.print(key);
    
    // Check if we're in change password mode
    if(changePasswordMode) {
      // If '#' is pressed, save the new password and exit change password mode
      if(key == '#') {
        password = enteredPassword;
        changePasswordMode = false;
        Serial.println("\nNew password set.");
        enteredPassword = ""; // Reset for next password entry
      } else {
        // Append the pressed key to the new password
        enteredPassword += key;
      }
    } else {
      // If '0' is pressed, enable change password mode
      if(key == '0') {
        changePasswordMode = true;
        enteredPassword = ""; // Reset to start new password entry
        Serial.println("\nEnter new password followed by '#'.");
      } else {
        // Normal password checking
        enteredPassword += key;
        if (enteredPassword.length() == password.length()) {
          if (enteredPassword == password) {
            Serial.println("\nPassword Correct");
            // Add action here (unlock door, turn on light, etc.)
          } else {
            Serial.println("\nPassword Incorrect");
          }
          enteredPassword = ""; // Reset entered password
        }
      }
    }
  }
}