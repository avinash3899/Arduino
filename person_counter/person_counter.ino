#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DELAY_TIMEOUT 1500
char ssid[] = "Avinash";
char pass[] = "password";
char auth[] = "mBfXwjTn8s9jTYN25R7m-qJxReVtVYKF";
WidgetLCD lcd1(V0);
int ir_right_pin = D1;
int ir_left_pin = D0;
int ir_right_state = 0;
int ir_left_state  = 0;
int ir_right_state_last = -1;
int ir_left_state_last  = -1;
int in_counter = 0;
int out_counter = 0;
bool bWalkIn = false;
bool bWalkOut = false;
unsigned long tm;
int people = 0;
int prev = 0 ;
void setup() {
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
   lcd1.clear();
   pinMode( ir_right_pin, INPUT);
   pinMode( ir_left_pin , INPUT);
   
}

void loop() {
 Blynk.run();
 ir_right_state = digitalRead( ir_right_pin );
 ir_left_state =  digitalRead( ir_left_pin );
 checkWalkIn();
 checkWalkOUT();
 if(out_counter>in_counter)out_counter=in_counter;
 people = in_counter-out_counter;
 if(people < 0)people=0;
 Serial.print( in_counter );
 Serial.print( " " );
 Serial.print( out_counter );
 Serial.print( " " );
 Serial.println(people);
 if(people!=prev){
 lcd1.print(0, 0, "PeopleCount= ");
 lcd1.print(12, 0, people);
 prev=people;
 }
}


void checkWalkIn(){



    if( ir_right_state != ir_right_state_last ){



         ir_right_state_last = ir_right_state;

         if( (bWalkIn == false) && ( ir_right_state == LOW ) ){

              bWalkIn = true;

              tm = millis();

         }

     }



     if( (millis() - tm) > DELAY_TIMEOUT ){

          bWalkIn = false;

     }



     if( bWalkIn && (ir_left_state == LOW) && (ir_right_state == HIGH) ){

          bWalkIn = false;

          in_counter++;

         

     }



}

void checkWalkOUT(){



    if( ir_left_state != ir_left_state_last ){



         ir_left_state_last = ir_left_state;

         if( (bWalkOut == false) && ( ir_left_state == LOW ) ){

              bWalkOut = true;

              tm = millis();

         }

     }



     if( (millis() - tm) > DELAY_TIMEOUT ){

          bWalkOut = false;

     }



     if( bWalkOut && (ir_right_state == LOW) && (ir_left_state == HIGH) ){

          bWalkOut = false;

          out_counter++;

       

     }



     

}
