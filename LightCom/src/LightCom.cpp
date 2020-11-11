#include "LightCom.hpp"

LightCom com = LightCom();

void onRecieveC(int length)
{
    com.onRecieve(length);
}

LightCom::LightCom()
{
}

void LightCom::setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(SENDER_DATA_LED_PIN, OUTPUT);
    pinMode(SENDER_CLOCK_LED_PIN, OUTPUT);
    pinMode(RECIEVER_PIN, INPUT);

    Wire.begin(I2C_MASTER_ADRESS);
    Wire.onReceive(onRecieveC);
}

void LightCom::loop()
{
    if (Serial)
    {
        String input = Serial.readString();
        Wire.beginTransmission(I2C_SLAVE_ADRESS);
        Wire.write(input.c_str());
        Wire.endTransmission();
    }
}

void LightCom::onRecieve(int length)
{
    while (1 < Wire.available())
    {
        char c = Wire.read();
        Serial.print(c);
    }
    int x = Wire.read();
    Serial.println(x);
}
