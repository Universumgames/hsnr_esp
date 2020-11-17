#include <Arduino.h>

//led pins
#define RED 6
#define GREEN 3
#define YELLOW 5
//supersonic sensor pins
#define TRIGGER 2
#define ECHO 4
//potentiometer
#define POT A0

//#define SERIAL_DEBUG true

//1 = true = HIGH
//0 = false = LOW

void allLED(bool value)
{
  digitalWrite(RED, value);
  digitalWrite(GREEN, value);
  digitalWrite(YELLOW, value);
}

void setSimpleLED(int value)
{
  allLED(LOW);
  if (value >= 0 && value <= 100)
  {
    digitalWrite(GREEN, HIGH);
  }
  else if (value > 100 && value <= 200)
  {
    digitalWrite(YELLOW, HIGH);
  }
  else if (value > 200 )
  {
    digitalWrite(RED, HIGH);
  }
}

double getDistance()
{
  long time = 0;
  double distance = 0;
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  time = pulseIn(ECHO, HIGH);
  distance = time * 0.017;
  //if (distance <= 40)
    return distance;
  //else
    //return -1;
}

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(9600);
  delay(500);
#endif

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(POT, INPUT);

}

void loop()
{
  double dist = getDistance();
#ifdef SERIAL_DEBUG
  
  String s = String(dist) + "cm";
  Serial.println((dist != -1) ? s : "Distance too large");
// same as
//if (dist != -1)
//    Serial.println(s);
//  else
//    Serial.println("Distance too large");
#endif

  setSimpleLED(map(dist, 0, 37, 0, 370));
}