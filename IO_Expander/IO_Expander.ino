#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23XXX.h>

#include <Wire.h>

// Create MCP23017 instance
Adafruit_MCP23X17 mcp;

void setup() {
  mcp.begin_I2C();      // Default address 0

  // Set MCP23017 pins to output
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
}

void loop() {
  // Turn LEDs on
  mcp.digitalWrite(0, HIGH);
  mcp.digitalWrite(1, HIGH);
  delay(500);

  // Turn LEDs off
  mcp.digitalWrite(0, LOW);
  mcp.digitalWrite(1, LOW);
  delay(500);
}