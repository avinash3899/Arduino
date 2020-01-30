#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address
struct Data_Package {
  byte temperature;
  byte moisture;
  byte pH;
  byte light;
  byte battery;
};
Data_Package data;
void setup() {
  Serial.begin(9600);
  sensors.begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

}
void loop() {
  sensors.requestTemperatures();
  data.temperature=sensors.getTempCByIndex(0);
  data.moisture=analogRead(A1);//random(60,70);
  data.pH= analogRead(A0);//random(70,80);//
  data.light=analogRead(A2);//random(80,90)
  data.battery=93;
  Serial.print(data.temperature);
  Serial.print(" ");
  Serial.print(data.moisture);
  Serial.print(" ");
  Serial.print(data.pH);
  Serial.print(" ");
  Serial.print(data.light);
  Serial.print(" ");
  Serial.println(data.battery);
  radio.write(&data, sizeof(Data_Package));
  delay(2000);
}
