/**
 * @file main.cpp
 * @author Arlt, Tom
 * @brief Main file to start program on Arduino Uno/Nano, kept as short as possible
 * @version 0.1
 * @date 2020-11-11
 * 
 * @copyright Copyright (c) 2020
 */

#include <Arduino.h>
#include "config.hpp"
#include "LightCom.hpp"

void setup()
{
  com.setup();
}

void loop()
{
  com.loop();
}