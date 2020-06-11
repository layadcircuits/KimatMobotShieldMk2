/***************************************************************************
 Line tracing example using the Kimat MoBot Shield Mk2.
 
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

 * NOTES:
 * Install right motor(s) on MB0 & MB1
 * Install left motor(s) on MA0 & MA1
 * When the Single Supply microjumper is installed, install just ONE power source for 
 * both Arduino (6-12V) and Motors(voltage dependes on motors). This single power source must be a voltage accepted by both Arduino and motors
 ***************************************************************************/

/* Hardware notes
 * 3 Saleng Trackers on pins headers on
 * pin A0(left), A1(center), A2(right)
 * Install right motor(s) on MB0 & MB1
 * Install left motor(s) on MA0 & MA1
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

#define BB 9
#define FB 6
#define BA 5
#define FA 3
#define SENSOR_L A0
#define SENSOR_C A1
#define SENSOR_R A2

// speed setting based on movement
// 255=full speed
#define SPEED_FORWARD 75
#define SPEED_BACKWARD 60
#define SPEED_ON_TURNS 60

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
  pinMode(SENSOR_L, INPUT);
  pinMode(SENSOR_C, INPUT);
  pinMode(SENSOR_R, INPUT);
  pinMode(BB, OUTPUT);
  pinMode(FB, OUTPUT);
  pinMode(BA, OUTPUT);
  pinMode(FA, OUTPUT);
  delay(3000); // add 5s delay 

}

void loop() {

  // read and store all sensors
  sensorL = digitalRead(SENSOR_L);
  sensorC = digitalRead(SENSOR_C);  
  sensorR = digitalRead(SENSOR_R);  

  if(sensorL == BLK && sensorC == BLK && sensorR == BLK)
  {
    //do nothing
  }
  else if(sensorL == WHT && sensorC == BLK && sensorR == BLK)
  {
    turnright();
  }
  else if(sensorL == WHT && sensorC == BLK && sensorR == WHT)
  {
    // confused! Just move forward
    forward();
  }  
  else if(sensorL == BLK && sensorC == BLK && sensorR == WHT)
  {
    turnleft();
  }
  else if(sensorL == BLK && sensorC == WHT && sensorR == BLK)
  {
    forward();
  }  
  else if(sensorL == WHT && sensorC == WHT && sensorR == BLK)
  {
    turnright();
  }
  else if(sensorL == WHT && sensorC == WHT && sensorR == WHT)
  {
    forward();
  }   
  else if(sensorL == BLK && sensorC == WHT && sensorR == WHT)
  {
    turnleft();
  } 
}
