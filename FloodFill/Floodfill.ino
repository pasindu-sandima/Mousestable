// #include "mm_func.h"

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
uint8_t inputset[45][4] { {0,1,1,1},
                          {0,0,0,1},
                          {1,0,0,1},
                          {1,0,1,0},
                          {0,1,1,0},
                          {1,0,0,1},
                          {1,1,0,0},
                          {0,1,0,1},
                          {0,0,1,1},
                          {0,1,1,0}, 
                          {1,0,0,1},
                          {1,0,0,0},
                          {1,0,1,0},
                          {1,1,0,0},
                          {0,1,0,0},
                          {0,0,1,1},
                          {0,0,1,0},
                          {1,0,0,1},
                          {0,1,1,0},
                          {0,1,0,0},
                          {0,1,0,1},
                          {1,0,0,1},
                          {0,1,1,0},
                          {0,1,0,0},
                          {0,1,0,1},
                          {1,1,0,0},
                          {0,0,1,1},
                          {0,1,0,1},
                          {0,1,0,1},
                          {1,1,0,0},
                          {1,0,0,1},
                          {0,1,1,0},
                          {0,0,1,1},
                          {0,1,0,1},
                          {1,1,0,0},
                          {1,0,0,1},
                          {0,1,0,1},
                          {0,1,0,1},
                          {0,1,0,1},
                          {0,0,0,1},
                          {1,1,0,0},
                          {0,1,1,0},
                          {0,0,1,1},
                          {0,0,0,0}};
                        

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




void setup(){
  Serial1.begin(9600);
  for (int n=0; n<size;n++){
    for (int m=0; m<size;m++){
      maze[n][m] = (maze[n][m]<<8);

    }
  }
  E=0,W=0;
  for(C=1;C<size-1;C++){
    R=size-1;
    N=1,S=0;
    updateWalldata(R,C);
    R=0;
    N=0,S=1;
    updateWalldata(R,C);
  }
  N=0,S=0;
  for(R=1;R<size-1;R++){
    C=size-1;
    E=1,W=0;
    updateWalldata(R,C);
    C=0;
    E=0,W=1;
    updateWalldata(R,C);
  }
  R=0;C=0;N=0;E=0;S=1;W=1;
  updateWalldata(R,C);
  R=0;C=size-1;N=0;E=1;S=1;W=0;
  updateWalldata(R,C);
  R=size-1;C=0;N=1;E=0;S=0;W=1;
  updateWalldata(R,C);
  R=size-1;C=size-1;N=1;E=1;S=0;W=0;
  updateWalldata(R,C);

  printMaze();
  R=0;C=0;





}


void loop(){
  uint8_t inputnum = 0;
  while(true){
    N = inputset[inputnum][0];
    E= inputset[inputnum][1];
    S=inputset[inputnum][2];
    W=inputset[inputnum][3];
    updateWalldata(R,C);
    updateCell(R,C);
    // Serial1.println("Before movetoFloodfill");
    movetoFloodfill();
    // Serial1.println("Before printMaze");
    // // printMaze();
    // Serial1.println("");
    // Serial1.print(R);
    // Serial1.print(" ");
    // Serial1.println(C);
    Serial1.println("ready"); 
    readDistancedata(R,C);
    
    if(tempDistance==0){
      break;
    }
    inputnum++;
    
  }
  inputnum++;

  printMaze();
  Serial1.println(" Done ");

  //0 walls
  if(R==size/2){
    if(C==(size/2)-1){
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R,C);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R,C+1);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R-1,C+1);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R-1,C);
        inputnum++;
        updateCell(R+1,C);
        updateCell(R+1,C+1);
        updateCell(R-2,C);
        updateCell(R-2,C+1);
        updateCell(R,C+2);
        updateCell(R-1,C+2);
        updateCell(R,C-1);
        updateCell(R-1,C-1);
    }
    else{
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R,C);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R-1,C);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R-1,C-1);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R,C-1);
        inputnum++;
        updateCell(R+1,C+1);
        updateCell(R+1,C);
        updateCell(R+1,C-1);
        updateCell(R+1,C-2);
        updateCell(R,C-2);
        updateCell(R-1,C-2);
        updateCell(R-2,C-2);
        updateCell(R-2,C-1);
        updateCell(R-2,C);
        updateCell(R-2,C+1);
        updateCell(R-1,C+1);
        updateCell(R,C+1);
        updateCell(R+1,C+1);

    }
  }
  else{
    if(C==size/2){
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R,C);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R,C-1);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R+1,C-1);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R+1,C);
        inputnum++;
        updateCell(R+2,C);
        updateCell(R+2,C-1);
        updateCell(R-1,C);
        updateCell(R-1,C-1);
        updateCell(R,C+1);
        updateCell(R+1,C+1);
        updateCell(R,C-2);
        updateCell(R+1,C-2);
    }
    else{
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R,C);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R+1,C);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R+1,C+1);
        inputnum++;
        N = inputset[inputnum][0];
        E= inputset[inputnum][1];
        S=inputset[inputnum][2];
        W=inputset[inputnum][3];
        updateWalldata(R,C+1);
        inputnum++;
        updateCell(R+2,C);
        updateCell(R+2,C+1);
        updateCell(R-1,C);
        updateCell(R-1,C+1);
        updateCell(R,C+2);
        updateCell(R+1,C+2);
        updateCell(R,C-1);
        updateCell(R+1,C-1);

    }
  }


  printMaze();
  
  for(int i=1;i+1<size;i++){
    for(int j=1;j+1<size;j++){
      backupdateCell(i,j);
    }
  }
  Serial1.println("");

  backprintMaze();

  while(true){}


}


void updateCell(uint8_t Nrow,uint8_t Ncol){
    checkMinDisUp(Nrow,Ncol);
    pushNeighbours(Nrow,Ncol);
    // Serial1.println(pointer);
    isStackempty();
    while(stackNotempty){
      // Serial1.println(pointer);
      stackPop();
      checkMinDisUp(poprow,popcol);
      if(updated){        
        pushOpenneighbours(poprow,popcol);
      }
      isStackempty();
    }

}

bool isStackempty(){      //returns true if the stack is empty
  if(pointer<0){
    stackNotempty=false;
    return true;
  }
  else{
    stackNotempty=true;
    return false;
  }
}

void stackPush(uint8_t Nrow,uint8_t Ncol){      //parameters row,col
  if(pointer+1<size*size){
    stackval=0;
    stackval|=(((uint16_t)Nrow<<8)|Ncol);
    pointer++;
    stack[pointer]=stackval;
  }
}

void stackPop(){           //returns row,col
  if(pointer>-1){
    stackval = stack[pointer];
    popcol=(stackval&(0x00FF));
    poprow=(uint8_t)((stackval&0xFF00)>>8);
    pointer--;
  }
  else{
    poprow=0,popcol=0;
  }
}

void updateWalldata(uint8_t Nrow,uint8_t Ncol){        //updates wall data in the maze array
  maze[Nrow][Ncol]|=((N<<Nbitval)|(E<<Ebitval)|(S<<Sbitval)|(W<<Wbitval));
  if((Nrow+1<size)&&(N==1)){
    maze[Nrow+1][Ncol]|=(N<<Sbitval);
  }
  if((Ncol+1<size)&&(E==1)){
    maze[Nrow][Ncol+1]|=(E<<Wbitval);
  }
  if((Nrow>0)&&(S==1)){
    maze[Nrow-1][Ncol]|=(S<<Nbitval);
  }
  if((Ncol>0)&&(W==1)){
    maze[Nrow][Ncol-1]|=(W<<Ebitval);
  }
}

void readMazedata(uint8_t Nrow,uint8_t Ncol){      //tempDistance,tempN,....
  tempMazedata = maze[Nrow][Ncol]; 
  tempDistance = (uint8_t)((tempMazedata&0xFF00)>>8);
  tempN = (uint8_t)((tempMazedata&0x0001));
  tempE = (uint8_t)((tempMazedata&0x0002)>>Ebitval);
  tempS = (uint8_t)((tempMazedata&0x0004)>>Sbitval);
  tempW = (uint8_t)((tempMazedata&0x0008)>>Wbitval);
}

void readDistancedata(uint8_t Nrow,uint8_t Ncol){     //updates tempDistance
  tempMazedata = maze[Nrow][Ncol]; 
  tempDistance = (uint8_t)((tempMazedata&0xFF00)>>8);
}

int getMin(uint8_t w,uint8_t x,uint8_t y,uint8_t z){
  if((w<=x)&&(w<=y)&&(w<=z)){
    return w;
  }
  else if((x<=w)&&(x<=y)&&(x<=z)){
    return x;
  }
  else if((y<=x)&&(y<=w)&&(y<=z)){
    return y;
  }
  else if((z<=w)&&(z<=y)&&(z<=x)){
    return z;
  }
}

void checkMinDisUp(uint8_t Nrow,uint8_t Ncol){
  readMazedata(Nrow,Ncol);
  currCell=tempDistance;
  if(tempN==0){
    readDistancedata(Nrow+1,Ncol);
    Ncell=tempDistance;
  }
  else{
    Ncell=255;
  }
  if(tempE==0){
    readDistancedata(Nrow,Ncol+1);
    Ecell=tempDistance;
  }
  else{
    Ecell=255;
  }
  if(tempS==0){
    readDistancedata(Nrow-1,Ncol);
    Scell=tempDistance;
  }
  else{
    Scell=255;
  }
  if(tempW==0){
    readDistancedata(Nrow,Ncol-1);
    Wcell=tempDistance;
  }
  else{
    Wcell=255;
  }
  minCell=getMin(Ncell,Ecell,Scell,Wcell)+1;
  if(currCell==minCell){
    updated = false;
  }
  else{
    updated = true;
    currCell = minCell;
    maze[Nrow][Ncol]= ((maze[Nrow][Ncol])&0x00FF)|((uint16_t)currCell<<8);    
  }


}

void printMaze(){
  const char* wall1 = "---+" ;
  const char* wall2 = " | ";
  const char* nowall1 = "   +";
  const char* nowall2 = "   ";
  for (int8_t Row =(size-1); Row >= 0; Row--) {
    Serial1.print("+");
    for (uint8_t i = 0; i <= 1; i++){         
      for (uint8_t Col = 0; Col <= (size-1); Col++) {
        readMazedata(Row,Col);
        if (i==0){                           //print North wall
          if (tempN==1){
            Serial1.print("---+");
            
          }
          else if (tempN==0){
            Serial1.print("   +");
          }
        }
        
        else if (i==1){                      //print West wall and distance
          readDistancedata(Row,Col);
          if(tempDistance<10){
            if (tempW==1){
              Serial1.print("| ");
              Serial1.print(tempDistance);
              Serial1.print(" ");
              
            }
            else if (tempW==0){
              Serial1.print("  ");
              Serial1.print(tempDistance);
              Serial1.print(" ");
            }
          }
          else{
             if (tempW==1){
              Serial1.print("| ");
              Serial1.print(tempDistance);
              Serial1.print("");
              
            }
            else if (tempW==0){
              Serial1.print("  ");
              Serial1.print(tempDistance);
              Serial1.print("");
            }
          }
          }
          if (Col == (size-1)){                 //end of one row
            if (i==0){
              Serial1.println();                     
            }
            else{
              Serial1.print("| ");
              Serial1.println();
            }
          }  
        
      }           
    }
    if (Row==0){                                                //end of the map
      for(uint8_t i=0;i<size;i++){
        Serial1.print("+---");
      }
      Serial1.print("+");
    }
  }  
}

void movetoFloodfill(){
  readMazedata(R,C);
  currCell=tempDistance;
  if(tempN==0){
    readDistancedata(R+1,C);
    Ncell=tempDistance;
  }
  else{
    Ncell=255;
  }
  if(tempE==0){
    readDistancedata(R,C+1);
    Ecell=tempDistance;
  }
  else{
    Ecell=255;
  }
  if(tempS==0){
    readDistancedata(R-1,C);
    Scell=tempDistance;
  }
  else{
    Scell=255;
  }
  if(tempW==0){
    readDistancedata(R,C-1);
    Wcell=tempDistance;
  }
  else{
    Wcell=255;
  }
  minCell=getMin(Ncell,Ecell,Scell,Wcell);

  if ((minCell==Ncell)&&(Ncell<255)){
    R=R+1;
  }
  else if ((minCell==Ecell)&&(Ecell<255)){
    C=C+1;
  }
  else if ((minCell==Scell)&&(Scell<255)){
    R=R-1;
  }
  else if ((minCell==Wcell)&&(Wcell<255)){
    C=C-1;
  }

  
}

void pushNeighbours(uint8_t Nrow,uint8_t Ncol){
  if(Nrow+1<size){
    if((Nrow+2==size/2)&&((Ncol==size/2)||(Ncol+1==size/2))){}
    else{
      stackPush(Nrow+1,Ncol);
    }
  }
  if(Ncol+1<size){
    if((Ncol+2==size/2)&&((Nrow==size/2)||(Nrow+1==size/2))){}
    else{
      stackPush(Nrow,Ncol+1);
    }
  }
  if(Nrow>0){
    if((Nrow-1==size/2)&&((Ncol==size/2)||(Ncol+1==size/2))){}
    else{
      stackPush(Nrow-1,Ncol);
    }
  }
  if(Ncol>0){
    if((Ncol-1==size/2)&&((Nrow==size/2)||(Nrow+1==size/2))){}
    else{
      stackPush(Nrow,Ncol-1);
    }
  }
}


void pushOpenneighbours(uint8_t Nrow,uint8_t Ncol){
  readMazedata(Nrow,Ncol);
  if((Nrow+1<size)&&(tempN==0)){
    if((Nrow+2==size/2)&&((Ncol==size/2)||(Ncol+1==size/2))){}
    else{
      stackPush(Nrow+1,Ncol);
    }
  }
  if((Ncol+1<size)&&(tempE==0)){
    if((Ncol+2==size/2)&&((Nrow==size/2)||(Nrow+1==size/2))){}
    else{
      stackPush(Nrow,Ncol+1);
    }
  }
  if((Nrow>0)&&(tempS==0)){
    if((Nrow-1==size/2)&&((Ncol==size/2)||(Ncol+1==size/2))){}
    else{
      stackPush(Nrow-1,Ncol);
    }
  }
  if((Ncol>0)&&(tempW==0)){
    if((Ncol-1==size/2)&&((Nrow==size/2)||(Nrow+1==size/2))){}
    else{
      stackPush(Nrow,Ncol-1);
    }
  }
}






void backcheckMinDisUp(uint8_t Nrow,uint8_t Ncol){
  readMazedata(Nrow,Ncol);
  currCell=backMaze[Nrow][Ncol];
  if(tempN==0){
    Ncell=backMaze[Nrow+1][Ncol];
  }
  else{
    Ncell=255;
  }
  if(tempE==0){
    Ecell=backMaze[Nrow][Ncol+1];
  }
  else{
    Ecell=255;
  }
  if(tempS==0){
    Scell=backMaze[Nrow-1][Ncol];
  }
  else{
    Scell=255;
  }
  if(tempW==0){
    Wcell=backMaze[Nrow][Ncol-1];
  }
  else{
    Wcell=255;
  }
  minCell=getMin(Ncell,Ecell,Scell,Wcell)+1;
  if(currCell==minCell){
    updated = false;
  }
  else{
    updated = true;
    currCell = minCell;
    backMaze[Nrow][Ncol]= currCell;
  }


}

void backpushNeighbours(uint8_t Nrow,uint8_t Ncol){
  if(Nrow+1<size){
      stackPush(Nrow+1,Ncol);
  }
  if(Ncol+1<size){
      stackPush(Nrow,Ncol+1);
  }
  if(Nrow>0){
    if((Ncol==0)&&(Nrow==1)){}
    else{
      stackPush(Nrow-1,Ncol);
    }
  }
  if(Ncol>0){
    if((Ncol==1)&&(Nrow==0)){}    
    else{
      stackPush(Nrow,Ncol-1);
    }
  }
}

void backpushOpenneighbours(uint8_t Nrow,uint8_t Ncol){
  readMazedata(Nrow,Ncol);
  if((Nrow+1<size)&&(tempN==0)){
      stackPush(Nrow+1,Ncol);
  }
  if((Ncol+1<size)&&(tempE==0)){
      stackPush(Nrow,Ncol+1);
  }
  if((Nrow>0)&&(tempS==0)){
    if((Ncol==0)&&(Nrow==1)){}
    else{
      stackPush(Nrow-1,Ncol);
    }
  }
  if((Ncol>0)&&(tempW==0)){
    if((Ncol==1)&&(Nrow==0)){}    
    else{
      stackPush(Nrow,Ncol-1);
    }
  }
}

void backprintMaze(){
  const char* wall1 = "---+" ;
  const char* wall2 = " | ";
  const char* nowall1 = "   +";
  const char* nowall2 = "   ";
  for (int8_t Row =(size-1); Row >= 0; Row--) {
    Serial1.print("+");
    for (uint8_t i = 0; i <= 1; i++){         
      for (uint8_t Col = 0; Col <= (size-1); Col++) {
        readMazedata(Row,Col);
        if (i==0){                           //print North wall
          if (tempN==1){
            Serial1.print("---+");
            
          }
          else if (tempN==0){
            Serial1.print("   +");
          }
        }
        
        else if (i==1){                      //print West wall and distance
          readDistancedata(Row,Col);
          tempDistance=backMaze[Row][Col];
          if(tempDistance<10){
            if (tempW==1){
              Serial1.print("| ");
              Serial1.print(tempDistance);
              Serial1.print(" ");
              
            }
            else if (tempW==0){
              Serial1.print("  ");
              Serial1.print(tempDistance);
              Serial1.print(" ");
            }
          }
          else{
             if (tempW==1){
              Serial1.print("| ");
              Serial1.print(tempDistance);
              Serial1.print("");
              
            }
            else if (tempW==0){
              Serial1.print("  ");
              Serial1.print(tempDistance);
              Serial1.print("");
            }
          }
          }
          if (Col == (size-1)){                 //end of one row
            if (i==0){
              Serial1.println();                     
            }
            else{
              Serial1.print("| ");
              Serial1.println();
            }
          }  
        
      }           
    }
    if (Row==0){                                                //end of the map
      for(uint8_t i=0;i<size;i++){
        Serial1.print("+---");
      }
      Serial1.print("+");
    }
  }  
}

void backupdateCell(uint8_t Nrow,uint8_t Ncol){
    backcheckMinDisUp(Nrow,Ncol);
    backpushNeighbours(Nrow,Ncol);
    // Serial1.println(pointer);
    isStackempty();
    while(stackNotempty){
      // Serial1.println(pointer);
      stackPop();
      backcheckMinDisUp(poprow,popcol);
      if(updated){        
        backpushOpenneighbours(poprow,popcol);
      }
      isStackempty();
    }

}

void movetoStart(){
  readMazedata(R,C);
  currCell=backMaze[R][C];
  if(tempN==0){
    Ncell=backMaze[R+1][C];
  }
  else{
    Ncell=255;
  }
  if(tempE==0){
    Ecell=backMaze[R][C+1];
  }
  else{
    Ecell=255;
  }
  if(tempS==0){
    Scell=backMaze[R-1][C];
  }
  else{
    Scell=255;
  }
  if(tempW==0){
    Wcell=backMaze[R][C-1];
  }
  else{
    Wcell=255;
  }
  minCell=getMin(Ncell,Ecell,Scell,Wcell);

  if ((minCell==Ncell)&&(Ncell<255)){
    R=R+1;
  }
  else if ((minCell==Ecell)&&(Ecell<255)){
    C=C+1;
  }
  else if ((minCell==Scell)&&(Scell<255)){
    R=R-1;
  }
  else if ((minCell==Wcell)&&(Wcell<255)){
    C=C-1;
  }

  
}

