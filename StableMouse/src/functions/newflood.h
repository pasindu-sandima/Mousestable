void floodfillNew(){
    updateWalldata(R,C);
    updateCell(R,C);
    movetoFloodfill();
    while(true){
        centertoedge();
        readDistancedata(R,C);
        if(tempDistance==0){
            break;
        }
        digitalWrite(Buzzer_Pin,HIGH);
        getWalldataNew();                   //read maze data and update walls for NESW for "fast run"
        updateWalldata(R,C);
        updateCell(R,C);
        movetoFloodfill();
        digitalWrite(Buzzer_Pin,LOW);
        edgetocenter();
        // brake();
        // printMaze();
        moveMouseNew();
    }


}

void moveMouseNew(){
    if(face==0){
        if(movdir==0){}
        else if(movdir==1){
            if(N==1){
                frontAdjuster();
            }
            // countForward(frontcount,210,218);
            turnR();
            // countBackward(backCount90,210,218);

            face=1;}
        else if(movdir==2){
            // countForward(100,210,218);
            if(N==1){
                frontAdjuster();
            }
            // countForward(frontcount,210,218);
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
            // countBackward(backcount180,210,218);
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
}

void edgetocenter(){
    rightFollow=false,leftFollow=false;
    if((face==0)&&(E==1)){rightFollow=true;}
    else if((face==1)&&(S==1)){rightFollow=true;}
    else if((face==2)&&(W==1)){rightFollow=true;}
    else if((face==3)&&(N==1)){rightFollow=true;}
    if((face==0)&&(W==1)){leftFollow=true;}
    else if((face==1)&&(N==1)){leftFollow=true;}
    else if((face==2)&&(E==1)){leftFollow=true;}
    else if((face==3)&&(S==1)){leftFollow=true;}
    rightcount=0;
    // leftcount=0;
    if(leftFollow){
        while(true){
            wallFollowL();
            if(rightcount>edge2cen){
                break;
            }
            // if(leftcount>cen2edge){
            //     break;
            // }
        }
    }
    else if(rightFollow){
        while(true){
            wallFollowR();
            if(rightcount>edge2cen){
                break;
            }
            // if(leftcount>cen2edge){
            //     break;
            // }
        }
    }
    else{
        driveForward();
        while(true){
            if(rightcount>edge2cen){
                break;
            }
            // if(leftcount>edge2cen){
            //     break;
            // }
        }
    }
}

void centertoedge(){
    rightFollow=false,leftFollow=false;
    if((face==0)&&(E==1)){rightFollow=true;}
    else if((face==1)&&(S==1)){rightFollow=true;}
    else if((face==2)&&(W==1)){rightFollow=true;}
    else if((face==3)&&(N==1)){rightFollow=true;}
    if((face==0)&&(W==1)){leftFollow=true;}
    else if((face==1)&&(N==1)){leftFollow=true;}
    else if((face==2)&&(E==1)){leftFollow=true;}
    else if((face==3)&&(S==1)){leftFollow=true;}
    rightcount=0;
    
    if(leftFollow){
        while(true){
            wallFollowLNew();
            if(rightcount>cen2edge){
                break;
            }
            // if(leftcount>cen2edge){
            //     break;
            // }
        }
    }
    else if(rightFollow){
        while(true){
            wallFollowRNew();
            if(rightcount>cen2edge){
                break;
            }
            // if(leftcount>cen2edge){
            //     break;
            // }
        }
    }
    else{
        driveForward();
        while(true){
            if(rightcount>cen2edge){
                break;
            }
        }
    }

}

void getWalldataNew(){
    if(face==0){
            if(getDistance(3)<sidewallThreshold){E=1;}
            else{E=0;}
            if(getDistance(4)<sidewallThreshold){W=1;}
            else{W=0;}
            if((getDistance(2)<frontwallThreshold)||(getDistance(5)<frontwallThreshold)){N=1;}
            else{N=0;}
            S=0;
        }
    else if(face==1){
        if(getDistance(3)<sidewallThreshold){S=1;}
        else{S=0;}
        if(getDistance(4)<sidewallThreshold){N=1;}
        else{N=0;}
        if((getDistance(2)<frontwallThreshold)||(getDistance(5)<frontwallThreshold)){E=1;}
        else{E=0;}
        W=0;
    }
    else if(face==2){
        if(getDistance(3)<sidewallThreshold){W=1;}
        else{W=0;}
        if(getDistance(4)<sidewallThreshold){E=1;}
        else{E=0;}
        if((getDistance(2)<frontwallThreshold)||(getDistance(5)<frontwallThreshold)){S=1;}
        else{S=0;}
        N=0;
    }
    else if(face==3){
        if(getDistance(3)<sidewallThreshold){N=1;}
        else{N=0;}
        if(getDistance(4)<sidewallThreshold){S=1;}
        else{S=0;}
        if((getDistance(2)<frontwallThreshold)||(getDistance(5)<frontwallThreshold)){W=1;}
        else{W=0;}
        E=0;
    }
}


void backFloodfillNew(){
    for(int i=1;i+1<size;i++){
        for(int j=1;j+1<size;j++){
            backupdateCell(i,j);
        }
    }
    backprintMaze();
    movetoStart();
    moveMouseNew();
    while(true){
        centertoedge();
        if(backMaze[R][C]==0){break;}
        digitalWrite(Buzzer_Pin,HIGH);
        getWalldataNew();
        updateWalldata(R,C);
        backupdateCell(R,C);
        movetoStart();
        digitalWrite(Buzzer_Pin,LOW);
        edgetocenter();
        moveMouseNew();
    }


}