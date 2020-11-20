#include "TwoLight.hpp"

TwoLight Light = TwoLight();

void onRXInterruptRising()
{
    Light.onRecieveEnd();
}

void onRXInterruptFalling(){
    Light.onRecieve();
}

TwoLight::TwoLight()
{
}

void TwoLight::begin(LightComPins pinConf)
{
    this->pinConfig = pinConf;

    pinMode(pinConfig.rx_clock_0, INPUT);
    pinMode(pinConfig.rx_clock_1, INPUT);
    pinMode(pinConfig.rx_data, INPUT);
    pinMode(pinConfig.tx_clock, OUTPUT);
    pinMode(pinConfig.tx_data, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(pinConfig.rx_clock_0), onRXInterruptRising, RISING);
    attachInterrupt(digitalPinToInterrupt(pinConfig.rx_clock_1), onRXInterruptFalling, FALLING);

    digitalWrite(pinConfig.tx_clock, LOW);
    digitalWrite(pinConfig.tx_data, LOW);
}

void TwoLight::onRecieve()
{
    int dataVal = !digitalRead(pinConfig.rx_data);
    bitWrite(tempB, currentBit, dataVal);
}

void TwoLight::onRecieveEnd()
{
    unsigned long delta = millis() - lastMillis;
    if (delta > TWO_LIGHT_MIN_SIGNAL_DUR)
    {
        b = tempB;
        Serial.print(bitRead(b, currentBit));
        currentBit--;
        if (currentBit < 0)
        {
            Serial.print(": ");
            Serial.write(b);
            Serial.print(": ");
            Serial.print(b, BIN);
            Serial.println();
            currentBit = 7;
            b = 0x0;
        }
        digitalWrite(7, LOW);
        lastMillis = millis();
    }else tempB = b;
    
}

void TwoLight::write(bool val)
{
    digitalWrite(pinConfig.tx_data, val);
    digitalWrite(pinConfig.tx_clock, HIGH);
    delay(TWO_LIGHT_DURATION_STATE);
    digitalWrite(pinConfig.tx_clock, LOW);
    digitalWrite(pinConfig.tx_data, LOW);
    delay(TWO_LIGHT_BITWISE_DELAY);
}

void TwoLight::print(char c)
{
    //MSB als erstes
    Serial.print(c);
    Serial.print(":");
    for (int i = 7; 0 <= i; i--)
    {
        bool bit = bitRead(c, i);
        write(bit);
        Serial.print(bit);
    }
    //delay(TWO_LIGHT_BYTE_DELAY);
}

void TwoLight::print(String s)
{
    const char* chars = s.c_str();
    for (unsigned int i = 0; i < s.length(); i++)
    {
        print(chars[i]);
    }
    Serial.println();
}