#include "arduino.h"
#include "airspeed.h"

AIRSPEED::AIRSPEED(int Pin)
{
    AS_PIN = Pin;
}

void AIRSPEED::init()
{
    pinMode(AS_PIN, INPUT);
}
void AIRSPEED::set()
{
    air_speed = analogRead(AS_PIN);
    data = "AS," + String(air_speed) + "\n"; 
}
