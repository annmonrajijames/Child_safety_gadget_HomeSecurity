#define VibratingSensor D3 // Only D3 and D4 pins left in my microcontroller, rest all used
void setup(){
  pinMode(VibratingSensor, INPUT); 
  Serial.begin(9600); 

}
void loop(){
  long measurement =vibration();
  if (measurement > 50){
    Serial.println("Your door is vibrating");
  }
}

long vibration(){
  long measurement=pulseIn (VibratingSensor, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}