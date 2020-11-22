#pragma once
#include <Arduino.h>
#include "config.hpp"

//TwoLight configuration, to clean up begin method
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
    //configure TwoLight with custom pin configuration
    //IMPORTANT: rx_clock_0 and rx_clock_1 has to be interupt pins
    void begin(LightComPins pinConfig);
    
    //print single character to stream
    void print(char c);
    //print a string to stream
    //IMPORTANT: reciever will probably only recieve the message properly after line-eending (\n)
    void print(String s);

    //Callback Method, is called after a line is recieved
    //Parameters for Callback: String line, int bytes in Line
    void setLineRecievedCallback(void (*lineCallback)(String, int));
    //Callback Method, is called after char is recieved
    //Parameters for Callback: byte b
    void setCharRecievedCallback(void (*charCallback)(char));
    //Callback Method, is called after a bit is recieved
    //Parameters for callback: bool bit
    void setBitRecievedCallback(void (*bitCallback)(bool));
    
    //internal interrupt callback method
    void __recieveInterruptStart();
    //internal interrupt callback method
    void __recieveInterruptEnd();

    void loop();
private: 
    //write binary value to stream
    void write(bool val);

    //process recieved char
    void processChar(char c);

    short currentBit = 7;
    long long lastMillis = 0;
    byte b = 0x0;
    byte tempB = 0x0;
    LightComPins pinConfig;
    signed int lineByteCount = 0;
    String currentLine = "";
    bool lastClockState = 0;
    char lastChar = '\n';

    //callback methods
    void (*lineCallback)(String, int);
    void (*charCallback)(char);
    void (*bitCallback)(bool);
};

//declare global variable
extern TwoLight Light;