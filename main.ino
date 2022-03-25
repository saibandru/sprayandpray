#include <Servo.h>

// Initialising each of the pins to a variable
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

// For ultrasonic sensor's calculation
int distanceR;
int durationR;
int distanceL;
int durationL;

Servo myservo;  // create servo object to control a servo


Servo myservo2;  // create servo object to control a servo

void moveForward (){ // A function to move the robot forward (voltages for the motor driver)
  digitalWrite(dcRF, HIGH);
  digitalWrite(dcRB, LOW);
  digitalWrite(dcLF, LOW);
  digitalWrite(dcLB, HIGH);

}

void moveLeft(){ // A function to move the robot left (voltages for the motor driver)
  digitalWrite(dcRF, HIGH);
  digitalWrite(dcRB, LOW);
  digitalWrite(dcLF, LOW);
  digitalWrite(dcLB, LOW);

}

void moveRight(){ // A function to move the robot right (voltages for the motor driver)
  digitalWrite(dcRF, LOW);
  digitalWrite(dcRB, LOW);
  digitalWrite(dcLF, LOW);
  digitalWrite(dcLB, HIGH);

}

void moveBackward(){ // A function to move the robot backwards (voltages for the motor driver)
  digitalWrite(dcRF, LOW);
  digitalWrite(dcRB, HIGH);
  digitalWrite(dcLF, HIGH);
  digitalWrite(dcLB, LOW);

}

void moveStop (){ // A function to stop the robot (voltages for the motor driver)
  digitalWrite(dcRF, LOW);
  digitalWrite(dcRB, LOW);
  digitalWrite(dcLF, LOW);
  digitalWrite(dcLB, LOW);
}

void setup() // Enabling the respective pins to read input/send output
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
  // Right Ultrasound - checking the distance of the surface from it
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  distanceR = durationR * 0.034 / 2;
  Serial.println("Right: ");
  Serial.println(distanceR);
  
  // Left Ultrasound - checking the distance of the surface from it
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = durationL * 0.034 / 2;
  Serial.println("Left: ");
  Serial.println(distanceL);

  // Movement - ensures that the robot does not deviate from its intended path 
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
  
  else if (distanceR < 20) // Spray on the right side if there is a table surface
  {
    myservo.write(180);
    moveStop();
    delay(2500);
  }
  else if (distanceL < 20) // Spray on the left side if there is a table surface
  {
    myservo2.write(180);
    moveStop();
    delay(2500);
  } 
 

}
