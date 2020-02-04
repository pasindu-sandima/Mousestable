#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <VL53L0X.h>
#include "global_space.h"
#include "function_list.h"

#include "functions\tofSetup.h"
#include "functions\pinModes.h"
#include "functions\mazeSolve.h"
#include "functions\drive.h"
#include "functions\others.h"
#include "functions\newflood.h"
#include "functions\Gyro.h"
#include "Algo\floodfill.h"
#include "Algo\maze.h"
#include "Algo\stack.h"
#include "Algo\backTrack.h"





void setup() {
  floodfillSetup();
  pinModes();
  Serial.begin(115200);
  init_hardware_timer_version();
  while(digitalRead(button2)){}
  Buzzer(500);
  Serial.println("Starting");
  Wire.begin();
  Wire1.begin();  
  Buzzer(300);
  tofSetup();
  // initGyro();
  Buzzer(300);

  // floodfillNew();
  // edgetocenter();
  // brake();
  // for(int i=0;i<5;i++){
  //   Buzzer(100);
  //   delay(50);
  // }
  // center();
  // for(int i=0;i<5;i++){
  //   Buzzer(100);
  //   delay(50);
  // }
  // backFloodfillNew();
  // edgetocenter();
  // brake();
  // for(int i=0;i<5;i++){
  //   Buzzer(100);
  //   delay(50);
  // }




}

void loop() {
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  while(digitalRead(button2)){
    if(digitalRead(button1)){}
    else{
      Buzzer(200);
      Mode+=1;
      if(Mode>3){
        Mode=0;
      }
    }
    if(digitalRead(button2)){}
    else{
      Buzzer(200);
      if(Mode==0){
        Mode=3;
      }
      else{
        Mode-=1;
      }
    }
    if(Mode==0){
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
    }
    else if(Mode==1){
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
    }
    else if(Mode==2){
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,LOW);
    }
    else if(Mode==3){
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
    }
  }
  Buzzer(400);

  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);

  while(digitalRead(button2)){
    if(Mode==0){
      break;
    }
    else if(Mode==1){
      face=0;
      R=0,C=0;
      N=0,E=1,S=1,W=1;
      floodfillNew();
      edgetocenter();
      brake();
      for(int i=0;i<5;i++){
        Buzzer(100);
        delay(50);
      }
      center();
      for(int i=0;i<5;i++){
        Buzzer(100);
        delay(50);
      }
      backFloodfillNew();
      edgetocenter();
      brake();
      for(int i=0;i<5;i++){
        Buzzer(100);
        delay(50);
      }
      break;

    }
    else if(Mode==2){
      face=1;
      R=0,C=0;
      N=1,E=0,S=1,W=1;
      floodfillNew();
      edgetocenter();
      brake();
      for(int i=0;i<5;i++){
        Buzzer(100);
        delay(50);
      }
      center();
      for(int i=0;i<5;i++){
        Buzzer(100);
        delay(50);
      }
      backFloodfillNew();
      edgetocenter();
      brake();
      for(int i=0;i<5;i++){
        Buzzer(100);
        delay(50);
      }
      break;
      
    }
    else if(Mode==3){
      
    }
  }
  Buzzer(200);
}
