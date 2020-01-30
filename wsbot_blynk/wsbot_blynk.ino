#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int x,y;
char auth[] = "YourAuthToken";

const char* ssid = "Avinash";
const char* password = "password";

int ota_flag = 0 ;
uint16_t time_elapsed = 0;
void writemotors();

BLYNK_WRITE(V0)
{
  x = param[0].asInt();
  y = param[1].asInt();
}
BLYNK_WRITE(V3)
{
  ota_flag = param.asInt();
}


void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.waitForConnectResult() != WL_CONNECTED) { 
    delay(1000);
    ESP.restart();
  }
  otainit();
 

  Blynk.begin(auth, ssid, password);

}

void loop() {
 if(ota_flag)
  {
    digitalWrite(2,LOW);
    while(time_elapsed < 20000)
    {
      ArduinoOTA.handle();
      time_elapsed = millis();
      delay(10);
    }
   digitalWrite(2,HIGH);
   ota_flag = 0; 
  }
  Blynk.run();
 int X= map(x,0,1023,-1023,1023);
 int Y= map(y,0,1023,-1023,1023);
  writemotors(X,Y);
}



















void otainit()
{
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    
  });
  ArduinoOTA.onEnd([]() {
    
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  
  });
  ArduinoOTA.onError([](ota_error_t error) {
   
    if (error == OTA_AUTH_ERROR) {
     
    } else if (error == OTA_BEGIN_ERROR) {
    
    } else if (error == OTA_CONNECT_ERROR) {
     
    } else if (error == OTA_RECEIVE_ERROR) {
      
    } else if (error == OTA_END_ERROR) {
      
    }
  });
    ArduinoOTA.begin();
  
  }




void writemotors(int x , int y){
if(y>=0){
  if(x>=0){
    mlfs=y
    mlbs=0;
    mrfs=
    mrbs=0;
  }
}

    analogWrite(mlf,mlfs);
    analogWrite(mlb,mlbs);
    analogWrite(mrf,mrfs);
    analogWrite(mrb,mrbs);
}
