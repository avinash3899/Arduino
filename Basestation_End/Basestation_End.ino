#include <Wire.h> 
#include <SPI.h>
#include <Wire.h> 
#include <RF24.h>
#include <nRF24L01.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
RF24 radio(8, 10);
int pump;
int temp,moist,light,battery,refresh;
float ph;
int buzzer=9;
const byte address[6] = "00001";

struct Data_Package {
  byte temperature;
  byte moisture;
  byte pH;
  byte light;
  byte battery;
};
Data_Package data; 
void setup() {
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  lcd.begin();
  lcd.backlight();
  lcd.home();
  lcd.print("Base Ready");
}
void loop() {
  
  int b1= digitalRead(3);
  int b2= digitalRead(4);
  int b3= digitalRead(5);
  int b4= digitalRead(6);
  int b5= digitalRead(A0);
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    refresh=1;
  }

  StaticJsonBuffer<1000> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    temp = data.temperature;
    moist= 90;//data.moisture;
    ph = 6.8;//data.pH;
    light= data.light;
    battery= data.battery;
    root["data1"] = temp ;
    root["data2"] = moist ;
    root["data3"] = ph ;
    root["data4"] = light ;
    root["data5"] = battery ;
    root["data6"] = pump ;
    root.printTo(Serial);
  if(refresh){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T =");
  lcd.print(temp);
  lcd.print("C");
  
  lcd.setCursor(8,0);
  lcd.print("M =");
  lcd.print(moist);
  lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print("pH=");
  lcd.print(ph);
 
  lcd.setCursor(8,1);
  lcd.print(" L=");
  lcd.print(light);
  lcd.print("lux");
  refresh=0;
  }
 if(b4==0||b5==0){
  delay(200);
  digitalWrite(7,!digitalRead(7));
  pump=digitalRead(7);
  tone(buzzer,300);
  delay(300);
  noTone(buzzer);
  }

  

}




 
