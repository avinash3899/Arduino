int val;
float voltage , temp;

void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
val=analogRead(1);
voltage=val*(5/1024);
temp=voltage/0.01;
Serial.println(temp);
delay(1000);
}
