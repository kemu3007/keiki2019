#ifndef CADENCE_H
#define CADENCE_H

#include "arduino.h"

class CADENCE
{
public:
    CADENCE();
    void init();
    void set();
    float cadence;
    String data;
};
#endif
