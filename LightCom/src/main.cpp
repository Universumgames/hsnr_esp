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
#include <SoftwareSerial.h>
#include "config.hpp"
#include "LightCom.hpp"

SoftwareSerial recieve(2,3);

void setup() {
  //com.setup();
  Serial.begin(9600);
  recieve.begin(1);
}

void loop() {
  if(recieve.available())
    Serial.write(recieve.read());
  if(Serial.available())
    recieve.write(Serial.read());
  //com.loop();
  //Serial.readString();
}