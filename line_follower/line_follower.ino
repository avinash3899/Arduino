#include <QTRSensors.h>

QTRSensors qtr;
#define Kp 0.1
#define Kd 2
#define Ki 0.01
int RIGHTSPEED=100;
int LEFTSPEED=100;
int MaxSpeed=100;
const int rightA = 5;      // RIGHT_MOTOR_A
const int rightB = 3;      // RIGHT_MOTOR_B
const int leftA = 9;       // LEFT_MOTOR_A
const int leftB = 6;       // LEFT_MOTOR_B
float RIGHTMOTOR = 0;
float LEFTMOTOR = 0;
float currentERROR = 0;    
float previousERROR = 0;   
float error1;
float error2;
float P = 0;               
float I = 0;               
float D = 0;               
float PID = 0;   
      



int valL3 = 0;
int valL2 = 0;
int valL1 = 0;
int valCL = 0;
int valCR = 0;
int valR1 = 0;
int valR2 = 0;
int valR3 = 0;

int L3;         // LEFT_3RD
int L2;          // LEFT_2ND
int L1;          // LEFT_1ST
int CL;          // CENTER_LEFT
int CR;          // CENTER_RIGHT
int R1;         // RIGHT_1ST
int R2;         // RIGHT_2ND
int R3;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
uint16_t position ;

int soL3 = 12;         // LEFT_3RD
int soL2 = 11;          // LEFT_2ND
int soL1 = 10;          // LEFT_1ST
int soCL = 8;          // CENTER_LEFT
int soCR = 7;          // CENTER_RIGHT
int soR1 = 4;         // RIGHT_1ST
int soR2 = 2;         // RIGHT_2ND
int soR3 = 13;         // RIGHT_3RD

 int valsL3=0;
 int valsL2=0;
 int valsL1=0;
 int valsCL=0;
 int valsCR=0;
 int valsR1=0;
 int valsR2=0;
 int valsR3=0;


void setup()
{
  Serial.begin(9600);
  calibrate_sensor();
  pinMode(soL3,INPUT);
  pinMode(soL2,INPUT);
  pinMode(soL1,INPUT);
  pinMode(soCL,INPUT);
  pinMode(soCR,INPUT);
  pinMode(soR1,INPUT);
  pinMode(soR2,INPUT);
  pinMode(soR3,INPUT);
  pinMode(rightA,OUTPUT);
  pinMode(rightB,OUTPUT);
  pinMode(leftA,OUTPUT);
  pinMode(leftB,OUTPUT);
}

void loop()
{
  int FAST = 0;
  
  readSensor8A();
  readSensor();

  currentERROR = 3460-position ;
     error1 = currentERROR - previousERROR;
     error2 = (2.0 / 3.0) * error2 + currentERROR ;
    PID = Kp * currentERROR + Kd * error1 + Ki * error2;
    RIGHTMOTOR = RIGHTSPEED + PID;
    LEFTMOTOR = LEFTSPEED - PID;
    if (RIGHTMOTOR > MaxSpeed ) RIGHTMOTOR = MaxSpeed; // prevent the motor from going beyond max speed
    if (LEFTMOTOR > MaxSpeed ) LEFTMOTOR = MaxSpeed; // prevent the motor from going beyond max speed
    if (RIGHTMOTOR < 0)RIGHTMOTOR = 0;
    if (LEFTMOTOR < 0)LEFTMOTOR = 0;
    analogWrite(leftA, LEFTMOTOR);
    analogWrite(leftB, 0);
    analogWrite(rightA, RIGHTMOTOR);
    analogWrite(rightB, 0);

    previousERROR = currentERROR;




 /* 
  if (L3==1 && L2==0 && L1==0 && CL==0 && CR==0 && R1==0 && R2==0 && R3==0)
  {
    currentERROR = -1.4;   //0001
  }

  if (L3==1 && L2==1 && L1==0 && CL==0 && CR==0 && R1==0 && R2==0 && R3==0)
  {
    currentERROR = -1.2;     //0002
  }

  if (L3==0 && L2==1 && L1==0 && CL==0 && CR==0 && R1==0 && R2==0 && R3==0)
  {
    currentERROR = -1;   //0003
  }

  if (L3==0 && L2==1 && L1==1 && CL==0 && CR==0 && R1==0 && R2==0 && R3==0)
  {
    currentERROR = -0.8;     //0004
  }

  if (L3==0 && L2==0 && L1==1 && CL==0 && CR==0 && R1==0 && R2==0 && R3==0)
  {
    currentERROR = -0.6;   //0005
  }

  if (L3==0 && L2==0 && L1==1 && CL==1 && CR==0 && R1==0 && R2==0 && R3==0)
  {
    currentERROR = -0.4;     //0006
  }

  if (L3==0 && L2==0 && L1==0 && CL==1 && CR==0 && R1==0 && R2==0 && R3==0)
  {
    currentERROR = -0.2;   //0007
  }

  if ((L3==0 && L2==0 && L1==0 && CL==1 && CR==1 && R1==0 && R2==0 && R3==0) || (L3==1 && L2==1 && L1==1 && CL==1 && CR==1 && R1==1 && R2==1 && R3==1))
  {
    currentERROR = 0;      //0008
    FAST = 25;             //0008
  }

  if (L3==0 && L2==0 && L1==0 && CL==0 && CR==1 && R1==0 && R2==0 && R3==0)
  {
    currentERROR = 0.2;    //0009
  }

  if (L3==0 && L2==0 && L1==0 && CL==0 && CR==1 && R1==1 && R2==0 && R3==0)
  {
    currentERROR = 0.4;      //0010
  }

  if (L3==0 && L2==0 && L1==0 && CL==0 && CR==0 && R1==1 && R2==0 && R3==0)
  {
    currentERROR = 0.6;    //0011
  }

  if (L3==0 && L2==0 && L1==0 && CL==0 && CR==0 && R1==1 && R2==1 && R3==0)
  {
    currentERROR = 0.8;      //0012
  }

  if (L3==0 && L2==0 && L1==0 && CL==0 && CR==0 && R1==0 && R2==1 && R3==0)
  {
    currentERROR = 1;    //0013
  }

  if (L3==0 && L2==0 && L1==0 && CL==0 && CR==0 && R1==0 && R2==1 && R3==1)
  {
    currentERROR = 1.2;      //0014
  }

  if (L3==0 && L2==0 && L1==0 && CL==0 && CR==0 && R1==0 && R2==0 && R3==1)
  {
    currentERROR = 1.4;    //0015
  }

 calculatepid();
*/

}
void calibrate_sensor(){
    // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A7, A6, A5, A4, A3, A2, A1, A0}, SensorCount);
 

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

  // analogRead() takes about 0.1 ms on an AVR.
  // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
  // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
 
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  
}

void readSensor8A(){
    position = qtr.readLineBlack(sensorValues);

/*  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }*/
valL3 = sensorValues[0];
valL2 = sensorValues[1];
valL1 = sensorValues[2];
valCL = sensorValues[3];
valCR = sensorValues[4];
valR1 = sensorValues[5];
valR2 = sensorValues[6];
valR3 = sensorValues[7];
if(valL3<300){L3=0;}
else if(valL3>800){L3=1;}

if(valL2<300){L2=0;}
else if(valL2>800){L2=1;}

if(valL1<300){L1=0;}
else if(valL1>800){L1=1;}

if(valCL<300){CL=0;}
else if(valCL>800){CL=1;}

if(valCR<300){CR=0;}
else if(valCR>800){CR=1;}

if(valR1<300){R1=0;}
else if(valR1>800){R1=1;}

if(valR2<300){R2=0;}
else if(valR2>800){R2=1;}

if(valR3<300){R3=0;}
else if(valR3>800){R3=1;}
Serial.print(L3);
Serial.print(L2);
Serial.print(L1);
Serial.print(CL);
Serial.print(CR);
Serial.print(R1);
Serial.print(R2);
Serial.print(R3);
Serial.print(" ");
Serial.print(position);
Serial.print("  ");
}

void readSensor(){
  valsL3 = digitalRead(soL3);
  valsL2 = digitalRead(soL2);
  valsL1 = digitalRead(soL1);
  valsCL = digitalRead(soCL);
  valsCR = digitalRead(soCR);
  valsR1 = digitalRead(soR1);
  valsR2 = digitalRead(soR2);
  valsR3 = digitalRead(soR3);
Serial.print(valsL3);
Serial.print(valsL2);
Serial.print(valsL1);
Serial.print(valsCL);
Serial.print(valsCR);
Serial.print(valsR1);
Serial.print(valsR2);
Serial.println(valsR3);
}


void brake(){

    analogWrite(leftA,255);
    analogWrite(leftB,255);
    analogWrite(rightA,255);
    analogWrite(rightB,255);
    delay(10);
    
    }
