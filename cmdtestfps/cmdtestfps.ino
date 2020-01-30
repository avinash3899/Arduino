#include "FPS_GT511C3.h"
#include <SoftwareSerial.h>
FPS_GT511C3 fps(D3, D4);
SoftwareSerial fpa(D3,D4);
void setup() {
  Serial.begin(9600);
  fps.UseSerialDebug = true;
  delay(5000);
  fps.Open();
  delay(5000);
  fps.GetTemplate(0);
  fpa.listen();
  while(true){

int    re=fpa.read();
    Serial.print(re);
  }}
void loop() {

}
