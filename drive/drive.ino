#include <SPI.h>
#include <RF24.h>
RF24 radio(7,4);

const byte address[6]="00001";
float pi=3.14;
float max_rpm=50;//max rpm of motors
 float R= 0.008; //radius of wheel in m
  float L= 0.045 ; //distance between wheel in m
  
  int motor1A= 6;                                        
  int motor1B= 5;
  int motor2A= 10;            
  int motor2B= 9;

 uint8_t device_id=1 ;    //bot number or ID number
 float v=0;
 float w;
 int pwm=0;   
  
  struct receive_buffer
  {
    uint8_t ID;
    
    float omega;

    int flag;
    
    };

  receive_buffer data[3];


   
  int rpm2pwm(float rpm) 
   { 
    //Serial.print(rpm);
    int pwm=map(rpm,0,max_rpm,0,255);    //rpm to pwm
    //Serial.print("pwmvalbefore=");
    return(pwm);
   }



  
  float anticlockwise(float vr,int motorA,int motorB)
  { 
    vr=abs(vr);
   int pwm=rpm2pwm(vr) ;
   Serial.print("pwmvalanti = ");
    Serial.print(pwm);              // for anticlockwise rotation
    analogWrite(motorA,pwm); 
    analogWrite(motorB,0); 
   }

    float clockwise(float vr,int motorA,int motorB)
  { 
    vr=abs(vr);
    int pwm=rpm2pwm(vr);
    Serial.print("pwmvalclk = ");
    Serial.print(pwm);
    analogWrite(motorA,0);                             // for clockwise rotation
    analogWrite(motorB,pwm); 
   }
  
  

  
 


void setup() {

  
 Serial.begin(9600);
 pinMode(13,OUTPUT);
 pinMode(motor1A,OUTPUT);
  pinMode(motor1B,OUTPUT);
   pinMode(motor2A,OUTPUT);
    pinMode(motor2B,OUTPUT);

 
 radio.begin();
      //Serial.println("checking if chip connected");
      bool check = radio.isChipConnected();
      Serial.print("check-");
      Serial.println(check);
      /*if(check){
        digitalWrite(13,HIGH);
      }*/
      
      radio.openReadingPipe(0, address);
      radio.setPALevel(RF24_PA_MIN);
      radio.startListening();
  
   
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly
 //receiving data from NRF

    if ( radio.available()) {
      radio.read(&data,sizeof(data));
      //delay(1500);                     
      //Serial.print("ID= ");
    //Serial.println(data[i].ID);
    //Serial.print("vrec= ");
   // Serial.println(data.vel);
       //Serial.print("wrec= ");
    //Serial.println(data.omega);

     for(int i =0;i<3;i++)
     {
      if(data[i].ID == device_id)
      {
        
        w=data[i].omega;
        }}
       
        if (data[0].flag==1)                    //setting linear velocity according to error
        {  v=0.003 ; }
        //Serial.print("vel=");
      //Serial.println(v);
      /* Serial.print("omega=");
       Serial.println(w);*/
     
  }

  //v=0.5;
  //w=0;

  float v_r=((2*v)+(w*L))/(2*R);   //right motor speed in rad/s
  float v_l=((2*v)-(w*L))/(2*R);    //right motor speed in rad/s
 // Serial.println(v_r);
  //Serial.println(v_l);
  
 /* Serial.print("v_r=");
  Serial.println(v_r);
  Serial.print("v_l=");
  Serial.println(v_l);*/
  //calculate rpm from rad/s
  float v_rrpm = (60/(2*pi))*v_r;
  float v_lrpm = (60/(2*pi))*v_l;
  Serial.print(" rightrpm= ");
  Serial.println(v_rrpm);
  Serial.print(" leftrpm= ");
  Serial.println(v_lrpm);
  
  if(v_rrpm < 0)
    {
     anticlockwise(v_rrpm,motor1A,motor1B);
    }
   else
   { 
    clockwise(v_rrpm,motor1A,motor1B);
    }  
   
    if(v_lrpm < 0)
    {
     anticlockwise(v_lrpm,motor2A,motor2B);
    }
   else
   { 
    clockwise(v_lrpm,motor2A,motor2B);
    }  

    //Serial.println();

 
}
