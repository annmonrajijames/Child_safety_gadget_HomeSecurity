#include <ESP8266WiFi.h>
#include <Keypad.h>

const int numRows = 4; // Number of rows on the keypad
const int numCols = 3; // Number of columns on the keypad

char keys[numRows][numCols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[numRows] = {D0, D1, D2, D3}; // Connect to the row pinouts of the keypad
byte colPins[numCols] = {D4, D5, D6};      // Connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, numRows, numCols );

String password = "1234"; // Set your password here
String enteredPassword = "";

void setup(){
  Serial.begin(9600);
  Serial.println("Enter Password:");
}

void loop(){
  char key = keypad.getKey();
  
  if(key){
    if(key == '#'){
      if(enteredPassword == password){
        Serial.println("Access granted!");
        Serial.println("Enter Password:");
        enteredPassword = "";
      }
      else{
        Serial.println("Access denied!");
        Serial.println("Enter Password:");
        enteredPassword = "";
      }
    }
    else{
      enteredPassword += key;
      Serial.print(key);
    }
  }
}