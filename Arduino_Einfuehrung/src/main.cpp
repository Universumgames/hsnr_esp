#include <Arduino.h>

//led pins
#define red 6
#define green 3
#define yellow 5
//supersonic sensor pins
#define trigger 2 
#define echo 4
//potentiometer
#define pot A0

void allLED(bool value)
{
  digitalWrite(red, value);
  digitalWrite(green, value);
  digitalWrite(yellow, value);
}

void setLED(int value)
{
  allLED(LOW);
  if (value >= 0 && value <= 341)
  {
    digitalWrite(green, HIGH);
  }
  else if (value > 341 && value <= 682)
  {
    digitalWrite(yellow, HIGH);
  }
  else if (value > 682)
  {
    digitalWrite(red, HIGH);
  }
}

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(pot, INPUT);
}

void loop()
{
  setLED(analogRead(pot));
}