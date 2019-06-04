#include "definition.h"

DATA data;
AIRSPEED airspeed(A0);
BMX055 bmx055;
void setup()
{
  Serial.begin(9600);
  Serial.println("started!");
  bmx055.init();
  airspeed.init();
}

void loop()
{
  if(bmx055.counter%2 == 1){
    bmx055.set_deg();
    data.append(bmx055.data);
    airspeed.set();
    data.append(airspeed.data);
    Serial.println(bmx055.data);
    Serial.println(airspeed.data);
  }
  if(bmx055.counter%50 == 0){
    data.save();
  }
  bmx055.counter++;
  delay(100);
}
