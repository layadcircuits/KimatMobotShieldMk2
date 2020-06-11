/***************************************************************************
  Example Code to move the motor of a 2 or 4 wheel robot driven by the Kimat Mobot Shield Mk2.
  This is meant as a first test code. It moves the robot forward, backward, left and right with certain time intervals.

  This software is free provided that this notice is not removed and proper attribution
  is accorded to Layad Circuits and its Author(s).
  Layad Circuits invests resources in producing free software. By purchasing Layad Circuits'
  products or utilizing its services, you support the continuing development of free software
  for all.

  Author(s): E.A.Binay-an for Layad Circuits Electronics Engineering
  Revision: 1.0.0 - 2020/6/11 - Initial release. Code is based on Mobot Shield
  Layad Circuits Electronics Engineering Supplies and Services
  B314 Lopez Bldg., Session Rd. cor. Assumption Rd., Baguio City, Philippines
  www.layadcircuits.com
  general: info@layadcircuits.com
  sales: sales@layadcircuits.com
  +63-916-442-8565

   NOTES:
   Install right motor(s) on MB0 & MB1
   Install left motor(s) on MA0 & MA1
   When the Single Supply microjumper is installed, install just ONE power source for
   both Arduino (6-12V) and Motors(voltage dependes on motors). This single power source must be a voltage accepted by both Arduino and motors
 ***************************************************************************/

#define BB 9
#define FB 6
#define BA 5
#define FA 3

// speed setting based on movement
// 255=full speed
#define SPEED_FORWARD 100
#define SPEED_BACKWARD 70
#define SPEED_ON_TURNS 80

byte sensorL, sensorC, sensorR;


void forward()
{
  analogWrite(BA, 0);
  analogWrite(FA, SPEED_FORWARD);
  analogWrite(BB, 0);
  analogWrite(FB, SPEED_FORWARD);
}

void backward()
{
  analogWrite(BA, SPEED_BACKWARD);
  analogWrite(FA, 0);
  analogWrite(BB, SPEED_BACKWARD);
  analogWrite(FB, 0);
}

void turnleft()
{
  analogWrite(BA, SPEED_ON_TURNS);
  analogWrite(FA, 0);
  analogWrite(BB, 0);
  analogWrite(FB, SPEED_ON_TURNS);
}

void turnright()
{
  analogWrite(BA, 0);
  analogWrite(FA, SPEED_ON_TURNS);
  analogWrite(BB, SPEED_ON_TURNS);
  analogWrite(FB, 0);
}

void motorstop()
{
  analogWrite(BA, 0);
  analogWrite(FA, 0);
  analogWrite(BB, 0);
  analogWrite(FB, 0);
}

void shortbreak()
{
  analogWrite(BA, 255);
  analogWrite(FA, 255);
  analogWrite(BB, 255);
  analogWrite(FB, 255);
}

void setup() {
  pinMode(BB, OUTPUT);
  pinMode(FB, OUTPUT);
  pinMode(BA, OUTPUT);
  pinMode(FA, OUTPUT);
  delay(3000); // add 3s delay
}

void loop() {
  forward(); delay(1000);
  shortbreak(); delay(100);
  motorstop(); delay(2000);

  backward(); delay(1000);
  shortbreak(); delay(100);
  motorstop(); delay(2000);

  turnleft(); delay(1000);
  shortbreak(); delay(100);
  motorstop(); delay(2000);

  turnright(); delay(1000);
  shortbreak(); delay(100);
  motorstop(); delay(2000);
}
