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
#include "config.hpp"
#include "LightCom.hpp"

void setup() {
  com.setup();
}

void loop() {
  com.loop();
}