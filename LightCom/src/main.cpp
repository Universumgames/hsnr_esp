/**
 * @file main.cpp
 * @author Arlt, Tom - Meyer, Florian - Mueller, Henning - Koerwer, Florian
 * @brief 
 * @version 0.1
 * @date 2020-11-11
 * 
 * @copyright Copyright (c) 2020
 * Wir entwickeln ein Programm :^)
 */

#include <Arduino.h>
#include <string.h>
#include "config.hpp"
#include "LightCom.hpp"

/*unsigned long lastMillis = 0;
bool lastState = 0;

void start(){
  lastMillis = millis();
}

void end(){
  unsigned long delta = millis()-lastMillis;
  if(delta > 100){
    Serial.println(delta);
    lastMillis = millis();
  }
}*/

void setup() {
  com.setup();
  //pinMode(RX_CLOCK_PIN, INPUT);
  /*pinMode(TX_CLOCK_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(RX_CLOCK_PIN), start, FALLING);
  attachInterrupt(digitalPinToInterrupt(RX_CLOCK_PIN), end, RISING);
  Serial.begin(9600);*/
}

void loop() {
  /*digitalWrite(TX_CLOCK_PIN, HIGH);
  delay(100);
  digitalWrite(TX_CLOCK_PIN, LOW);
  delay(100);*/

  /*bool state = digitalRead(RX_CLOCK_PIN);
  if(state != lastState && lastState == LOW){
    //test();
  }
  lastState = state;*/
  com.loop();
}