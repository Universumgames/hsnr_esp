#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "config.hpp"
#include "TwoLight.hpp"

class LightCom
{
public:
    LightCom();
    void setup();
    void loop();
private:
};

extern LightCom com;