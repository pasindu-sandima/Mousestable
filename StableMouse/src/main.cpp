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

// uint8_t list[500] = {7, 1, 1, 2, 4, 7, 1, 9, 0, 0, 1, 1, 2, 3, 5, 8, 4, 3, 7, 0, 8, 9, 7, 6, 4, 1, 5, 6, 2, 9, 2, 1, 3, 5, 9, 4, 4, 9, 3, 2, 6, 8, 4, 3, 8, 1, 9, 0, 0, 1, 2, 3, 5, 8, 4, 3, 7, 1, 9, 0, 9, 0, 0, 1, 1, 2, 4, 7, 2, 9, 1, 1, 3, 4, 8, 3, 1, 4, 6, 1, 7, 8, 6, 5, 1, 6, 8, 5, 3, 9, 2, 2, 5, 7, 2, 9, 1, 0, 2, 3, 5, 8, 3, 1, 5, 7, 2, 9, 1, 1, 2, 3, 6, 0, 7, 7, 5, 2, 8, 1, 9, 0, 9, 9, 8, 8, 7, 5, 3, 9, 2, 1, 4, 6, 1, 7, 8, 6, 5, 1, 6, 8, 5, 3, 8, 2, 1, 3, 5, 8, 3, 2, 6, 8, 4, 3, 8, 2, 1, 3, 4, 7, 2, 0, 2, 2, 5, 7, 2, 0, 3, 4, 7, 2, 0, 2, 2, 4, 6, 1, 8, 9, 8, 7, 6, 4, 0, 4, 4, 8, 3, 2, 5, 8, 3, 2, 5, 8, 3, 2, 6};



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
  Buzzer(300);

  //add another comment

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
