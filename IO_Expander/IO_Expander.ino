#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>

// Initialize MCP23017 with the address 0x24 (adjust if needed)
MCP23017 mcp = MCP23017(0x24);

void setup() {
  Wire.begin();    // Start I2C communication
  mcp.init();      // Initialize MCP23017

  // Set pin 8 (GPB0) to output. Adjust as needed for your setup.
  mcp.pinMode(8, OUTPUT);
}

void loop() {
  // Turn the LED on at pin 8
  mcp.digitalWrite(8, HIGH);

  // Wait for a second
  delay(1000);

  // Turn the LED off at pin 8
  mcp.digitalWrite(8, LOW);

  // Wait for a second
  delay(1000);
}
