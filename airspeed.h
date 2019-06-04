#ifndef AIRSPEED_H
#define AIRSPEED_H

class AIRSPEED
{
public:
    AIRSPEED(int Pin);
    void init();
    void set();
    float air_speed;
    String data;
private:
    int AS_PIN;
};
#endif
