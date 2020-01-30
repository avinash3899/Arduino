const int M1A = 9;
const int M1B = 10;
const int M2A =6;
const int M2B = 5;
void setup() {
  
      pinMode(M2B,OUTPUT);
      pinMode(M1A,OUTPUT);
      pinMode(M1B,OUTPUT);
      pinMode(M2A,OUTPUT);
      

}

void loop() {
 digitalWrite(M2A,HIGH);
 digitalWrite(M1A,HIGH);
 digitalWrite(M1B,LOW);
 digitalWrite(M2B,LOW);


}
