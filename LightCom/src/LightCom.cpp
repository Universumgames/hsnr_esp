#include "LightCom.hpp"

LightCom com = LightCom();
LightCom::LightCom()
{
}

void LightCom::setup()
{
    Serial.begin(BAUD_RATE);
    LightComPins pins;
    pins.rx_clock_0 = RX_CLOCK_PIN_0;
    pins.rx_clock_1 = RX_CLOCK_PIN_1;
    pins.rx_data = RX_DATA_PIN;
    pins.tx_clock = TX_CLOCK_PIN;
    pins.tx_data = TX_DATA_PIN;
    Light.begin(pins);
}

void LightCom::loop()
{
    String input = Serial.readString();
    if (input != "\n" && input != "" && input != " ")
        Light.print(input);
}