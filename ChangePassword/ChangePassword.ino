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
bool verifyMode = false; // Indicates if the system is in verification mode
bool changePasswordMode = false; // Indicates if the system is in password change mode
String randomPassword = "";

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Initialize random number generator
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    // Reset the entered password if '*' is pressed
    if(key == '*') {
      enteredPassword = "";
      Serial.println("\nEnter password:");
    }
    // Enter verify mode if '0' is pressed
    else if(key == '0' && !verifyMode && !changePasswordMode) {
      randomPassword = String(random(1000, 10000)); // Generate 4-digit random number
      Serial.print("\nEnter the number: "); // Enter the OTP (One-time password)
      Serial.println(randomPassword); // Debug: Show the random number
      verifyMode = true;
      enteredPassword = ""; // Clear enteredPassword for new input
    }
    // Handle number verification
    else if(verifyMode) {
      if(key != '#') {
        enteredPassword += key; // Append key to enteredPassword if not '#'
      } else {
        // Check if entered number matches the random number
        if(enteredPassword == randomPassword) {
          Serial.println("\nNumber Verified. Enter new password followed by '#'.");
          verifyMode = false;
          changePasswordMode = true;
          enteredPassword = ""; // Clear for new password entry
        } else {
          Serial.println("\nVerification Failed. Try again.");
          verifyMode = false;
          enteredPassword = ""; // Reset for a new attempt
        }
      }
    }
    // Handle new password setup
    else if(changePasswordMode) {
      if(key != '#') {
        enteredPassword += key; // Append key to enteredPassword if not '#'
      } else {
        // Set the new password and exit change password mode
        password = enteredPassword;
        changePasswordMode = false;
        Serial.println("\nNew password set.");
        enteredPassword = ""; // Clear after setting new password
      }
    }
    // Normal password entry mode
    else if (!verifyMode && !changePasswordMode) {
      if(key != '#') {
        enteredPassword += key;
      } else {
        // Check the entered password
        if(enteredPassword == password) {
          Serial.println("\nPassword Correct");
          // Action after correct password (unlock door, etc.)
        } else {
          Serial.println("\nPassword Incorrect");
        }
        enteredPassword = ""; // Reset entered password
      }
    }
  }
}