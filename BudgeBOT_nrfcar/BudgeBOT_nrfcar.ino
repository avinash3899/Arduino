#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 4); // CE, CSN
const byte address[6] = "00001";
int message[4];
int sum=0;
int previousMillis = 0;
int timeout = 1000;


void setup() {
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  radio.begin();
  while(!radio.isChipConnected()){
   
    delay(400);
  }
  Serial.println("Chip Connected");
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  // put your setup code here, to run once:

}

void loop() {
    int currentmillis=millis();
  if (radio.available()) {
      while(radio.available()){
      previousMillis=millis();
      radio.read(&message,sizeof(message));
      int sum=0;
      for(int i=0;i<4;i++){sum=sum+message[i];Serial.print(message[i]);}
      Serial.print(" ");
      Serial.print(sum);
      Serial.print(" ");
      if(sum==3&&(message[0]==0&&message[1]==1&&message[2]==1&&message[3]==1)){forward();}
      if(sum==3&&(message[0]==1&&message[1]==0&&message[2]==1&&message[3]==1)){right();}
      if(sum==3&&(message[0]==1&&message[1]==1&&message[2]==0&&message[3]==1)){backward();}
      if(sum==3&&(message[0]==1&&message[1]==1&&message[2]==1&&message[3]==0)){left();}
      else if(sum==4){stp();}      
    } 
  }
  else if(!radio.available()&&(currentmillis-previousMillis)>timeout){

           Serial.println("connection lost");
           while(!radio.available()){stp();}
  }

}

void forward(){
 digitalWrite(5,HIGH);
 digitalWrite(9,HIGH);
 digitalWrite(6,LOW);
 digitalWrite(10,LOW);
 Serial.println("FWD");
}
void right(){
 digitalWrite(5,LOW);
 digitalWrite(9,HIGH);
 digitalWrite(6,HIGH);
 digitalWrite(10,LOW);
 Serial.println("RIT");
}
void backward(){
 digitalWrite(5,LOW);
 digitalWrite(9,LOW);
 digitalWrite(6,HIGH);
 digitalWrite(10,HIGH);
 Serial.println("BWD");
}
void left(){
 digitalWrite(5,HIGH);
 digitalWrite(9,LOW);
 digitalWrite(6,LOW);
 digitalWrite(10,HIGH);
 Serial.println("LFT");
}
void stp(){
 digitalWrite(5,LOW);
 digitalWrite(9,LOW);
 digitalWrite(6,LOW);
 digitalWrite(10,LOW);
 Serial.println("STP");
}
