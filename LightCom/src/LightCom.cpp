#include "LightCom.hpp"

LightCom::LightCom()
{
}

void LightCom::setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(SENDER_DATA_LED_PIN, OUTPUT);
    pinMode(SENDER_CLOCK_LED_PIN, OUTPUT);
    pinMode(RECIEVER_PIN, INPUT);
}

void LightCom::loop()
{
}
