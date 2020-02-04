void pinModes(){

    pinMode(RM1,OUTPUT);
    pinMode(RM2,OUTPUT);
    pinMode(LM1,OUTPUT);
    pinMode(LM2,OUTPUT);
    // pinMode(Standby,OUTPUT);
    // digitalWrite(Standby,HIGH);
    pinMode(Buzzer_Pin,OUTPUT);
    pinMode(Rpwm,OUTPUT);
    pinMode(Lpwm,OUTPUT);
    analogWriteFrequency(20000);
    // analogWriteResolution(10);

    pinMode(button1,INPUT_FLOATING);
    pinMode(button2,INPUT_FLOATING);
    pinMode(button3,INPUT_FLOATING);
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);


}