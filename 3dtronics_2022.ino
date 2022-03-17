#include <Servo.h>

#define echoPinR 3
#define trigPinR 2
#define echoPinL 6
#define trigPinL 5
#define dcRF 4
#define dcLF 7
#define dcRB 8
#define dcLB 9
#define IR_R 12
#define IR_L 13


int distanceR;
int durationR;
int distanceL;
int durationL;

Servo myservo;  // create servo object to control a servo


Servo myservo2;  // create servo object to control a servo

void moveForward (){
  digitalWrite(dcRF, HIGH);
  digitalWrite(dcRB, LOW);
  digitalWrite(dcLF, LOW);
  digitalWrite(dcLB, HIGH);

}

void moveLeft(){
  digitalWrite(dcRF, HIGH);
  digitalWrite(dcRB, LOW);
  digitalWrite(dcLF, LOW);
  digitalWrite(dcLB, LOW);

}

void moveRight(){
  digitalWrite(dcRF, LOW);
  digitalWrite(dcRB, LOW);
  digitalWrite(dcLF, LOW);
  digitalWrite(dcLB, HIGH);

}

void moveBackward(){
  digitalWrite(dcRF, LOW);
  digitalWrite(dcRB, HIGH);
  digitalWrite(dcLF, HIGH);
  digitalWrite(dcLB, LOW);

}

void moveStop (){
  digitalWrite(dcRF, LOW);
  digitalWrite(dcRB, LOW);
  digitalWrite(dcLF, LOW);
  digitalWrite(dcLB, LOW);
}

void setup()
{
  pinMode(echoPinR, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(dcRF, OUTPUT);
  pinMode(dcLF, OUTPUT);
  pinMode(dcRB, OUTPUT);
  pinMode(dcLB, OUTPUT);
  pinMode(IR_R, INPUT);
  pinMode(IR_L, INPUT);
  myservo.attach(10);
  myservo2.attach(11);
  Serial.begin(9600);
}

void loop()
{
  //Right Ultrasound
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  distanceR = durationR * 0.034 / 2;
  Serial.println("Right: ");
  Serial.println(distanceR);
  
  //Left Ultrasound
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = durationL * 0.034 / 2;
  Serial.println("Left: ");
  Serial.println(distanceL);

  //Movement
  if (distanceR > 20 && distanceL > 20){
    if (digitalRead(IR_R) == HIGH && digitalRead(IR_L) == HIGH)
    {
      moveForward();
    }
    else if (digitalRead(IR_R) == HIGH)
    {
      moveRight();
    }
    else if (digitalRead(IR_L) == HIGH)
    {
      moveLeft();
    }
  }
  
  else if (distanceR < 20)
  {
    myservo.write(180);
    moveStop();
    delay(2500);
  }
  else if (distanceL < 20)
  {
    myservo2.write(180);
    moveStop();
    delay(2500);
  } 
 

}
