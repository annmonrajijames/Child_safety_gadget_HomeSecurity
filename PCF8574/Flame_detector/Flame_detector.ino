// Define the GPIO pin where the flame sensor is connected
const int flameSensorPin = D0; // Example pin D1, change according to your setup

void setup() {
  Serial.begin(115200); // Start the Serial communication
  pinMode(flameSensorPin, INPUT); // Set the flame sensor pin as an input
}

void loop() {
  int flameDetected = digitalRead(flameSensorPin); // Read the flame sensor value
  
  if (flameDetected == LOW) {
    // Flame is detected
    Serial.println("Flame detected!");
  } else {
    // No flame detected
    Serial.println("No flame detected.");
  }
  
  delay(1000); // Wait for 1 second before reading again
}
