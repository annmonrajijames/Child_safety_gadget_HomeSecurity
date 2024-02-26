#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  textexample();
}
  

void loop() {
}

void textexample(void) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("Start");
  display.display();
  delay(2000);
  display.setCursor(50,27);
  display.println("Middle");
  display.display();
  delay(2000);
  display.setCursor(100,55);
  display.println("End");
  display.display();
  delay(2000);
  display.setCursor(0,55);
  display.println("bottom left");
  display.display();
  delay(2000);
  display.setCursor(72,0);
  display.println("top right");
  display.display();
}