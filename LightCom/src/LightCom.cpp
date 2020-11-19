#include "LightCom.hpp"

LightCom com = LightCom();
LightCom::LightCom()
{
}

void LightCom::setup()
{
    Serial.begin(BAUD_RATE);
    LightComPins pins;
    pins.rx_clock = RX_CLOCK_PIN;
    pins.rx_data = RX_DATA_PIN;
    pins.tx_clock = TX_CLOCK_PIN;
    pins.tx_data = TX_DATA_PIN;
    Light.begin(pins);
}

void LightCom::loop()
{
    if (Serial)
    {
        String input = Serial.readStringUntil('\n');
        if(input != "\n" && input != "")
            Light.print(input);
    }
}