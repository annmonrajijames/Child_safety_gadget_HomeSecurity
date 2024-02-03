// Blinks an LED attached to a MCP23XXX pin.
#include <Adafruit_MCP23X17.h>

#define LED_PIN 0     // MCP23XXX pin LED is attached to GPA0; MCP23x17 Pin 21

Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);
  Serial.println("MCP23xxx Blink Test!");
  if (!mcp.begin_I2C()) {
    Serial.println("Error.");
    while (1);
  }
  mcp.pinMode(LED_PIN, OUTPUT);
  Serial.println("Looping...");
}

void loop() {
 mcp.digitalWrite(LED_PIN, HIGH);
 delay(500);
 mcp.digitalWrite(LED_PIN, LOW);
 delay(500);
}