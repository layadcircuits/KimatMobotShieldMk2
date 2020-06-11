/***************************************************************************
  Example Code of an obstacle avoidance robot using the Kimat Mobot Shield Mk2,
  an ultrasonic sensor and a 2-wheel (or 4-wheel) robot chassis.

  This software is free provided that this notice is not removed and proper attribution
  is accorded to Layad Circuits and its Author(s).
  Layad Circuits invests resources in producing free software. By purchasing Layad Circuits'
  products or utilizing its services, you support the continuing development of free software
  for all.
  The Kimat Mobot Shield Mk2 is designed and made by Layad Circuits.
  By supporting our products, you support local innovation and share in the movement
  to spur local ingenuity.

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
   one ultrasonic sensor on pin headers,
   Trig connected to pin 4 and echo connected to pin 2
   Install right motor(s) on MB0 & MB1
   Install left motor(s) on MA0 & MA1
*/

// speed setting based on movement
// 255=full speed
#define SPEED_ON_TURNS 100
#define SPEED_FORWARD 100
#define SPEED_BACKWARD 80

#define BB 9
#define FB 6
#define BA 5
#define FA 3
#define PIN_TRIG 4
#define PIN_ECHO 2

const unsigned int MAX_DISTANCE_CM = 100;
const unsigned int THRESHOLD_DISTANCE_CM = 10;
float duration;
float distance;

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

void usRoutine()
{
  static unsigned long t;
  if (millis() - t < 30) return;
  t = millis();
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO, HIGH, 30000);
  distance = duration * 0.034 / 2;
  if ((distance >= MAX_DISTANCE_CM) || (distance < 2))
    distance = MAX_DISTANCE_CM;
}


void mainlogic(float d)
{
  static unsigned long t;
  if (millis() - t < 100) return;
  t = millis();

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  if (d <= THRESHOLD_DISTANCE_CM)
  {
    byte dir;
    shortbreak();
    delay(10);
    motorstop();
    dir = random(0, 2);
    switch (dir)
    {
      case 0:
        backward();
        delay(200);
        break;

      case 1:
        turnleft();
        delay(200);
        break;

      case 2:
        turnright();
        delay(200);
        break;
    }
  }
  else
  {
    forward();
  }
}

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(BB, OUTPUT);
  pinMode(FB, OUTPUT);
  pinMode(BA, OUTPUT);
  pinMode(FA, OUTPUT);

  delay(3000); // add 3s delay before rumbling
}

void loop() {
  usRoutine();
  mainlogic(distance);
}
