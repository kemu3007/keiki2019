#include "definition.h"

DATA::DATA()
{
  temp = "\n";
  chip_select = 53;
  SD.begin(chip_select);
}

void DATA::append(String data){
  temp += data;
}

void DATA::save(){
  datafile = SD.open("data.csv", FILE_WRITE);
  if (datafile) {
    datafile.print(temp);
    datafile.close();
    temp = "";
  }
  else{
    Serial.println("writing error!");
  }
}
