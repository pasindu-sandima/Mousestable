void floodfillSetup(){
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
}

void moveMouse(){
    if(face==0){
        if(movdir==0){}
        else if(movdir==1){
            if(N==1){
                frontAdjuster();
            }
            turnR();
            face=1;}
        else if(movdir==2){
            if(N==1){
                frontAdjuster();
            }
            if(E==1){
                turnR();
                frontAdjuster();
                turnR();
            }
            else if(W==1){
                turnL();
                frontAdjuster();
                turnL();
            }
            else{
                turn180();
            }
            face=2;}
        else if(movdir==3){
            if(N==1){
                frontAdjuster();
            }
            turnL();
            face=3;}
    }
    else if(face==1){
        if(movdir==0){
            if(E==1){
                frontAdjuster();
            }
            turnL();
            face=0;
        }
        else if(movdir==1){}
        else if(movdir==2){
            if(E==1){
                frontAdjuster();
            }
            turnR();
            face=2;
        }
        else if(movdir==3){
            if(E==1){
                frontAdjuster();
            }
            if(S==1){
                turnR();
                frontAdjuster();
                turnR();
            }
            else if(N==1){
                turnL();
                frontAdjuster();
                turnL();
            }
            else{
                turn180();
            }
            face=3;
        }
    }
    else if(face==2){
        if(movdir==0){
            if(S==1){
                frontAdjuster();
            }
            if(W==1){
                turnR();
                frontAdjuster();
                turnR();
            }
            else if(E==1){
                turnL();
                frontAdjuster();
                turnL();
            }
            else{
                turn180();
            }
            face=0;
        }
        else if(movdir==1){
            if(S==1){
                frontAdjuster();
            }
            turnL();
            face=1;}
        else if(movdir==2){}
        else if(movdir==3){
            if(S==1){
                frontAdjuster();
            }
            turnR();
            face=3;}
    }
    else if(face==3){
        if(movdir==0){
            if(W==1){
                frontAdjuster();
            }
            turnR();
            face=0;}
        else if(movdir==1){
            if(W==1){
                frontAdjuster();
            }
            if(S==1){
                turnL();
                frontAdjuster();
                turnL();
            }
            else if(N==1){
                turnR();
                frontAdjuster();
                turnR();
            }
            else{
                turn180();
            }
            face=1;}
        else if(movdir==2){
            if(W==1){
                frontAdjuster();
            }
            turnL();
            face=2;}
        else if(movdir==3){}
    }
    moveCell();
}

void getWalldata(){
    if(face==0){
            if(getDistance(1)<wallThreshold){E=1;}
            else{E=0;}
            if(getDistance(6)<wallThreshold){W=1;}
            else{W=0;}
            if((getDistance(2)<120)||(getDistance(5)<120)){N=1;}
            else{N=0;}
            S=0;
        }
    else if(face==1){
        if(getDistance(1)<wallThreshold){S=1;}
        else{S=0;}
        if(getDistance(6)<wallThreshold){N=1;}
        else{N=0;}
        if((getDistance(2)<120)||(getDistance(5)<120)){E=1;}
        else{E=0;}
        W=0;
    }
    else if(face==2){
        if(getDistance(1)<wallThreshold){W=1;}
        else{W=0;}
        if(getDistance(6)<wallThreshold){E=1;}
        else{E=0;}
        if((getDistance(2)<120)||(getDistance(5)<120)){S=1;}
        else{S=0;}
        N=0;
    }
    else if(face==3){
        if(getDistance(1)<wallThreshold){N=1;}
        else{N=0;}
        if(getDistance(6)<wallThreshold){S=1;}
        else{S=0;}
        if((getDistance(2)<120)||(getDistance(5)<120)){W=1;}
        else{W=0;}
        E=0;
    }
}

void floodfill(){
    R=0,C=0;
    while(true){
        getWalldata();
        updateWalldata(R,C);  //Walls get updated in the array
        updateCell(R,C);  //Runs modified floodfill and updates distances
        printMaze();
        movetoFloodfill();  //Updates R and C
        moveMouse();           //Turns mouse to correct direction
        readDistancedata(R,C);
        if(tempDistance==0){break;}
    }
}

void center(){
    if((R==size/2)&&(C==size/2)){
        if(face==2){
            N=1,E=0,S=0,W=1;            
            updateWalldata(R,C-1);
            N=0,E=0,S=1,W=1;
            updateWalldata(R-1,C-1);
            N=0,E=1,S=1,W=0;
            updateWalldata(R-1,C);
            N=0,E=1,S=0,W=0;
            updateWalldata(R,C);
        }
        else if(face==3){
            N=1,E=0,S=0,W=1;            
            updateWalldata(R,C-1);
            N=0,E=0,S=1,W=1;
            updateWalldata(R-1,C-1);
            N=0,E=1,S=1,W=0;
            updateWalldata(R-1,C);
            N=1,E=0,S=0,W=0;
            updateWalldata(R,C);   
        }
    }
    else if((R==size/2)&&(C==(size/2)-1)){
        if(face==1){
            N=1,E=1,S=0,W=0;
            updateWalldata(R,C+1);            
            N=0,E=0,S=1,W=1;
            updateWalldata(R-1,C);
            N=0,E=1,S=1,W=0;
            updateWalldata(R-1,C+1);
            N=1,E=0,S=0,W=0;            
            updateWalldata(R,C);
        }
        else if(face==2){
            N=1,E=1,S=0,W=0;
            updateWalldata(R,C+1);            
            N=0,E=0,S=1,W=1;
            updateWalldata(R-1,C);
            N=0,E=1,S=1,W=0;
            updateWalldata(R-1,C+1);
            N=0,E=0,S=0,W=1;            
            updateWalldata(R,C);            
        }
    }
    else if((R==(size/2)-1)&&(C==(size/2)-1)){
        if(face==1){
            N=1,E=1,S=0,W=0;
            updateWalldata(R+1,C+1);
            N=1,E=0,S=0,W=1;            
            updateWalldata(R+1,C);            
            N=0,E=1,S=1,W=0;
            updateWalldata(R,C+1);
            N=0,E=0,S=1,W=0;
            updateWalldata(R,C);
        }
        else if(face==0){
            N=1,E=1,S=0,W=0;
            updateWalldata(R+1,C+1);
            N=1,E=0,S=0,W=1;            
            updateWalldata(R+1,C);
            N=0,E=1,S=1,W=0;
            updateWalldata(R,C+1);
            N=0,E=0,S=0,W=1;
            updateWalldata(R,C);                        
        }
    }
    else if((R==(size/2)-1)&&(C==size/2)){
        if(face==0){
            N=1,E=1,S=0,W=0;
            updateWalldata(R+1,C);
            N=1,E=0,S=0,W=1;            
            updateWalldata(R+1,C-1);
            N=0,E=0,S=1,W=1;
            updateWalldata(R,C-1);
            N=0,E=1,S=0,W=0;
            updateWalldata(R,C);
        }
        else if(face==3){
            N=1,E=1,S=0,W=0;
            updateWalldata(R+1,C);
            N=1,E=0,S=0,W=1;            
            updateWalldata(R+1,C-1);
            N=0,E=0,S=1,W=1;
            updateWalldata(R,C-1);
            N=0,E=0,S=1,W=0;
            updateWalldata(R,C);            
        }
    }
    updateCell((size/2)+1,(size/2)+1);
    updateCell((size/2)+1,(size/2));
    updateCell((size/2)+1,(size/2)-1);
    updateCell((size/2)+1,(size/2)-2);
    updateCell((size/2)-2,(size/2)+1);
    updateCell((size/2)-2,(size/2));
    updateCell((size/2)-2,(size/2)-1);
    updateCell((size/2)-2,(size/2)-2);
    updateCell((size/2),(size/2)+1);
    updateCell((size/2)-1,(size/2)+1);
    updateCell((size/2),(size/2)-2);
    updateCell((size/2)-1,(size/2)-2);
}

void backFloodfill(){
    for(int i=1;i+1<size;i++){
        for(int j=1;j+1<size;j++){
            backupdateCell(i,j);
        }
    }
    backprintMaze();
    movetoStart();
    moveMouse();
    while(true){
        getWalldata();
        updateWalldata(R,C);  //Walls get updated in the array
        updateCell(R,C);  //Runs modified floodfill and updates distances
        backupdateCell(R,C);
        backprintMaze();
        movetoStart();  //Updates R and C
        moveMouse();           //Turns mouse to correct direction
        if(backMaze[R][C]==0){break;}
    }

}


