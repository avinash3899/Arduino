#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Avinash";
const char* password = "password";

WiFiUDP Udp;
unsigned int localUdpPort = 8080;  // local port to listen on
int incomingPacket;  // buffer for incoming packets


void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(D0,OUTPUT);
  digitalWrite(D0,HIGH);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}


void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    incomingPacket = Udp.read( );
    Serial.printf("UDP packet contents: %d\n", incomingPacket);
    if(incomingPacket==49){
      digitalWrite(D0,LOW);
    }
    if(incomingPacket==48){
      digitalWrite(D0,HIGH);
    }
    
  }
  
}
