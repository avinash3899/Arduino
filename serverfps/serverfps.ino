
#include <SoftwareSerial.h>
#include <SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "Avinash";               // SSID of your home WiFi
char pass[] = "password";               // password of your home WiFi
WiFiServer server(80);                    

IPAddress ip(192, 168, 43, 80);            // IP address of the server
IPAddress gateway(192,168,43,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network
SoftwareSerial fps(D3, D4);


void setup()
{
  
  Serial.begin(9600); //set up Arduino's hardware serial UART
   fps.begin(9600);  
  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  server.begin();                         // starts the server
}

void loop()
{
 WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      fps.write(client.read());
      delay(10);
  if(fps.available()){
      while(fps.available()>0){
      client.write(fps.read()); // sends the answer to the client
    }
      }
    }
  }
}
