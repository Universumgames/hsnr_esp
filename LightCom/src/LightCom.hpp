#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "config.hpp"

class LightCom
{
public:
    LightCom();
    void setup();
    void loop();
    void onRecieve(int length);
private:
};

extern LightCom com;