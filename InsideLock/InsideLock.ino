void setup() {
pinMode(D6, OUTPUT); // Pin connected to the relay controlling the solenoid lock
digitalWrite(D6, LOW); // Start with the solenoid lock in locked state
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(D6, HIGH);
delay(2000);
digitalWrite(D6, LOW);
delay(2000);
}