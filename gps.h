#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

class GPS
{
public:
    GPS();
    void init();
    void set();
    float latitude, longitude, rotate;
    String data;
};
#endif
