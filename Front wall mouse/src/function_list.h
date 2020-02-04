//TOF functions 
void tofSetup();
void measure();
int getDistance(uint8_t Sensor);
void printDistance();




//declaration of pinModes
void pinModes();

//drive
void drive(int Rspeed,int Lspeed);
void brake();
void turnR();
void turnL();
void turn180();
void countForward(uint16_t count, int Rspeed,int Lspeed);
void moveCell();
void driveForward();
void countBackward(uint16_t count, int Rspeed,int Lspeed);




//WallFollow
void wallFollowL();
void wallFollowR();
void wallFollowLNew();
void wallFollowRNew();
void frontAdjuster();


//Others
void Buzzer(uint16_t time_delay);
void init_hardware_timer_version(void);


//Gyro
void initGyro();
void getGyro();


//New Flood
void floodfillNew();
void moveMouseNew();
void edgetocenter();
void centertoedge();
void getWalldataNew();





//Flood Fill
void floodfillSetup();
void moveMouse();
void backFloodfill();
void floodfill();
void getWalldata();
void center();

    //maze
    void updateCell(uint8_t Nrow,uint8_t Ncol);
    void updateWalldata(uint8_t Nrow,uint8_t Ncol);
    void readMazedata(uint8_t Nrow,uint8_t Ncol);      //tempDistance,tempN,....
    void readDistancedata(uint8_t Nrow,uint8_t Ncol);     //updates tempDistance
    int getMin(uint8_t w,uint8_t x,uint8_t y,uint8_t z);
    void checkMinDisUp(uint8_t Nrow,uint8_t Ncol);
    void printMaze();
    void movetoFloodfill();

    //stack
    bool isStackempty();      //returns true if the stack is empty
    void stackPush(uint8_t Nrow,uint8_t Ncol);      //parameters row,col
    void stackPop();           //returns row,col
    void pushNeighbours(uint8_t Nrow,uint8_t Ncol);
    void pushOpenneighbours(uint8_t Nrow,uint8_t Ncol);


    //backTrack
    void backcheckMinDisUp(uint8_t Nrow,uint8_t Ncol);
    void backpushNeighbours(uint8_t Nrow,uint8_t Ncol);
    void backpushOpenneighbours(uint8_t Nrow,uint8_t Ncol);
    void backprintMaze();
    void backupdateCell(uint8_t Nrow,uint8_t Ncol);
    void movetoStart();







    