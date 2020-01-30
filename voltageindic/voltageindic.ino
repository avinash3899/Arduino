#include <Wire.h>
#include <LiquidCrystal_I2C.h>
float value,volts_1,volts_2,percentage,maxvalue=13.6,minvalue=11.8;
LiquidCrystal_I2C lcd(0x3F,16,2);
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
void loop()
{
  value=analogRead(A0);
  volts_1=value*(5.0/1023.0);
  volts_2=(volts_1*50.0)/4.4;
  percentage=((volts_2-minvalue)/(maxvalue-minvalue))*100;
  Serial.print("Voltage = ");
  Serial.print(volts_2);
  Serial.println("");
  Serial.print("percentage = ");
  Serial.print(percentage);
  Serial.println("");
  lcd.setCursor(0,0);
  lcd.print("VOLTAGE = ");
  lcd.print(volts_2);
  lcd.print(" ");
  lcd.setCursor(0,1);
  lcd.print("Percent = ");
  lcd.print(percentage);
  lcd.print(" ");
delay(1000);
}
