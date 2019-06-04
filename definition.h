#include <SD.h>

#ifndef DEFINITION_H
#define DEFINITION_H

#include "airspeed.h"
#include "altimeter.h"
#include "bmx055.h"
#include "cadence.h"
#include "gps.h"

class DATA{
public:
    String temp;
    DATA();
    void append(String data);
    void save(); 
private:
    File datafile;
    int chip_select;
};
#endif
