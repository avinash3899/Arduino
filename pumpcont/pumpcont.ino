#define trigger 9
#define echo 10
#define motor 8
float duration=0,distance=0;
int temp=0;
void setup()
{
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(motor, OUTPUT);
 digitalWrite(motor, HIGH);
 delay(1000);
}
 
void loop()
{
  
  digitalWrite(motor, HIGH);
 delay(1000);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 duration=pulseIn(echo,HIGH);
 distance=duration*340/20000;
 if(distance<20 && temp==0)
 {
     digitalWrite(motor, LOW);
     temp=1;
     delay(2000);
     
 }
}
