#include "LightCom.hpp"

//global, non-class method to recieve interrupt
void lineCallback(String line, int bytes)
{
    Serial.println();
    Serial.println(line);
    Serial.print(bytes);
    Serial.println(" Bytes recieved in current line");
    Serial.println("Waiting for new signal....");
}

void bitCallback(bool bit){
    Serial.print(bit);
}

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
    Light.setLineRecievedCallback(lineCallback);
    Light.setBitRecievedCallback(bitCallback);
}

void LightCom::loop()
{
    Light.loop();
    if (Serial.available())
    {
        String input = Serial.readString();
        if (input != "\n" && input != "" && input != " ")
            Light.println(input);
    }
}