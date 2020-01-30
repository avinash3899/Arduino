#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 4); // CE, CSN
const byte address[6] = "00001";
int i=0;



void setup() {

  radio.begin();
  digitalWrite(8,LOW);
  while(!radio.isChipConnected()){
   
    delay(400);
  }
  digitalWrite(8,HIGH);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

}



void loop() {
radio.write(&i,sizeof(i));
i++;
delay(1000);
}
