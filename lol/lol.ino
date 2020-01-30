#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>

char password[4];
char pass[4],pass1[4];
int i=0;
char customKey=0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {A0,A1,A2,A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A4,A5,3,2};   //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int led;
int buzzer = 10;
int m11;
int m12;
void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);

 
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
 
  Serial.print(" Electronic ");
 
  
  Serial.print(" Keypad Lock ");
  delay(2000);
 
  Serial.println("Enter Ur Passkey:");
 
  for(int j=0;j<4;j++)
    EEPROM.write(j, j+49);
  for(int j=0;j<4;j++)
    pass[j]=EEPROM.read(j);
}

void loop()
{
  digitalWrite(11, LOW);
  customKey = customKeypad.getKey();
  if(customKey=='#')
    change();
  if (customKey)
  {
    password[i++]=customKey;
    
    Serial.print(customKey);
    beep();
  }
  if(i==4)
  {
    delay(200);
    for(int j=0;j<4;j++)
      pass[j]=EEPROM.read(j);
    if(!(strncmp(password, pass,4)))
    {
      digitalWrite(led, HIGH);
      beep();
     
      Serial.println("Passkey Accepted");
      digitalWrite(11, HIGH);
      delay(2000);
     
      Serial.println("#.Change Passkey");
      delay(2000);
      
      Serial.println("Enter Passkey:");
      
      i=0;
      digitalWrite(led, LOW);
    }
    else
    {
      digitalWrite(11, LOW);
      digitalWrite(buzzer, HIGH);
     
      Serial.println("Access Denied...");
      
      Serial.println("#.Change Passkey");
      delay(2000);
     
      Serial.println("Enter Passkey:");
     
      i=0;
      digitalWrite(buzzer, LOW);
    }
  }
}
void change()
{
  int j=0;
 
  Serial.println("UR Current Passk");
 
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      pass1[j++]=key;
     
      Serial.print(key);
      beep();
    }
    key=0;
  }
  delay(500);

  if((strncmp(pass1, pass, 4)))
  {
   
    Serial.println("Wrong Passkey...");
   
    Serial.println("Better Luck Again");
    delay(1000);
  }
  else
  {
    j=0;
   
    Serial.println("Enter New Passk:");
    
    while(j<4)
    {
      char key=customKeypad.getKey();
      if(key)
      {
        pass[j]=key;
       
        Serial.print(key);
        EEPROM.write(j,key);
        j++;
        beep();
      }
    }
   
    Serial.println(" Done......");
    delay(1000);
  }
 
  Serial.println("Enter Ur Passk:");
 
  customKey=0;
}
void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
}
