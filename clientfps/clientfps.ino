#include <SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "Avinash";           // SSID of your home WiFi
char pass[] = "password";            // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(192,168,43,80);       // the fix IP address of the server
WiFiClient client;

void setup()
{
  Serial.begin(9600); //set up Arduino's hardware serial UAR
   WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
}

void loop()
{
     
   if(Serial.available()){
      client.connect(server, 80);
      client.print(Serial.read());
      if(client.available()){
      Serial.write(client.read());
      client.flush();
    }
    }
    

}
