#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "Avinash";
const char* password = "password";

bool ota_flag = true;
uint16_t time_elapsed = 0;


int M1A=16;//left motor A(fwd)
int M1B=14;//left motor B(rev)
int M2A=12;//right motor A(fwd)
int M2B=13;//right motor B(rev)
int rl=1;//red led
int gl=3;//green led
int bl=5;//blue led
int SF= 1024;
int SB=1024;
int SR=1024;
int SL=1024;
int SF1=1024;
int SF2=1024;
int SB1=1024;
int SB2=1024;


void fw();
void bw();
void rt();
void lt();
void stp();
void otainit();


void setup() {
  pinMode(M1A,OUTPUT);
  pinMode(M1B,OUTPUT);
  pinMode(M2A,OUTPUT);
  pinMode(M2B,OUTPUT);
  pinMode(rl,OUTPUT);
  pinMode(gl,OUTPUT);
  pinMode(bl,OUTPUT);
  pinMode(2,OUTPUT);
  digitalWrite(rl,HIGH);
  digitalWrite(gl,HIGH);
  digitalWrite(bl,HIGH);


  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
   
    delay(5000);
    ESP.restart();
  }
  otainit();

  digitalWrite(2,LOW);
}

void loop() {
   if(ota_flag)
  {
    while(time_elapsed < 20000)
    {
      ArduinoOTA.handle();
      time_elapsed = millis();
      delay(10);
    }
   digitalWrite(2,HIGH);
   ota_flag = false; 
  }

  digitalWrite(rl,LOW);
  delay(1000);
  digitalWrite(rl,HIGH);
  delay(1000);
  digitalWrite(gl,LOW);
  delay(1000);
  digitalWrite(gl,HIGH);
  delay(1000);
  digitalWrite(bl,LOW);
  delay(1000);
  digitalWrite(bl,HIGH);
  delay(1000);
 /* fw();
  delay(2000);
  stp();
  delay(1000);
  bw();
  delay(2000);
  stp();
  delay(1000);
  rt();
  delay(2000);
  stp();
  delay(1000);
  lt();
  delay(2000);
  stp();
  delay(1000);*/
  // put your main code here, to run repeatedly:

}


void fw()
{
  analogWrite(M1A,SF);
  analogWrite(M2A,SF);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }

  
void bw()
{
  analogWrite(M1A,0);
  analogWrite(M2A,0);
  analogWrite(M1B,SB);
  analogWrite(M2B,SB);  
  }

  
void rt()
{
  analogWrite(M1A,SR);
  analogWrite(M2A,0);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }

  
void lt()
{
  analogWrite(M1A,0);
  analogWrite(M2A,SL);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }


void fwd()
{
  analogWrite(M1A,SF1);
  analogWrite(M2A,SF2);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }

void bwd()
{
  analogWrite(M1A,0);
  analogWrite(M2A,0);
  analogWrite(M1B,SB1);
  analogWrite(M2B,SB2);
  }

void stp()
{
  analogWrite(M1A,0);
  analogWrite(M2A,0);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
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
