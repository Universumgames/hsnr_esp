#include "TwoLight.hpp"

TwoLight Light = TwoLight();

void onRXInterrupt()
{
    Light.onRecieve();
}

TwoLight::TwoLight()
{
}

void TwoLight::begin(LightComPins pinConf)
{
    this->pinConfig = pinConf;

    pinMode(pinConfig.rx_clock, INPUT);
    pinMode(pinConfig.rx_data, INPUT);
    pinMode(pinConfig.tx_clock, OUTPUT);
    pinMode(pinConfig.tx_data, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(pinConfig.rx_clock), onRXInterrupt, FALLING);

    digitalWrite(pinConfig.tx_clock, LOW);
    digitalWrite(pinConfig.tx_data, LOW);
}

void TwoLight::onRecieve()
{
    long long delta = millis() - lastMessageMillis;
    if(delta >= TWO_LIGHT_BIT_TIMEOUT){
        if(delta >= TWO_LIGHT_BIT_TIMEOUT && currentBit != 0)
            Serial.println("Byte Timeout");
        else Serial.println();
        currentBit = 0;
        b = 0x0;
    }

    int dataVal = !digitalRead(pinConfig.rx_data);
    bitWrite(b, currentBit, dataVal);
    Serial.print(dataVal);
    if(currentBit >= 7){
        Serial.write(b);
        Serial.println();
        currentBit = 0;
        b = 0x0;
    }
    currentBit++;
    
    lastMessageMillis = millis();
    
}

void TwoLight::write(bool val){
    digitalWrite(pinConfig.tx_data, val);
    digitalWrite(pinConfig.tx_clock, HIGH);
    delay(TWO_LIGHT_DURATION_STATE);
    digitalWrite(pinConfig.tx_clock, LOW);
    digitalWrite(pinConfig.tx_data, LOW);
    delay(TWO_LIGHT_BITWISE_DELAY);
}

void TwoLight::print(char c){
    //LSB als erstes
    Serial.print(c);
    Serial.print(":");
    for(int i = 7; 0 <= i; i --){
        bool bit = bitRead(c, i);
        write(bit);
        Serial.print(bit);
    }
    delay(TWO_LIGHT_BYTE_DELAY);
}

void TwoLight::print(String s){
    byte buffer[s.length()];
    s.getBytes(buffer, s.length());
    for(unsigned int i = 0; i < s.length(); i++){
        print(buffer[i]);
    }
    Serial.println();
}