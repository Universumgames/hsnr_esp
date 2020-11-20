#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "config.hpp"
#include "TwoLight.hpp"

class LightCom
{
public:
    LightCom();
    //light com setup method
    void setup();
    //light com loop method
    void loop();
private:
};

extern LightCom com;