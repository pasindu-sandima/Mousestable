void wallFollowR(){
        Kp=2,Kd=5;
        distanceR=getDistance(3);
        if(distanceR>160){
                distanceR=100;
        }
        error = distanceR-100;
        adj = Kp*error + Kd*(error-last_error);
        last_error = error;
        Rspeed = rspeed;
        Lspeed = lspeed;
        if (adj>0) {      
                Lspeed += adj;
                Rspeed -= adj/2;
        }
        else{
                Rspeed -= adj;
                Lspeed += adj/2;
        }
        if (Rspeed>255){
                Rspeed = 255;
        }
        if (Lspeed>255){
                Lspeed = 255;
        }
        if (Rspeed<0){
                Rspeed =0;
        }
        if (Lspeed<0){
                Lspeed = 0;
        }
        drive(Rspeed,Lspeed);
}

void wallFollowL(){
        Kp=2,Kd=5;
        distanceL=getDistance(4);
        if(distanceL>160){
                distanceL=100;
        }
        error = distanceL-100;
        adj = Kp*error + Kd*(error-last_error);
        last_error = error;
        Rspeed = rspeed;
        Lspeed = lspeed;
        if (adj>0) {      
                Rspeed += adj;
                Lspeed -= adj/2;
        }
        else{
                Lspeed -= adj;
                Rspeed += adj/2;
        }
        if (Rspeed>255){
                Rspeed = 255;
        }
        if (Lspeed>255){
                Lspeed = 255;
        }
        if (Rspeed<0){
                Rspeed =0;
        }
        if (Lspeed<0){
                Lspeed = 0;
        }
        drive(Rspeed,Lspeed);
}



void wallFollowRNew(){
        Kp=6,Kd=20;
        distanceR=getDistance(1);
        error = distanceR-55;
        adj = Kp*error + Kd*(error-last_error);
        last_error = error;
        Rspeed = rspeed;
        Lspeed = lspeed;
        if (adj>0) {      
                Lspeed += adj;
                Rspeed -= adj/2;
        }
        else{
                Rspeed -= adj;
                Lspeed += adj/2;
        }
        if (Rspeed>255){
                Rspeed = 255;
        }
        if (Lspeed>255){
                Lspeed = 255;
        }
        if (Rspeed<0){
                Rspeed =0;
        }
        if (Lspeed<0){
                Lspeed = 0;
        }
        drive(Rspeed,Lspeed);
}
void wallFollowLNew(){
        Kp=6,Kd=20;
        distanceL=getDistance(6);
        error = distanceL-55;
        adj = Kp*error + Kd*(error-last_error);
        last_error = error;
        Rspeed = rspeed;
        Lspeed = lspeed;
        if (adj>0) {      
                Rspeed += adj;
                Lspeed -= adj/2;
        }
        else{
                Lspeed -= adj;
                Rspeed += adj/2;
        }
        if (Rspeed>255){
                Rspeed = 255;
        }
        if (Lspeed>255){
                Lspeed = 255;
        }
        if (Rspeed<0){
                Rspeed =0;
        }
        if (Lspeed<0){
                Lspeed = 0;
        }
        drive(Rspeed,Lspeed);
}



void frontAdjuster(){
        for(int i=0;i<40;i++){
                Kp=3,Kd=0;
                distanceR=getDistance(2);
                distanceL=getDistance(5);
                distanceR+=distanceL;
                Rerror= distanceR-160;
                // Lerror= distanceL-75;
                Rspeed= Kp*Rerror + Kd*(Rerror-Rlast_error);
                Lspeed= Kp*Lerror + Kd*(Lerror-Llast_error);
                drive(Rspeed,Rspeed);
                Rlast_error=Rerror;
                Llast_error=Lerror;
        }
}
void frontAdjuster180(){
        for(int i=0;i<20;i++){
                Kp=10,Kd=10;
                distanceR=getDistance(2);
                distanceL=getDistance(5);
                distanceR+=distanceL;
                Rerror= distanceR-120;
                // Lerror= distanceL-80;
                Rspeed= Kp*Rerror + Kd*(Rerror-Rlast_error);
                // Lspeed= Kp*Lerror + Kd*(Lerror-Llast_error);
                drive(Rspeed,Rspeed);
                Rlast_error=Rerror;
                // Llast_error=Lerror;
        }
}