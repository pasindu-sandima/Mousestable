TwoWire Wire1(PB11,PB10);
MPU6050 Gyro(Wire1);
void initGyro(){
    Gyro.begin();
    Gyro.calcGyroOffsets(false);
}

void getGyro(){
    Gyro.update();
    GyroZ = Gyro.getAngleZ();
    GyroZ = (((GyroZ % modAngle) + modAngle) % modAngle);
    GyroZ = map(GyroZ,0,modAngle,360,0);
}