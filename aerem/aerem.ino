#include "MQ135.h"
#include "Wire.h"
#include <ArduinoJson.h>
 
MQ135 gasSensor = MQ135(A0);
MQ135 gasSensor1 = MQ135(A1);

void setup() 
{
       Serial.begin(9600); 
}
 
void loop() 
{
     float t = 31.0;
     float h = 84.0;
     float ppm = gasSensor.getPPM();
     float ppm1 = gasSensor1.getPPM();
     StaticJsonBuffer<1000> jsonBuffer;
     JsonObject& root = jsonBuffer.createObject();
  root["data1"] = t;
  root["data2"] = h;
  root["data3"] = ppm-100;
  root["data4"] = ppm1;
  root.printTo(Serial);
  delay(2000);
}
