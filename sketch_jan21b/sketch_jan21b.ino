#include "MQ135.h"
#include "Wire.h"
MQ135 gasSensor = MQ135(A0);
void setup() {
 Serial.begin(9600);  // put your setup code here, to run once:

}

void loop() {
  
  float res = gasSensor.getPPM();
  Serial.println(res);
  delay(1000);
  // put your main code here, to run repeatedly:

}
