#include <QueueList.h>
#include <StackArray.h>


boolean son = false;
boolean deneme = false;
boolean turnback = false;
int motor1A = 12; //Burayı güncelle baba
//int motor1B = 0;
int motor1E = 3;
int motor2A = 13;
//int motor2B = 0;
int motor2E = 11;
boolean gayfatih = true;
boolean finish = false;
/*ArrayList<Integer> yol = new ArrayList<Integer>();
ArrayList<Integer> geridon = new ArrayList<Integer>();*/
int THRESHOLD = 42;
const int echoPin2 = 9;
const int trigPin2 = 8;
const int echoPin3 = 6;
const int trigPin3 = 7;
const int echoPin4 = 2;
const int trigPin4 = 10;
int sageski = 0;
int soleski = 0;
int oneski = 0;
boolean sagadonus = true;
boolean soladonus = true;

boolean geridon = false;
boolean turn = false;
int baban = 0;
int a = 0;

StackArray <int> righthandstack;
StackArray <int> lefthandstack;
StackArray<int> dogrustack;
StackArray<int> BABANSTACK;

boolean turnbacktime = false;
boolean righthandrule = true;
boolean lefthandrule = false;



void setup() {
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(motor1E, OUTPUT);
  pinMode(motor2E, OUTPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  Serial.begin(9600);
  forward(70);
  delay(50);
  forward(0);
}

void loop() {

  long duration2, sag;
  long duration3, sol;
  long duration4, on;


  /*while(getRect == 0 && digitalRead(button) == LOW) { //button basılı değilse
    digitalWrite(LED, !digitalRead(LED));
    delay(50);
  }*/
  //getRect = 1;
  //*************
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);


  duration2 = pulseIn(echoPin2, HIGH);

  // convert the time into a distance
  sag = duration2 / 10;

  //Serial.print(sag);



  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);


  duration3 = pulseIn(echoPin3, HIGH);

  // convert the time into a distance
  sol = duration3 / 10;
  /*Serial.print(" ");
  Serial.print(sol);*/


  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);



  duration4 = pulseIn(echoPin4, HIGH);

  // convert the time into a distance
  on = duration4 / 10;
  if (sag < THRESHOLD) {
    sagadonus = true;
  }
  if (sol < THRESHOLD) {
    soladonus = true;
  }
  if (sagadonus && soladonus) {
    baban = false;
  }
  //sag el kurali
  if (righthandrule) {
    if (sol > 500 && on > 500 && sag > 500) {
      right(90);
      delay(240);
      right(0);
      delay(500);
      right(90);
      delay(240);
      right(0);
      righthandrule = false;
      lefthandrule = true;
      delay(10000);

    }
    else if (sag > THRESHOLD + 40 && sol > THRESHOLD + 40 && sagadonus && on > THRESHOLD - 15) {
      for (int i = 0; i < 2; i++) {
        forward(20);
        delay(170);
        forward(0);
      }
      right(90);
      delay(240);
      right(0);
      sagadonus = false;
      soladonus = false;
      righthandstack.push(4);
    }
    else if (on > THRESHOLD + 40 && sag > THRESHOLD + 40 && sagadonus) {
      for (int i = 0; i < 4; i++) {
        forward(20);
        delay(170);
        forward(0);
      }
      right(90);
      delay(240);
      right(0);
      sagadonus = false;
      soladonus = false;
      righthandstack.push(4);
    }
    else if (sol > THRESHOLD + 40 && on > THRESHOLD + 40 && soladonus) {
      forward(20);
      delay(180);
      forward(0);
      righthandstack.push(1);
      soladonus = false;
    }
    else if (on > THRESHOLD - 15) {
      if (sag > sol) {
        digitalWrite(motor1A, LOW);
        digitalWrite(motor2A, LOW);
        analogWrite(motor1E, 22);
        analogWrite(motor2E, 15);
        delay(180);
        forward(0);
      }
      else if (sol > sag) {
        digitalWrite(motor1A, LOW);
        digitalWrite(motor2A, LOW);
        analogWrite(motor1E, 15);
        analogWrite(motor2E, 22);
        delay(180);
        forward(0);
      }
      else {
        forward(20);
        delay(180);
        forward(0);
      }

    }
    else if (sag > THRESHOLD && sagadonus) {
      right(90);
      delay(240);
      right(0);
      sagadonus = false;
      for (int i = 0; i < 2; i++) {
        forward(20);
        delay(170);
        forward(0);
      }
      righthandstack.push(4);
    }
    else if (sol > THRESHOLD && soladonus) {
      left(90);
      delay(240);
      left(0);
      soladonus = false;
      for (int i = 0; i < 2; i++) {
        forward(20);
        delay(170);
        forward(0);
      }
      righthandstack.push(5);
    }
    else if (sagadonus && soladonus) {
      right(90);
      delay(240);
      right(0);
      delay(500);
      right(90);
      delay(240);
      right(0);
      delay(500);
    }
    else {
      sagadonus = true;
      soladonus = true;
    }
  }
  //sol el kurali
  else if (lefthandrule) {
    if (sol > 500 && on > 500 && sag > 500) {
        right(90);
        delay(240);
        right(0);
        delay(500);
        right(90);
        delay(240);
        right(0);
        lefthandrule = false;
        deneme = true;
        delay(10000);

      }
      else if (sag > THRESHOLD+40 && sol > THRESHOLD+40 && soladonus && on > THRESHOLD - 15) {
        for (int i = 0; i < 2; i++) {
          forward(20);
          delay(170);
          forward(0);
        }
        left(90);
        delay(240);
        left(0);
        sagadonus = false;
        soladonus = false;
        lefthandstack.push(4);
      }
      else if (on > THRESHOLD+40 && sol > THRESHOLD+40 && soladonus) {
        for (int i = 0; i < 4; i++) {
          forward(20);
          delay(170);
          forward(0);
        }
        left(90);
        delay(240);
        left(0);
        sagadonus = false;
        soladonus = false;
        lefthandstack.push(4);
      }
      else if (sag > THRESHOLD+40 && on > THRESHOLD+40 && sagadonus) {
        forward(20);
        delay(180);
        forward(0);
        lefthandstack.push(1);
        sagadonus = false;
      }
      else if (on > THRESHOLD - 15) {
        if (sag > sol) {
          digitalWrite(motor1A, LOW);
          digitalWrite(motor2A, LOW);
          analogWrite(motor1E, 22);
          analogWrite(motor2E, 15);
          delay(180);
          forward(0);
        }
        else if (sol > sag) {
          digitalWrite(motor1A, LOW);
          digitalWrite(motor2A, LOW);
          analogWrite(motor1E, 15);
          analogWrite(motor2E, 22);
          delay(180);
          forward(0);
        }
        else {
          forward(20);
          delay(180);
          forward(0);
        }

      }
      else if (sol > THRESHOLD && soladonus) {
        left(90);
        delay(240);
        left(0);
        soladonus = false;
        for (int i = 0; i < 2; i++) {
          forward(20);
          delay(170);
          forward(0);
        }
        lefthandstack.push(4);
      }
      else if (sag > THRESHOLD && sagadonus) {
        right(90);
        delay(240);
        right(0);
        sagadonus = false;
        for (int i = 0; i < 2; i++) {
          forward(20);
          delay(170);
          forward(0);
        }
        lefthandstack.push(5);
      }
      else if (sagadonus && soladonus) {
        right(90);
        delay(240);
        right(0);
        delay(500);
        right(90);
        delay(240);
        right(0);
        delay(500);
      }
      else {
        sagadonus = true;
        soladonus = true;
      }
  }
  // daha kisa yoldaki yanlislari eleme
  else if (deneme) {
    if (righthandstack.count() <= lefthandstack.count()) {
      if (!(turnbacktime)) {
        if (sol > 500 && on > 500 && sag > 500) {
          right(90);
          delay(240);
          right(0);
          delay(500);
          right(90);
          delay(240);
          right(0);
          deneme = false;
          son = true;
          int yeah = dogrustack.count();
          for (int i = 0; i < yeah; i++) {
            BABANSTACK.push(dogrustack.pop());
          }
          a = BABANSTACK.pop();
          delay(10000);

        }
        else if (sag > THRESHOLD + 40 && sol > THRESHOLD + 40 && sagadonus && on > THRESHOLD - 15) {
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          soladonus = false;
          dogrustack.push(4);
        }
        else if (on > THRESHOLD + 40 && sag > THRESHOLD + 40 && sagadonus) {
          for (int i = 0; i < 4; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          soladonus = false;
          dogrustack.push(4);
        }
        else if (sol > THRESHOLD + 40 && on > THRESHOLD + 40 && soladonus) {
          forward(20);
          delay(180);
          forward(0);
          dogrustack.push(1);
          soladonus = false;
        }
        else if (on > THRESHOLD - 15) {
          if (sag > sol) {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 22);
            analogWrite(motor2E, 15);
            delay(180);
            forward(0);
          }
          else if (sol > sag) {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 15);
            analogWrite(motor2E, 22);
            delay(180);
            forward(0);
          }
          else {
            forward(20);
            delay(180);
            forward(0);
          }

        }
        else if (sag > THRESHOLD && sagadonus) {
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          dogrustack.push(4);
        }
        else if (sol > THRESHOLD && soladonus) {
          left(90);
          delay(240);
          left(0);
          soladonus = false;
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          dogrustack.push(5);
        }
        else if (sagadonus && soladonus) {
          right(90);
          delay(240);
          right(0);
          delay(500);
          right(90);
          delay(240);
          right(0);
          delay(500);
          turnbacktime = true;
          delay(2000);
        }
        else {
          sagadonus = true;
          soladonus = true;
        }
      }
      else if (turnbacktime) {
        if (sag > THRESHOLD && sol > THRESHOLD && sagadonus && on > THRESHOLD - 15) {
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          turnbacktime = false;
          dogrustack.pop();
          dogrustack.push(1);
          delay(2000);
        }
        else if (on > THRESHOLD + 40 && sag > THRESHOLD + 40 && sagadonus) {
          for (int i = 0; i < 4; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          turnbacktime = false;
          dogrustack.pop();
          dogrustack.push(5);
          delay(2000);
        }
        else if (sol > THRESHOLD + 40 && on > THRESHOLD + 40 && soladonus) {
          forward(20);
          delay(180);
          forward(0);
          turnbacktime = false;
          dogrustack.pop();
          dogrustack.push(5);
          soladonus = false;
          delay(2000);
        }
        else if (on > THRESHOLD - 10) {
          if (sag > sol) {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 22);
            analogWrite(motor2E, 15);
            delay(180);
            forward(0);
          }
          else if (sol > sag) {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 15);
            analogWrite(motor2E, 22);
            delay(180);
            forward(0);
          }
          else {
            forward(20);
            delay(180);
            forward(0);
          }

        }
        else if (sag > THRESHOLD && sagadonus) {
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          dogrustack.pop();
        }
        else if (sol > THRESHOLD && soladonus) {
          left(90);
          delay(240);
          left(0);
          soladonus = false;
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          dogrustack.pop();
        }
        else {
          sagadonus = true;
          soladonus = true;
        }
      }
    }
    else if (lefthandstack.count() < righthandstack.count()) {
      if (!(turnbacktime)) {
        if (sol > 500 && on > 500 && sag > 500) {
          right(90);
          delay(240);
          right(0);
          delay(500);
          right(90);
          delay(240);
          right(0);
          deneme = false;
          son = true;
          int yeah = dogrustack.count();
          for (int i = 0; i < yeah; i++) {
            BABANSTACK.push(dogrustack.pop());
          }
          a = BABANSTACK.pop();
          delay(10000);

        }
        else if (sag > THRESHOLD + 40 && sol > THRESHOLD + 40 && soladonus && on > THRESHOLD - 15) {
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          left(90);
          delay(240);
          left(0);
          sagadonus = false;
          soladonus = false;
          dogrustack.push(5);
        }
        else if (on > THRESHOLD + 40 && sol > THRESHOLD + 40 && soladonus) {
          for (int i = 0; i < 4; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          soladonus = false;
          dogrustack.push(5);
        }
        else if (sag > THRESHOLD + 40 && on > THRESHOLD + 40 && sagadonus) {
          forward(20);
          delay(180);
          forward(0);
          dogrustack.push(1);
          sagadonus = false;
        }
        else if (on > THRESHOLD - 15) {
          if (sag > sol) {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 22);
            analogWrite(motor2E, 15);
            delay(180);
            forward(0);
          }
          else if (sol > sag) {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 15);
            analogWrite(motor2E, 22);
            delay(180);
            forward(0);
          }
          else {
            forward(20);
            delay(180);
            forward(0);
          }

        }
        else if (sol > THRESHOLD && soladonus) {
          left(90);
          delay(240);
          left(0);
          soladonus = false;
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          dogrustack.push(5);
        }
        else if (sag > THRESHOLD && sagadonus) {
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          dogrustack.push(4);
        }
        else if (sagadonus && soladonus) {
          right(90);
          delay(240);
          right(0);
          delay(500);
          right(90);
          delay(240);
          right(0);
          delay(500);
          turnbacktime = true;
          delay(2000);
        }
        else {
          sagadonus = true;
          soladonus = true;
        }
      }
      else if (turnbacktime) {
        if (sag > THRESHOLD && sol > THRESHOLD && soladonus && on > THRESHOLD - 15) {
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          left(90);
          delay(240);
          left(0);
          soladonus = false;
          turnbacktime = false;
          dogrustack.pop();
          dogrustack.push(1);
          delay(2000);
        }
        else if (on > THRESHOLD + 40 && sol > THRESHOLD + 40 && soladonus) {
          for (int i = 0; i < 4; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          left(90);
          delay(240);
          left(0);
          soladonus = false;
          turnbacktime = false;
          dogrustack.pop();
          dogrustack.push(5);
          delay(2000);
        }
        else if (sag > THRESHOLD + 40 && on > THRESHOLD + 40 && sagadonus) {
          forward(20);
          delay(180);
          forward(0);
          turnbacktime = false;
          dogrustack.pop();
          dogrustack.push(5);
          sagadonus = false;
          delay(2000);
        }
        else if (on > THRESHOLD - 10) {
          if (sag > sol) {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 22);
            analogWrite(motor2E, 15);
            delay(180);
            forward(0);
          }
          else if (sol > sag) {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 15);
            analogWrite(motor2E, 22);
            delay(180);
            forward(0);
          }
          else {
            forward(20);
            delay(180);
            forward(0);
          }

        }
        else if (sol > THRESHOLD && soladonus) {
          left(90);
          delay(240);
          left(0);
          soladonus = false;
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          dogrustack.pop();
        }
        else if (sag > THRESHOLD && sagadonus) {
          right(90);
          delay(240);
          right(0);
          sagadonus = false;
          for (int i = 0; i < 2; i++) {
            forward(20);
            delay(170);
            forward(0);
          }
          dogrustack.pop();
        }
        else {
          sagadonus = true;
          soladonus = true;
        }
      }
    }
    // son gidis
    else if (son) {
      if (righthandstack.count() <= lefthandstack.count()) {
        if (a == 31) {
          forward(20);
          delay(180);
          forward(0);
        }
        else if (baban) {
          forward(20);
          delay(180);
          forward(0);
        }
        else if (a == 4) {
          if (sag > THRESHOLD + 40 && sol > THRESHOLD + 40 && sagadonus) {
            for (int i = 0; i < 2; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            baban = true;
            right(90);
            delay(240);
            right(0);
            sagadonus = false;
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
          else if (on > THRESHOLD + 40 && sag > THRESHOLD + 40 && sagadonus) {
            for (int i = 0; i < 4; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            baban = true;
            right(90);
            delay(240);
            right(0);
            sagadonus = false;
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
          else if (on > THRESHOLD - 10) {
            if (sag > sol) {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 22);
              analogWrite(motor2E, 15);
              delay(180);
              forward(0);
            }
            else if (sol > sag) {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 15);
              analogWrite(motor2E, 22);
              delay(180);
              forward(0);
            }
            else {
              forward(20);
              delay(180);
              forward(0);
            }

          }
          else if (sag > THRESHOLD && sagadonus) {
            right(90);
            delay(240);
            right(0);
            sagadonus = false;
            baban = true;
            for (int i = 0; i < 2; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
        }
        else if (a == 5) {
          if (sag > THRESHOLD + 40 && sol > THRESHOLD + 40 && soladonus) {
            for (int i = 0; i < 2; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            left(90);
            delay(240);
            left(0);
            soladonus = false;
            baban = true;
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
          else if (sol > THRESHOLD + 40 && on > THRESHOLD + 40 && soladonus) {
            for (int i = 0; i < 4; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            baban = true;
            left(90);
            delay(240);
            left(0);
            soladonus = false;
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
          else if (on > THRESHOLD - 10) {
            if (sag > sol) {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 22);
              analogWrite(motor2E, 15);
              delay(180);
              forward(0);
            }
            else if (sol > sag) {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 15);
              analogWrite(motor2E, 22);
              delay(180);
              forward(0);
            }
            else {
              forward(20);
              delay(180);
              forward(0);
            }

          }
          else if (sol > THRESHOLD && soladonus) {
            baban = true;
            left(90);
            delay(240);
            left(0);
            soladonus = false;
            for (int i = 0; i < 2; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
        }
        else if (a == 1) {
          if (on > THRESHOLD && sag > THRESHOLD && sagadonus) {
            sagadonus = false;
            for (int i = 0; i < 4; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
            baban = true;
          }
          else {
            forward(20);
            delay(170);
            forward(0);
          }
        }
      }
      else if (lefthandstack.count() <= righthandstack.count()) {
        if (a == 31) {
          forward(20);
          delay(180);
          forward(0);
        }
        else if (baban) {
          forward(20);
          delay(180);
          forward(0);
        }
        else if (a == 5) {
          if (sol > THRESHOLD + 40 && sag > THRESHOLD + 40 && soladonus) {
            for (int i = 0; i < 2; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            baban = true;
            left(90);
            delay(240);
            left(0);
            soladonus = false;
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
          else if (on > THRESHOLD + 40 && sol > THRESHOLD + 40 && soladonus) {
            for (int i = 0; i < 4; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            baban = true;
            left(90);
            delay(240);
            left(0);
            soladonus = false;
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
          else if (on > THRESHOLD - 10) {
            if (sag > sol) {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 22);
              analogWrite(motor2E, 15);
              delay(180);
              forward(0);
            }
            else if (sol > sag) {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 15);
              analogWrite(motor2E, 22);
              delay(180);
              forward(0);
            }
            else {
              forward(20);
              delay(180);
              forward(0);
            }

          }
          else if (sol > THRESHOLD && soladonus) {
            left(90);
            delay(240);
            left(0);
            soladonus = false;
            baban = true;
            for (int i = 0; i < 2; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
        }
        else if (a == 4) {
          if (sag > THRESHOLD + 40 && sol > THRESHOLD + 40 && sagadonus) {
            for (int i = 0; i < 2; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            right(90);
            delay(240);
            right(0);
            sagadonus = false;
            baban = true;
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
          else if (sag > THRESHOLD + 40 && on > THRESHOLD + 40 && sagadonus) {
            for (int i = 0; i < 4; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            baban = true;
            right(90);
            delay(240);
            right(0);
            sagadonus = false;
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
          else if (on > THRESHOLD - 10) {
            if (sag > sol) {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 22);
              analogWrite(motor2E, 15);
              delay(180);
              forward(0);
            }
            else if (sol > sag) {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 15);
              analogWrite(motor2E, 22);
              delay(180);
              forward(0);
            }
            else {
              forward(20);
              delay(180);
              forward(0);
            }

          }
          else if (sag > THRESHOLD && sagadonus) {
            baban = true;
            right(90);
            delay(240);
            right(0);
            sagadonus = false;
            for (int i = 0; i < 2; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
          }
        }
        else if (a == 1) {
          if (on > THRESHOLD && sag > THRESHOLD && soladonus) {
            soladonus = false;
            for (int i = 0; i < 4; i++) {
              forward(20);
              delay(170);
              forward(0);
            }
            if (BABANSTACK.count() > 0) {
              a = BABANSTACK.pop();
            }
            else {
              a = 31;
            }
            baban = true;
          }
          else {
            forward(20);
            delay(170);
            forward(0);
          }
        }
      }
    }
  }
  //****************





  void forward(int powa) {
    digitalWrite(motor1A, LOW);
    digitalWrite(motor2A, LOW);
    analogWrite(motor1E, powa);
    analogWrite(motor2E, powa);
  }

  void backward(int powa) {
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor2A, HIGH);
    analogWrite(motor1E, powa);
    analogWrite(motor2E, powa);
  }

  void left(int powa) {
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor2A, LOW);
    analogWrite(motor1E, powa);
    analogWrite(motor2E, powa);
  }

  void right(int powa) {
    digitalWrite(motor1A, LOW);
    digitalWrite(motor2A, HIGH);
    analogWrite(motor1E, powa);
    analogWrite(motor2E, powa);
  }
