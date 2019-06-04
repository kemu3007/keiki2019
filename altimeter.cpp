#include "arduino.h"
#include "altimeter.h"

ALTIMETER::ALTIMETER(int Pin){
    AL_PIN = Pin;
}

void ALTIMETER::init(){
    pinMode(AL_PIN, INPUT);
}
void ALTIMETER::set(){
}
