
#include <ArduinoJson.h>
 
void setup() {
Serial.begin(9600);
randomSeed(20);
}
 
void loop() {
 StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
  root["data1"] = random(10,20);
  root["data2"] = random(40,50);
  root.printTo(Serial);
  delay(1000);
}
