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
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String passwords[3] = {"1234", "5678", "5454"}; // Default passwords for Secret 1, 2, and 3
String enteredPassword;
bool verifyMode = false; // Indicates if the system is in verification mode
int changePasswordStep = 0; // Tracks the step in the change password sequence
String randomPassword = "";
BlynkTimer timer; // timer object created, BlynkTimer is a class.

void setup() {
  Blynk.begin(auth, ssid, pass); // Start Blynk using WiFi credentials
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Initialize random number generator
  timer.setInterval(1L, emailsetup); // Set timer to call emailsetup function every 1 second
}

void emailsetup() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '*') {
      enteredPassword = "";
      Serial.println("\nEnter password:");
    } else if (key == '0' && !verifyMode && changePasswordStep == 0) {
      randomPassword = String(random(1000, 10000));
      String SecretMessage= "OTP (One time password) is " + String(randomPassword);
      Blynk.logEvent("password_entry", SecretMessage);
      Serial.print("\nEnter the OTP (One Time Password): ");
      verifyMode = true;
      enteredPassword = "";
    } else if (verifyMode) {
      verifyRandomPassword(key);
    } else if (changePasswordStep > 0) {
      setNewPasswords(key);
    } else {
      checkPasswords(key);
    }
  }
}

void verifyRandomPassword(char key) {
  if (key != '#') {
    enteredPassword += key;
  } else {
    if (enteredPassword == randomPassword) {
      Serial.println("\nNumber Verified. Proceed to set new passwords.");
      verifyMode = false;
      changePasswordStep = 1; // Proceed to change passwords for Secret 1
    } else {
      Serial.println("\nVerification Failed. Try again.");
      verifyMode = false;
    }
    enteredPassword = "";
  }
}

void setNewPasswords(char key) {
  if (key != '#') {
    enteredPassword += key;
  } else {
    passwords[changePasswordStep - 1] = enteredPassword;
    Serial.print("\nNew password for Secret ");
    Serial.print(changePasswordStep);
    Serial.println(" set.");
    enteredPassword = "";
    changePasswordStep++;
    if (changePasswordStep > 3) {
      changePasswordStep = 0; // Reset after setting all new passwords
      Serial.println("\nAll new passwords are set.");
    }
  }
}

void checkPasswords(char key) {
  if (key == '#') {
    bool passwordMatched = false;

      if (enteredPassword == passwords[0]) {
        Blynk.logEvent("password_entry", "Your child reached home"); // correct password entry
        Serial.print("\nPassword Correct- Secret 1");
        passwordMatched = true;
      }
      if (enteredPassword == passwords[1]) {
        Blynk.logEvent("password_entry", "Your Child is in danger"); // Child entered SOS code
        Serial.print("\nPassword Correct- Secret 2");
        passwordMatched = true;
      }
      if (enteredPassword == passwords[2]) {
        Blynk.logEvent("password_entry", "Door locked");      
        Serial.print("\nPassword Correct- Secret 3");
        passwordMatched = true;
      }

    if (!passwordMatched) {
      Blynk.logEvent("password_entry", "Password incorrect"); 
      Serial.println("\nPassword Incorrect");
    }
    enteredPassword = ""; // Reset entered password
  } else {
    enteredPassword += key;
  }
}
void loop() {
  Blynk.run(); // Run Blynk process
  timer.run(); // checks if it's time to call any function scheduled by the timer.
}