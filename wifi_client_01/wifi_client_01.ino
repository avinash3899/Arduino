#include <ESP8266WiFi.h>
char ssid[] = "AvinashNetGear";        
char pass[] = "Avinash!@#3899";         

IPAddress server(192,168,1,24);
WiFiClient client;
long int i = 0;
void setup() {
  Serial.begin(115200);               
  WiFi.begin(ssid, pass);      
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
   Serial.print("IP: ");     Serial.println(WiFi.localIP());
}

void loop () {
if (client.connect(server,8080))
  {

    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        i++;
      }
    }
    Serial.print(i);
    Serial.println(" lines received");
   while(true){delay(2000);};
  }
 
}
