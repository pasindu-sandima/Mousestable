#ifndef GLOBAL_SPACE_H
#define GLOBAL_SPACE_H



//Motor Controlling
#define RM1 PB0
#define RM2 PB1
#define LM1 PA4
#define LM2 PA5
// #define Standby PA7
#define Rpwm PB9
#define Lpwm PB8


#define Buzzer_Pin PB5
#define button1 PB12        //Right
#define button2 PB13        //Middle
#define button3 PB14        //Left
#define LED1 PB15           //Blue
#define LED2 PA8            //Green
#define LED3 PA11           //Red


//TOF setup
#define XSHUT_pin1 PA12           //Right Sensor
#define XSHUT_pin2 PA15        //Left Sensor
#define XSHUT_pin3 PB3           //Front Sensor    
#define XSHUT_pin4 PB4           //Right Sensor
#define XSHUT_pin5 PA2          //Left Sensor
#define XSHUT_pin6 PA3        //Front Sensor  

#define Sensor1_newAddress 42
#define Sensor2_newAddress 43
#define Sensor3_newAddress 44
#define Sensor4_newAddress 45
#define Sensor5_newAddress 46
#define Sensor6_newAddress 47

#define SignalRateLimit 0.8          //Higher the limit , higher the accuracy
#define MeasurementBudget 60000      //Higher the time , higher the accuracy
#define Timeout 200
#define ContInterval 40 //inter-measurement period in milliseconds determining how often the sensor takes a measurement.


uint8_t Mode=0;

//wall following parameters
int16_t error=0,Lerror=0,Rerror=0,last_error=0,Rlast_error=0,Llast_error=0,adj=0;
uint8_t Kd=0, Kp=11;//4
uint16_t rspeed=210,lspeed=218;
//TOF readings2
uint16_t distanceR=0,distanceL=0,distanceRF=0,distanceLF=0,distanceRT=0,distanceLT=0;
bool rightFollow;bool leftFollow;
// //drive
int Rspeed; int Lspeed;


// Gyro
int16_t GyroZ;
int16_t angle;
#define modAngle 720

int time;


//encoders
#define rightcount TIM2->CNT
#define leftcount TIM3->CNT

//Floodfill Implement
uint8_t face=0; //N=0,E=1,S=2,W=3
#define wallThreshold 70
#define sidewallThreshold 150
#define frontwallThreshold 230
#define edge2cen 1015
#define cen2edge 300
#define backCount90 145

#define frontcount 120 
#define backcount180 110
uint8_t movdir=0; //the direction mouse should move (Absolute)   N=0,E=1,S=2,W=3




//FloodFill
const int size= 14;
const int Nbitval=0,Ebitval=1,Sbitval=2,Wbitval=3;
uint8_t tempN=0,tempE=0,tempS=0,tempW=0,tempDistance=0;
uint8_t currCell=0,Ncell=0,Ecell=0,Scell=0,Wcell=0,minCell=0;
bool updated=false;
bool stackNotempty= false;
uint16_t tempMazedata;
uint8_t N=0,E=0,S=0,W=0,R=0,C=0;
uint16_t stack[size*size];
uint16_t stackval;
uint8_t poprow,popcol;
int16_t pointer=-1;
uint16_t maze[size][size] { 
                            // {6,5,4,3,3,4,5,6},
                            // {5,4,3,2,2,3,4,5},
                            // {4,3,2,1,1,2,3,4},
                            // {3,2,1,0,0,1,2,3},
                            // {3,2,1,0,0,1,2,3},
                            // {4,3,2,1,1,2,3,4},
                            // {5,4,3,2,2,3,4,5},
                            // {6,5,4,3,3,4,5,6}};

                            {12,11,10,9,8,7,6,6,7,8,9,10,11,12},
                            {11,10,9,8,7,6,5,5,6,7,8,9,10,11},
                            {10,9,8,7,6,5,4,4,5,6,7,8,9,10},
                            {9,8,7,6,5,4,3,3,4,5,6,7,8,9},
                            {8,7,6,5,4,3,2,2,3,4,5,6,7,8},
                            {7,6,5,4,3,2,1,1,2,3,4,5,6,7},
                            {6,5,4,3,2,1,0,0,1,2,3,4,5,6},
                            {6,5,4,3,2,1,0,0,1,2,3,4,5,6},
                            {7,6,5,4,3,2,1,1,2,3,4,5,6,7},
                            {8,7,6,5,4,3,2,2,3,4,5,6,7,8},
                            {9,8,7,6,5,4,3,3,4,5,6,7,8,9},
                            {10,9,8,7,6,5,4,4,5,6,7,8,9,10},
                            {11,10,9,8,7,6,5,5,6,7,8,9,10,11},
                            {12,11,10,9,8,7,6,6,7,8,9,10,11,12}};

uint8_t backMaze[size][size] { 
                            // {0,1,2,3,4,5,6,7},
                            // {1,2,3,4,5,6,7,8},
                            // {2,3,4,5,6,7,8,9},
                            // {3,4,5,6,7,8,9,10},
                            // {4,5,6,7,8,9,10,11},
                            // {5,6,7,8,9,10,11,12},
                            // {6,7,8,9,10,11,12,13},
                            // {7,8,9,10,11,12,13,14}                  
                            // };

                            {0,1,2,3,4,5,6,7,8,9,10,11,12,13},
                            {1,2,3,4,5,6,7,8,9,10,11,12,13,14},
                            {2,3,4,5,6,7,8,9,10,11,12,13,14,15},
                            {3,4,5,6,7,8,9,10,11,12,13,14,15,16},
                            {4,5,6,7,8,9,10,11,12,13,14,15,16,17},
                            {5,6,7,8,9,10,11,12,13,14,15,16,17,18},
                            {6,7,8,9,10,11,12,13,14,15,16,17,18,19},
                            {7,8,9,10,11,12,13,14,15,16,17,18,19,20},
                            {8,9,10,11,12,13,14,15,16,17,18,19,20,21},
                            {9,10,11,12,13,14,15,16,17,18,19,20,21,22},
                            {10,11,12,13,14,15,16,17,18,19,20,21,22,23},
                            {11,12,13,14,15,16,17,18,19,20,21,22,23,24},
                            {12,13,14,15,16,17,18,19,20,21,22,23,24,25},
                            {13,14,15,16,17,18,19,20,21,22,23,24,25,26}
                            };





#endif