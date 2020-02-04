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
  Serial.print(face);
  Serial.print(" , ");
  Serial.print(R);
  Serial.print(" , ");
  Serial.println(C);

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
    movdir=0;
  }
  else if ((minCell==Ecell)&&(Ecell<255)){
    C=C+1;
    movdir=1;
  }
  else if ((minCell==Scell)&&(Scell<255)){
    R=R-1;
    movdir=2;
  }
  else if ((minCell==Wcell)&&(Wcell<255)){
    C=C-1;
    movdir=3;
  }

  
}
