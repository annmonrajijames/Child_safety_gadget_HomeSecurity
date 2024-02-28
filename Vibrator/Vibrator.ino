int led = 13;
int vs =9; // vibration sensor

void setup(){
  pinMode(led, OUTPUT);
  pinMode(vs, INPUT); 
  Serial.begin(9600); 

}
void loop(){
  long measurement =vibration();
  delay(50);
  Serial.println(measurement);
  if (measurement > 50){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW); e
  }
}

long vibration(){
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}