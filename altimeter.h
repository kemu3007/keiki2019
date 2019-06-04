#ifndef ALTIMETER_H
#define ALTIMETER_H

#define PIN_ALTIMETER 12

class ALTIMETER
{
public:
    ALTIMETER(int Pin);
    void init();
    void set();
    float altimeter;
    int AL_PIN;
};
#endif
