#pragma once
#include <Arduino.h>
#include "config.hpp"

struct LightComPins
{
    int rx_clock_0;
    int rx_clock_1;
    int rx_data;
    int tx_clock;
    int tx_data;
};

class TwoLight
{
public:
    TwoLight();
    void begin(LightComPins pinConfig);
    void onRecieve();
    void onRecieveEnd();
    void write(bool val);
    void print(char c);
    void print(String s);
private: 
    short currentBit = 7;
    long long lastMillis = 0;
    byte b = 0x0;
    byte tempB = 0x0;
    LightComPins pinConfig;
};

extern TwoLight Light;