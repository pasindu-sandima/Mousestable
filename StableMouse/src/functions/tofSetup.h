VL53L0X Sensor1;      //Right Sensor
VL53L0X Sensor2;      //TILT RIGHT Sensor
VL53L0X Sensor3;      //Front RIGHT Sensor
VL53L0X Sensor4;      //Front LEFT Sensor
VL53L0X Sensor5;      //TILT LEFT Sensor
VL53L0X Sensor6;      //Left Sensor

void tofSetup(){
  pinMode(XSHUT_pin1, OUTPUT);
  pinMode(XSHUT_pin2, OUTPUT);
  pinMode(XSHUT_pin3, OUTPUT);
  pinMode(XSHUT_pin4, OUTPUT);
  pinMode(XSHUT_pin5, OUTPUT);
  pinMode(XSHUT_pin6, OUTPUT);
  digitalWrite(XSHUT_pin1,LOW);
  digitalWrite(XSHUT_pin2,LOW);
  digitalWrite(XSHUT_pin3,LOW);
  digitalWrite(XSHUT_pin4,LOW);
  digitalWrite(XSHUT_pin5,LOW);
  digitalWrite(XSHUT_pin6,LOW);

  pinMode(XSHUT_pin6,INPUT);
  delay(10);
  Sensor6.setAddress(Sensor6_newAddress);
  
  pinMode(XSHUT_pin5,INPUT);
  delay(10);
  Sensor5.setAddress(Sensor5_newAddress);
  
  pinMode(XSHUT_pin4, INPUT);
  delay(10);
  Sensor4.setAddress(Sensor4_newAddress);
  
  pinMode(XSHUT_pin3,INPUT);
  delay(10);
  Sensor3.setAddress(Sensor3_newAddress);
  
  pinMode(XSHUT_pin2,INPUT);
  delay(10);
  Sensor2.setAddress(Sensor2_newAddress);
  
  pinMode(XSHUT_pin1, INPUT);
  delay(10);
  Sensor1.setAddress(Sensor1_newAddress);
 
  if(Sensor1.init()){
    Serial.println("Sensor 1 : Configured");
  }
  else{
    Serial.println("Sensor 1 : Configuration Failed");
  }
  if(Sensor2.init()){
    Serial.println("Sensor 2 : Configured");
  }
  else {
    Serial.println("Sensor 2 : Configuration Failed");
  }
  if(Sensor3.init()){
    Serial.println("Sensor 3 : Configured");
  }
  else{
    Serial.println("Sensor 3 : Configuration Failed");
  }
  if(Sensor4.init()){
    Serial.println("Sensor 4 : Configured");
  }
  else{
    Serial.println("Sensor 4 : Configuration Failed");
  }
  if(Sensor5.init()){
    Serial.println("Sensor 5 : Configured");
  }
  else{
    Serial.println("Sensor 5 : Configuration Failed");
  }
  if(Sensor6.init()){
    Serial.println("Sensor 6 : Configured");
  }
  else{
    Serial.println("Sensor 6 : Configuration Failed");
  }

  // Sensor1.setMeasurementTimingBudget(20000);
  // Sensor2.setMeasurementTimingBudget(20000);
  // Sensor3.setMeasurementTimingBudget(20000);
  // Sensor4.setMeasurementTimingBudget(20000);
  // Sensor5.setMeasurementTimingBudget(20000);
  // Sensor6.setMeasurementTimingBudget(20000);

  Sensor1.startContinuous();
  Sensor2.startContinuous();
  Sensor3.startContinuous();
  Sensor4.startContinuous();
  Sensor5.startContinuous();
  Sensor6.startContinuous();

  Serial.println("TOF setup done");
}

void measure(){
  distanceR = Sensor1.readRangeContinuousMillimeters();
  distanceRF = Sensor2.readRangeContinuousMillimeters()-28;
  distanceRT = Sensor3.readRangeContinuousMillimeters()-40;
  distanceLT = Sensor4.readRangeContinuousMillimeters();
  distanceLF = Sensor5.readRangeContinuousMillimeters();
  distanceL = Sensor6.readRangeContinuousMillimeters()-3;
}
int getDistance(uint8_t Sensor){
  if(Sensor==1){
    distanceR=Sensor1.readRangeContinuousMillimeters();
    return distanceR;
  }
  else if(Sensor==2){
    distanceRF=Sensor2.readRangeContinuousMillimeters()-28;
    return distanceRF;
  }
  else if(Sensor==3){
    distanceRT=Sensor3.readRangeContinuousMillimeters()-40;
    return distanceRT;
  }
  else if(Sensor==4){
    distanceLT=Sensor4.readRangeContinuousMillimeters();
    return distanceLT;
  }
  else if(Sensor==5){
    distanceLF=Sensor5.readRangeContinuousMillimeters();
    return distanceLF;
  }
  else if(Sensor==6){
    distanceL=Sensor6.readRangeContinuousMillimeters()-3;
    return distanceL;
  }

}

void printDistance(){
  delay(150);
  time = millis();
  measure();
  time = millis()-time;
  Serial.print(distanceL);
  Serial.print(" , ");
  Serial.print(distanceLF);
  Serial.print(" , ");
  Serial.print(distanceLT);
  Serial.print(" , ");
  Serial.print(distanceRT);
  Serial.print(" , ");
  Serial.print(distanceRF);
  Serial.print(" , ");
  Serial.print(distanceR);
  Serial.print(" , ");
  Serial.println(time);
}