int RIGHTSPEED;
int LEFTSPEED;
const int rightA = 5;      // RIGHT_MOTOR_A
const int rightB = 3;      // RIGHT_MOTOR_B
const int leftA = 9;       // LEFT_MOTOR_A
const int leftB = 6;       // LEFT_MOTOR_B
float RIGHTMOTOR = 0;
float LEFTMOTOR = 0;
float currentERROR = 0;    
float previousERROR = 0;   
float P = 0;               
float I = 0;               
float D = 0;               
float PID = 0;   
          
const int L3 = 12;         // LEFT_3RD
const int L2 = 11;          // LEFT_2ND
const int L1 = 10;          // LEFT_1ST
const int CL = 8;          // CENTER_LEFT
const int CR = 7;          // CENTER_RIGHT
const int R1 = 4;         // RIGHT_1ST
const int R2 = 2;         // RIGHT_2ND
const int R3 = 13;         // RIGHT_3RD

const int Kp = 17;
const int Kd = 8;
const int Ki = 0;

int valL3 = 0;
int valL2 = 0;
int valL1 = 0;
int valCL = 0;
int valCR = 0;
int valR1 = 0;
int valR2 = 0;
int valR3 = 0;

void setup() 
{
  //Serial.begin(9600);
  pinMode(L3,INPUT);
  pinMode(L2,INPUT);
  pinMode(L1,INPUT);
  pinMode(CL,INPUT);
  pinMode(CR,INPUT);
  pinMode(R1,INPUT);
  pinMode(R2,INPUT);
  pinMode(R3,INPUT);
  pinMode(rightA,OUTPUT);
  pinMode(rightB,OUTPUT);
  pinMode(leftA,OUTPUT);
  pinMode(leftB,OUTPUT);
  
}

void loop() 
{
  int FAST = 0;
  readSensor();

  /*
  Serial.print(valL3);
  Serial.print(valL2);
  Serial.print(valL1);
  Serial.print(valCL);
  Serial.print(valCR);
  Serial.print(valR1);
  Serial.print(valR2);
  Serial.print(valR3);
  Serial.println("");
    */

    analogWrite(leftA, LEFTMOTOR);
    analogWrite(leftB, 0);
    analogWrite(rightA, RIGHTMOTOR);
    analogWrite(rightB, 0);
 

  /* if (valL3== && valL2== && valL1== && valCL== && valCR== && valR1== && valR2== && valR3==)
     {
        currentERROR = ;
     } */

 if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW && (previousERROR<0))
  {
    
    analogWrite(leftA,0);
    analogWrite(leftB,150);
    analogWrite(rightA,180);
    analogWrite(rightB,0);
    if(valL3==1 || valL2==1 || valL1==1 || valCL==1 || valCR==1 || valR1==1 || valR2==1 || valR3==1){
    brake();}
    //delay(5);
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW && (previousERROR>0))
  {
    //ERROR_CORRECTON for RIGHT
    analogWrite(leftA,180);
    analogWrite(leftB,0);
    analogWrite(rightA,0);
    analogWrite(rightB,150);
    
    if(valL3==1 || valL2==1 || valL1==1 || valCL==1 || valCR==1 || valR1==1 || valR2==1 || valR3==1){
    brake();}
    //delay(5);
  }


  
  if (valL3==HIGH && valL2==LOW && valL1==LOW && valCL==LOW && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW)
  {
    currentERROR = -5;   //0001
  }

  if (valL3==HIGH && valL2==HIGH && valL1==LOW && valCL==LOW && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW)
  {
    currentERROR = -4;     //0002
  }

  if (valL3==LOW && valL2==HIGH && valL1==LOW && valCL==LOW && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW)
  {
    currentERROR = -3;   //0003
  }

  if (valL3==LOW && valL2==HIGH && valL1==HIGH && valCL==LOW && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW)
  {
    currentERROR = -2;     //0004
  }

  if (valL3==LOW && valL2==LOW && valL1==HIGH && valCL==LOW && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW)
  {
    currentERROR = -1.5;   //0005
  }

  if (valL3==LOW && valL2==LOW && valL1==HIGH && valCL==HIGH && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW)
  {
    currentERROR = -1;     //0006
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==HIGH && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW)
  {
    currentERROR = -0.5;   //0007
  }

  if ((valL3==LOW && valL2==LOW && valL1==LOW && valCL==HIGH && valCR==HIGH && valR1==LOW && valR2==LOW && valR3==LOW) || (valL3==HIGH && valL2==HIGH && valL1==HIGH && valCL==HIGH && valCR==HIGH && valR1==HIGH && valR2==HIGH && valR3==HIGH))
  {
    currentERROR = 0;      //0008
    FAST = 25;             //0008
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==HIGH && valR1==LOW && valR2==LOW && valR3==LOW)
  {
    currentERROR = 0.5;    //0009
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==HIGH && valR1==HIGH && valR2==LOW && valR3==LOW)
  {
    currentERROR = 1;      //0010
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==LOW && valR1==HIGH && valR2==LOW && valR3==LOW)
  {
    currentERROR = 1.5;    //0011
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==LOW && valR1==HIGH && valR2==HIGH && valR3==LOW)
  {
    currentERROR = 2;      //0012
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==LOW && valR1==LOW && valR2==HIGH && valR3==LOW)
  {
    currentERROR = 3;    //0013
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==LOW && valR1==LOW && valR2==HIGH && valR3==HIGH)
  {
    currentERROR = 4;      //0014
  }

  if (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==LOW && valR1==LOW && valR2==LOW && valR3==HIGH)
  {
    currentERROR =5;    //0015
  }

  

  

  if ((valL3==HIGH && valL2==HIGH && valL1==HIGH && valCL==HIGH && valCR==HIGH && valR1==LOW && valR2==LOW && valR3==LOW) || (valL3==HIGH && valL2==HIGH && valL1==HIGH && valCL==HIGH && valCR==LOW && valR1==LOW && valR2==LOW && valR3==LOW))
  {
        //HARD LEFT TURN
    while (valL2!=0) // HARD LEFT TURN
    {
      
      analogWrite(leftA, 0);
      analogWrite(leftB, 200);
      analogWrite(rightA, 200);
      analogWrite(rightB, 0);
      readSensor();
    }
   
  }

  if ((valL3==LOW && valL2==LOW && valL1==LOW && valCL==HIGH && valCR==HIGH && valR1==HIGH && valR2==HIGH && valR3==HIGH) || (valL3==LOW && valL2==LOW && valL1==LOW && valCL==LOW && valCR==HIGH && valR1==HIGH && valR2==HIGH && valR3==HIGH))
  {             
    
    while (valR2!=0) // HARD RIGHT TURN
    {
      
      analogWrite(leftA, 200);
      analogWrite(leftB, 0);
      analogWrite(rightA, 0);
      analogWrite(rightB, 200);
      readSensor();
    }
    
  }


  if (FAST == 25)
  {
    analogWrite(leftA,240);
    analogWrite(leftB,0);
    analogWrite(rightA,240);
    analogWrite(rightB,0);
  }



if((currentERROR>=-5&&currentERROR<=-1.5)||(currentERROR>=1.5&&currentERROR<=5))
{
  RIGHTSPEED = 130;
  LEFTSPEED = 130;
  calculatepid();
  //readSensor();  
}

if((currentERROR>=-1&&currentERROR<=1))
{
  RIGHTSPEED = 215;
  LEFTSPEED = 215;
  calculatepid();
 //readSensor(); 
}

}    

void calculatepid()
{

    P = currentERROR;
    I = previousERROR + currentERROR;
    D = previousERROR - currentERROR;
    previousERROR = currentERROR;
    PID = (Kp*P) + (Ki*I) + (Kd*D);
    RIGHTMOTOR = RIGHTSPEED - PID;
    LEFTMOTOR = LEFTSPEED + PID;
}

void readSensor()
{
  valL3 = digitalRead(L3);
  valL2 = digitalRead(L2);
  valL1 = digitalRead(L1);
  valCL = digitalRead(CL);
  valCR = digitalRead(CR);
  valR1 = digitalRead(R1);
  valR2 = digitalRead(R2);
  valR3 = digitalRead(R3);
}

void brake(){

    analogWrite(leftA,255);
    analogWrite(leftB,255);
    analogWrite(rightA,255);
    analogWrite(rightB,255);
    delay(400);
    
    }
