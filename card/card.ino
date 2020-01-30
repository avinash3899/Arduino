/*
 * 
 * All the resources for this project: https://www.hackster.io/Aritro
 * Modified by Aritro Mukherjee
 * 
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.clear();

}
void loop() 
{
  lcd.setCursor(0,0);
  lcd.print("Show card");
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "4D D0 DA 4B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HELLO");
    lcd.setCursor(0,1);
    lcd.print("AVINASH");
    delay(3000);
    lcd.clear();
  }


  else if (content.substring(1) == "0D 7C DB 0A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HELLO");
    lcd.setCursor(0,1);
    lcd.print("SHUBHAM");
    delay(3000);
    lcd.clear();
  }

  
 
 else   {
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HELLO");
    lcd.setCursor(0,1);
    lcd.print("BHOSDIKE");
    delay(3000);
    lcd.clear();
  }
} 
