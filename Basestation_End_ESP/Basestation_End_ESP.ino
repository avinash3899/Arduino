#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>

char auth[] = "CPNs4YCV-7bl-GrmZ-I1iB4GJ4H-z75j";
int refresh;
int pumpstate = 0;
char ssid[] = "Avinash";
char pass[] = "password";

int temp = 50;
int moisture = 50;
int pH = 50;
int light = 50;
int battery = 50;
int pump,onetimeon,onetimeoff;


WidgetLCD lcd1(V0);
WidgetLCD lcd2(V1);

BLYNK_WRITE(V2)
{
  pumpstate = param.asInt(); // assigning incoming value from pin V2 to a variable

  // process received value
}
BLYNK_WRITE(V3)
{
  refresh = param.asInt(); // assigning incoming value from pin V3 to a variable

  // process received value
}

BLYNK_CONNECTED()
{
  // Request the latest state from the server
  Blynk.syncVirtual(V2);
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);

  Blynk.begin(auth, ssid, pass);
  lcd1.clear();
  lcd2.clear();
}


void loop()
{
  Blynk.run();

  if (Serial.available() > 0) {

    while (Serial.available()) {

      StaticJsonBuffer<1000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(Serial);
      if (root == JsonObject::invalid())
        return;
      temp = root["data1"];
      moisture = root["data2"];
      pH = root["data3"];
      light = root["data4"];
      battery = root["data5"];
      pump = root["data6"];
      refresh = 1;
    }
  }

  if (refresh == 1) {

    lcd1.print(0, 0, "Temperature=");
    lcd1.print(12, 0, temp);
    lcd1.print(14, 0, "°C");

    lcd1.print(0, 1, "Moisture=");
    lcd1.print(9, 1, moisture);
    lcd1.print(11, 1, "%");

    lcd2.print(0, 0, "pH=");
    lcd2.print(3, 0, pH);

    lcd2.print(0, 1, "Light=");
    lcd2.print(6, 1, light);
    lcd2.print(8, 1, "lux");
    Blynk.virtualWrite(V4, battery);
    refresh = 0;
  }

  if (pumpstate == 1) {
    digitalWrite(1, LOW);
    if (pump == 0&&onetimeon==0) {
      digitalWrite(2, LOW);
      delay(200);
      digitalWrite(2, HIGH);
      onetimeon=1;
      onetimeoff=0;
    }
  }
  else if (pumpstate == 0)
  {
    digitalWrite(1, HIGH);
    if (pump == 1&&onetimeoff==0)
    {
      digitalWrite(2, LOW);
      delay(200);
      digitalWrite(2, HIGH);
      onetimeon=0;
      onetimeoff=1;
    }
  }

}
