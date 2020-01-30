#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
String apiKey = "3YLPEYDVTRGNGIWD";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "SRM-Event";     // replace with your wifi ssid and wpa2 key
const char *pass =  "SRMist#3333";
const char* server = "api.thingspeak.com";
float t,h,ppm,ppm1;
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}


void loop()
{

  if (Serial.available() > 0) {

    while (Serial.available()) {

      StaticJsonBuffer<1000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(Serial);
      if (root == JsonObject::invalid())
        return;
      t = root["data1"];
      h = root["data2"];
      ppm = root["data3"];
      ppm1 = root["data4"];
      
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(ppm);
                             postStr +="&field4=";
                             postStr += String(ppm1);                             
                             
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                            /* Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.print("%, Indoor CO2: ");
                             Serial.print(ppm);
                             Serial.print("ppm, Outdoor CO2: ");
                             Serial.print(ppm1);
                             Serial.println("ppm. Send to Thingspeak.");  */                           
                        }
          client.stop();

    }
  }

}
