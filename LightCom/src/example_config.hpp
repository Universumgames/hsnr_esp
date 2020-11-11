/*
this is an example config
if you've cloned this project and no config.hpp exists, rename this file and change the settings for your need
if you constribute to this project and you don't have a config.hpp copy this file and rename it to "config.hpp" instead of just renaming this file, so the example_config.hhpp wont't be lost
*/

#pragma once

#define BAUD_RATE 115200
#define SENDER_DATA_LED_PIN SDA
#define SENDER_CLOCK_LED_PIN SCL
#define RECIEVER_PIN 7
#define I2C_MASTER_ADRESS 1
#define I2C_SLAVE_ADRESS 2
#define I2C_CLOCK_SPEED 10000