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
