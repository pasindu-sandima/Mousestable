void drive(int Rspeed,int Lspeed){
    if(Rspeed>0){
        digitalWrite(RM1,HIGH);
        digitalWrite(RM2,LOW);
    }
    else{
        digitalWrite(RM1,LOW);
        digitalWrite(RM2,HIGH);
        Rspeed=-Rspeed;
    }
    if(Lspeed>0){
        digitalWrite(LM1,HIGH);
        digitalWrite(LM2,LOW);
    }
    else{
        digitalWrite(LM1,LOW);
        digitalWrite(LM2,HIGH);
        Lspeed=-Lspeed;
    }
    if(Rspeed>225){
        Rspeed = 225;
    }
    if(Lspeed>225){
        Lspeed=225;
    }            
    analogWrite(Rpwm,Rspeed);
    analogWrite(Lpwm,Lspeed);
}

void brake(){
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2,HIGH);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2,HIGH);
    digitalWrite(Rpwm, HIGH);
    digitalWrite(Lpwm,HIGH);
}

void turnR(){
    countForward(190,213,216);
    brake();
    delay(100);
    leftcount=0;
    drive(-255,255);
    while(true){
        if(leftcount>600){
            brake();
            break;
        }
    }
    delay(100);
    countBackward(140,213,216);
}

void turnL(){
    countForward(190,213,216);
    brake();
    delay(100);
    rightcount=0;
    drive(255,-255);
    while(true){
        if(rightcount>610){
            brake();
            break;
        }
    }
    delay(100);
    countBackward(140,213,216);
}

void turnLGyro(){
    while(true){
        drive(150,-150);
        getGyro();
        Serial.println(GyroZ);
        if(GyroZ>angle+160){
            brake();
            getGyro();
            Serial.println(GyroZ);
            break;
        }
  }
}

void turnRGyro(){
    while(true){
    drive(-150,150);
    getGyro();
    Serial.println(GyroZ);
    if(GyroZ<angle-165){
      brake();
      getGyro();
      Serial.println(GyroZ);
      break;
    }

  }
}

void turn180(){
    brake();
    delay(100);
    rightcount=0;
    drive(255,-255);
    while(true){
        if(rightcount>1285){
            brake();
            break;
        }
    }
    delay(100);
    countBackward(370,213,216);
}

void countForward(uint16_t count, int Rspeed,int Lspeed){
    rightcount=0;
    drive(Rspeed,Lspeed);
    while(true){
        if(rightcount>count){
            brake();
            break;
        }
    }
    delay(100);
}
void countBackward(uint16_t count, int Rspeed,int Lspeed){
    rightcount=1000;
    drive(-Rspeed,-Lspeed);
    while(true){
        if(rightcount<1000-count){
            brake();
            break;
        }
    }
    delay(100);
}

void moveCell(){
    rightcount=0;
    while(true){
        getDistance(3);
        getDistance(4);
        getDistance(2);
        getDistance(5);
        getDistance(1);
        getDistance(6);
        if((distanceRT<130)&&(distanceR<80)){
            for(int i=0;i<5;i++){
                wallFollowR();
                if(rightcount>1350){
                    break;
                }
            }
            Serial.println(0);
        }
        else if((distanceLT<130)&&(distanceL<80)){
            for(int i=0;i<5;i++){
                wallFollowL();
                if(rightcount>1350){
                    break;
                }
            }
            Serial.println(1);
        }
        else{
            drive(213,216);
            Serial.println(2);
        }
        if(rightcount>1350){
            break;
        }
        if((distanceRF<70)||(distanceLF<70)){
            brake();
            while(digitalRead(button2)){}
            break;
        }
    }
    // brake();
    // Buzzer(2);

}

void driveForward(){
    drive(213,216);
}