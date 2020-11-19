#pragma once
#include <Arduino.h>
#include "config.hpp"

struct LightComPins
{
    int rx_clock;
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
    void write(bool val);
    void print(char c);
    void print(String s);
private:
    unsigned short currentBit = 0;
    long long lastMessageMillis = 0;
    byte b = 0x0;
    LightComPins pinConfig;
};

extern TwoLight Light;