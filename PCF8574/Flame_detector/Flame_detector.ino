// Define the GPIO pin where the flame sensor is connected
const int flameSensor = D0; // Example pin D1, change according to your setup

void setup() {
  Serial.begin(9600); // Start the Serial communication
  pinMode(flameSensor, INPUT); // Set the flame sensor pin as an input
}

void loop() {
  if (isFlameDetected()) {
    Serial.println("No flame detected!");    // Flame is not detected
  } else {
    Serial.println("Flame detected.");     // Flame detected
  }  
  delay(1000); // Wait for 1 second before reading again
}

// Function to check if a flame is detected
bool isFlameDetected() {
  int flameDetected = digitalRead(flameSensor); // Read the flame sensor value
  return flameDetected == HIGH; // Return true if flame is detected, false otherwise
}
