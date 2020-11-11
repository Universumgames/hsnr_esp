#pragma once
#include <Arduino.h>
#include "config.hpp"

class TwoLight{
public:
    TwoLight();
    void begin();
};

extern TwoLight Light;