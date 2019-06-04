#ifndef BMX055_H
#define BMX055_H

#include <Wire.h>
#include <MadgwickAHRS.h>
#include <Arduino.h>
#include <math.h>
#define Addr_Accl 0x19 // (JP1,JP2,JP3 = Open)
#define Addr_Gyro 0x69 // (JP1,JP2,JP3 = Open)
#define Addr_Mag 0x13  // (JP1,JP2,JP3 = Open)
class BMX055
{
public:
    BMX055();
    void init();
    void set_accl();
    void set_gyro();
    void set_mag();
    
    void set_deg();

    Madgwick MadgwickFilter;
    float xAccl, yAccl, zAccl;
    float xGyro, yGyro, zGyro;
    int xMag, yMag, zMag;
    float pitch, roll, yaw;
    String data;

    int counter;

    float def_pitch, def_roll, def_yaw;
};
#endif
