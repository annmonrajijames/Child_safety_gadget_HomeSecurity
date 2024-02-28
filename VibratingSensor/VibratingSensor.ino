#define VibratingSensor D3
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