#include "bmx055.h"

BMX055 bmx055;

void setup()
{
  Serial.begin(115200);
  bmx055.init();
}

void loop()
{
  bmx055.processing();
  Serial.print(bmx055.pitch);
  Serial.print(",");
  Serial.print(bmx055.roll);
  Serial.print(",");
  Serial.println(bmx055.yaw);
  delay(50);
}
