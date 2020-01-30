#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(10,8); // CE, CSN
const byte address[6] = "00001";
int i=0;
const int lt = 3;
const int fw = 2;
const int rt = 5;
const int bw = 4;


int message[4];

void setup() {
  Serial.begin(9600);
  for(int i=2;i<6;i++)
  {
    pinMode(i,INPUT_PULLUP);
  }
  radio.begin();
  bool check = radio.isChipConnected();
  while(!check){}
  Serial.println("Chip Connected");
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  message[0]=digitalRead(fw);
  message[1]=digitalRead(rt);
  message[2]=digitalRead(bw);
  message[3]=digitalRead(lt);
  for(int i=0;i<=3;i++)
  {
    Serial.print(message[i]);
    
    }
  Serial.println("");
  radio.write(&message, sizeof(message));
  
}
