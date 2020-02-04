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

