#include <Arduino.h>

//led pins
#define red 6
#define green 3
#define yellow 5
//subsonic sensor pins
#define trigger 2
#define echo 4
//potentiometer
#define pot A0

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(pot, INPUT);
}

void loop() {
  digitalWrite(3, HIGH);
  delay(100);
  digitalWrite(3, LOW);
  delay(100);
}