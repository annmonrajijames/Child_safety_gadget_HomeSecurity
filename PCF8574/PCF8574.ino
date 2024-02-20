/* tecnologias jpc
 *  code to use matrix keypad with PCF8574 module y OLED
 *  circuit https://drive.google.com/file/d/1safDFtSTFCdoUiZfRS5aiq9BK9p3Zf_4/view?usp=sharing
 *  compatible with omega board http://www.tecnologiasjpc.com/
*/
#define SCREEN_WIDTH    128        // OLED screen width
#define SCREEN_HEIGHT   32         // OLED screen height
#define OLED128         0x3C       // OLED address
#define I2CADDR         0x20       // matrix keypad address

#include <Wire.h>                 //library for I2C communication
#include <Adafruit_SSD1306.h>     //library for OLED
#include <Keypad_I2C.h>           //library for matrix keypad I2C communication
#include <Keypad.h>               //library for matrix keypad

const byte ROWS = 4;              // 4 rows in matrix keypad
const byte COLS = 4;              // 4 columns in matrix keypad

//define a character for every button
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {0, 1, 2, 3}; // row pins connected to I2C module 
byte colPins[COLS] = {4, 5, 6, 7}; // column pins connected to I2C module 

// object for OLED control
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// object for matrix keypad
Keypad_I2C customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 

void setup(){
  Serial.begin(9600);                     // initialize serial communication
  customKeypad.begin( );                  // initialize matrix keypad
  
  // initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED128)) {
     Serial.println(F("Error al iniciar OLED"));
     for(;;);
  }
  display.clearDisplay();                 // clear OLED screen
  display.display();                      // execute previous commands sent to OLED
  display.setTextSize(1);                 // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);    // write white text on OLED screen
  display.setCursor(0, 0);                // set cursor at top-left corner
}
  
void loop(){
  char pressed_key = customKeypad.getKey();  // save character pressed 
  if (pressed_key != NO_KEY){                // ask for any pressed button 
    Serial.println(pressed_key);             // write character pressed in serial monitor
    display.write(pressed_key);              // write character pressed in OLED
    display.display();                       // execute previous commands sent to OLED
  }
}