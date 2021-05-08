#include <AFMotor.h>
//#include <HCSR04.h>


//defining pins and variables
//#define TRIG_PIN D9 
//#define ECHO_PIN D10 
#define MAX_DISTANCE 200 
#define MAX_SPEED 200 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

//defining motors,servo,sensor

AF_DCMotor motor1(1, MOTOR12_8KHZ); 
AF_DCMotor motor2(2, MOTOR12_8KHZ);
//UltraSonicDistanceSensor distanceSensor1(9, 10);  // Initialize sensor that uses digital pins 13 and 12.

//UltraSonicDistanceSensor distanceSensor2(1, 2);

//UltraSonicDistanceSensor distanceSensor3(13, 12);
  
//defining global variables
boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup () {
      // We initialize serial connection so that we could print values from sensor.
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=50)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }
  else
  {
    turnLeft();
    moveStop();
  }
 }
 else
 {
  moveForward();
 }

 //reseting the variable after the operations
 distance = readPing();
// correction_left();
}
int usmeasure(int trig1,int echo1) {
  long duration;
  int cm;
   pinMode(trig1, OUTPUT);
   digitalWrite(trig1, LOW);
   delayMicroseconds(2);
   digitalWrite(trig1, HIGH);
   delayMicroseconds(10);
   digitalWrite(trig1, LOW);
   pinMode(echo1, INPUT);
   duration = pulseIn(echo1, HIGH);
   cm = duration/ 29 / 2;
   return cm;
}

int lookRight()
{
    int distance = usmeasure(16,17);
    delay(100);
    return distance;
    delay(100);
}

int lookLeft()
{
     int distance = usmeasure(9,10);
    delay(100);
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = usmeasure(14,15) ;
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);      
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);     
  delay(300);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);     
  delay(300);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
}  
/*void correction_left()
{{int a,b,c,d;
  a= usmeasure(9,10);

c= usmeasure(14,15);
delay (1000);
b= usmeasure(9,10);
d= usmeasure(14,15);
if(a+c==b+d)
{
while(a<b)
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
  a=usmeasure(9,10);

delay (100);
b=usmeasure(9,10);

if(a==b)
{break;
}
}
while(a>b)
{
   motor1.setSpeed(0);
  motor1.run(RELEASE); //turn motor1 off
  motor2.setSpeed(255);   //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  a=usmeasure(9,10);

delay (100);
b=usmeasure(9,10);

if(a==b)
{break;
}
}
}}} */

  
