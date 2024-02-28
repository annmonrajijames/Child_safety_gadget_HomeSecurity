#define VibrationSensor D4

void setup(){
  pinMode(VibrationSensor, INPUT); 
  Serial.begin(9600); 

}
void loop(){
  long measurement =vibration();
  delay(50);
  Serial.println(measurement);
  if (measurement > 50){
    Serial.println("Door vibrated");
  }
  else{
    Serial.println("Door not vibrated");
  }
}

long vibration(){
  long measurement=pulseIn (VibrationSensor, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}