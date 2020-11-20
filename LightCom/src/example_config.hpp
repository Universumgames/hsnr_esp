/*
this is an example config
if you've cloned this project and no config.hpp exists, rename this file and change the settings for your need
if you constribute to this project and you don't have a config.hpp copy this file and rename it to "config.hpp" instead of just renaming this file, so the example_config.hhpp wont't be lost
*/

#pragma once
#include <Arduino.h>

#define BAUD_RATE 9600

#define RX_CLOCK_PIN_0 2
#define RX_CLOCK_PIN_1 3
#define RX_DATA_PIN 4
#define TX_CLOCK_PIN 5
#define TX_DATA_PIN 6

#define TWO_LIGHT_DURATION_STATE 120
#define TWO_LIGHT_BITWISE_DELAY TWO_LIGHT_DURATION_STATE
#define TWO_LIGHT_MIN_SIGNAL_DUR 90