/***************************************************************************
  Example Code of a  sumobot with 2 line trackers and an ultrasonic front obstacle sensors

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

/* Hardware notes
   2 Saleng Trackers on pins headers on
   pin A1(front), A3(rear)
   one ultrasonic sensor on pin headers,
   Trig connected to pin 4 and echo connected to pin 2
   Install right motor(s) on MB0 & MB1
   Install left motor(s) on MA0 & MA1
*/

// change below to define if line
// is black on white background or
// white on black background.
// These define the sensor value when
// under black and white surface
// You may also use the DO and ~DO
// pins of the Saleng Tracker to
// change line configuration

#define BLK LOW  // line
#define WHT HIGH // background

// speed setting based on movement
// 255=full speed
#define SPEED_FORWARD 255
#define SPEED_BACKWARD 255
#define SPEED_ON_TURNS 65

#define BB 9
#define FB 6
#define BA 5
#define FA 3

#define US_TRIG  4
#define US_ECHO  2
#define FRONT_LINE_SENSOR A1
#define REAR_LINE_SENSOR A3

unsigned long us_dist, ir_dist;

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

void us_sensor()
{
  static unsigned long t;
  if (millis() - t < 25) return;
  t = millis();

  unsigned long d;
  float f;
  digitalWrite(US_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(US_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG, LOW);
  d = pulseIn(US_ECHO, HIGH, 15000);
  f = ( (float)d / 29.4 ) / 2;
  d = (unsigned long)f;
  if ( d < 2 ) d = 200;

  if (d < 25 )
  {
    forward();
    delay(100);
  }
  else
  {
    turnleft();
  }
}

// generate a number 0-1
byte generate_random()
{
  randomSeed(micros() % 100);
  return   random(0, 1);
}



void setup() {
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
  pinMode(FRONT_LINE_SENSOR, INPUT);
  pinMode(REAR_LINE_SENSOR, INPUT);

  pinMode(BB, OUTPUT);
  pinMode(FB, OUTPUT);
  pinMode(BA, OUTPUT);
  pinMode(FA, OUTPUT);

  delay(1000); // add 1s delay

}


void loop() {

  if (digitalRead(FRONT_LINE_SENSOR) == LOW) // front sensor was tripped
  {
    // move back
    backward();
    delay(100);
    if (generate_random()) turnright();
    else turnleft();
  }
  else if (digitalRead(REAR_LINE_SENSOR) == LOW) // rear sensor was tripped
  {
    // move forward
    forward();
    delay(100);
    if (generate_random()) turnright();
    else turnleft();
  }
  else // no line sensors were touched so do scan algorithm
  {
    us_sensor();
  }
}
