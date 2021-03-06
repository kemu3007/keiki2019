#include "bmx055.h"

BMX055::BMX055()
{
    xAccl = yAccl = zAccl = 0.0;
    xGyro = yGyro = zGyro = 0.0;
    xMag = yMag = zMag = 0;
    pitch = roll = yaw = 0.0;
}

void BMX055::init(){
    Wire.begin();
    MadgwickFilter.begin(5);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Accl);
    Wire.write(0x0F); // Select PMU_Range register
    Wire.write(0x03); // Range = +/- 2g
    Wire.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Accl);
    Wire.write(0x10); // Select PMU_BW register
    Wire.write(0x08); // Bandwidth = 7.81 Hz
    Wire.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Accl);
    Wire.write(0x11); // Select PMU_LPW register
    Wire.write(0x00); // Normal mode, Sleep duration = 0.5ms
    Wire.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Gyro);
    Wire.write(0x0F); // Select Range register
    Wire.write(0x04); // Full scale = +/- 125 degree/s
    Wire.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Gyro);
    Wire.write(0x10); // Select Bandwidth register
    Wire.write(0x07); // ODR = 100 Hz
    Wire.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Gyro);
    Wire.write(0x11); // Select LPM1 register
    Wire.write(0x00); // Normal mode, Sleep duration = 2ms
    Wire.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x4B); // Select Mag register
    Wire.write(0x83); // Soft reset
    Wire.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x4B); // Select Mag register
    Wire.write(0x01); // Soft reset
    Wire.endTransmission();
    delay(100);
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x4C); // Select Mag register
    Wire.write(0x00); // Normal Mode, ODR = 10 Hz
    Wire.endTransmission();
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x4E); // Select Mag register
    Wire.write(0x84); // X, Y, Z-Axis enabled
    Wire.endTransmission();
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x51); // Select Mag register
    Wire.write(0x04); // No. of Repetitions for X-Y Axis = 9
    Wire.endTransmission();
    //------------------------------------------------------------//
    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x52); // Select Mag register
    Wire.write(0x16); // No. of Repetitions for Z-Axis = 15
    Wire.endTransmission();

    
    def_pitch = 0;
    def_roll = 0;
    def_yaw = 0;
    counter=0;
}

void BMX055::set_accl()
{
    int data[6];
    for (int i = 0; i < 6; i++)
    {
        Wire.beginTransmission(Addr_Accl);
        Wire.write((2 + i)); // Select data register
        Wire.endTransmission();
        Wire.requestFrom(Addr_Accl, 1); // Request 1 byte of data
        // Read 6 bytes of data
        // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
        if (Wire.available() == 1)
            data[i] = Wire.read();
    }
    // Convert the data to 12-bits
    xAccl = ((data[1] * 256) + (data[0] & 0xF0)) / 16;
    if (xAccl > 2047)
        xAccl -= 4096;
    yAccl = ((data[3] * 256) + (data[2] & 0xF0)) / 16;
    if (yAccl > 2047)
        yAccl -= 4096;
    zAccl = ((data[5] * 256) + (data[4] & 0xF0)) / 16;
    if (zAccl > 2047)
        zAccl -= 4096;
    xAccl = xAccl * 0.0098; // renge +-2g
    yAccl = yAccl * 0.0098; // renge +-2g
    zAccl = zAccl * 0.0098; // renge +-2g
}

void BMX055::set_gyro()
{
    int data[6];
    for (int i = 0; i < 6; i++)
    {
        Wire.beginTransmission(Addr_Gyro);
        Wire.write((2 + i)); // Select data register
        Wire.endTransmission();
        Wire.requestFrom(Addr_Gyro, 1); // Request 1 byte of data
        // Read 6 bytes of data
        // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
        if (Wire.available() == 1)
            data[i] = Wire.read();
    }
    // Convert the data
    xGyro = (data[1] * 256) + data[0];
    if (xGyro > 32767)
        xGyro -= 65536;
    yGyro = (data[3] * 256) + data[2];
    if (yGyro > 32767)
        yGyro -= 65536;
    zGyro = (data[5] * 256) + data[4];
    if (zGyro > 32767)
        zGyro -= 65536;

    xGyro = xGyro * 0.0038; //  Full scale = +/- 125 degree/s
    yGyro = yGyro * 0.0038; //  Full scale = +/- 125 degree/s
    zGyro = zGyro * 0.0038; //  Full scale = +/- 125 degree/s
}

void BMX055::set_mag()
{
    int data[8];
    for (int i = 0; i < 8; i++)
    {
        Wire.beginTransmission(Addr_Mag);
        Wire.write((0x42 + i)); // Select data register
        Wire.endTransmission();
        Wire.requestFrom(Addr_Mag, 1); // Request 1 byte of data
        // Read 6 bytes of data
        // xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
        if (Wire.available() == 1)
            data[i] = Wire.read();
    }
    // Convert the data
    xMag = ((data[1] << 8) | (data[0] >> 3));
    if (xMag > 4095)
        xMag -= 8192;
    yMag = ((data[3] << 8) | (data[2] >> 3));
    if (yMag > 4095)
        yMag -= 8192;
    zMag = ((data[5] << 8) | (data[4] >> 3));
    if (zMag > 16383)
        zMag -= 32768;
}

void BMX055::set_deg()
{
    set_accl();
    set_gyro();
    set_mag();
    MadgwickFilter.updateIMU(xGyro, yGyro, zGyro, xAccl, yAccl, zAccl);
    //MadgwickFilter.update(xGyro, yGyro, zGyro, xAccl, yAccl, zAccl, xMag, yMag, zMag);
    pitch = MadgwickFilter.getRoll();
    roll = MadgwickFilter.getPitch(); //センサーを置く向きに応じて変更する
    yaw = MadgwickFilter.getYaw();
    if(counter==1){
      def_pitch = pitch;
      def_roll = roll;
      def_yaw = yaw;
      data = "def_oyr," + String(pitch) + "," + String(roll) + "," + String(yaw) + ",";
      return;
    }
    data = "oyr," + String(pitch-def_pitch) + "," + String(roll-def_roll) + "," + String(yaw-def_yaw) + ",";
}
