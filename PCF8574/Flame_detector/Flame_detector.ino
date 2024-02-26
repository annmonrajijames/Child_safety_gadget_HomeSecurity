const int flameSensor = D0; 
void setup() {
  Serial.begin(9600); // Start the Serial communication
  pinMode(flameSensor, INPUT); // Set the flame sensor pin as an input
}

void loop() {
  if (isFlameDetected()) {
    Serial.println("Flame detected!");    // Flame is detected
  }   
}

// Function to check if a flame is detected
bool isFlameDetected() {
  int flameDetected = digitalRead(flameSensor); // Read the flame sensor value
  return flameDetected == LOW; // Return true if flame is detected
}
