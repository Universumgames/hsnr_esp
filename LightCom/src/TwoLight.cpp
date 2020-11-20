#include "TwoLight.hpp"

TwoLight Light = TwoLight();

//global, non-class method to recieve interrupt
void onRXInterruptRising()
{
    Light.__recieveInterruptEnd();
}
//global, non-class method to recieve interrupt
void onRXInterruptFalling(){
    Light.__recieveInterruptStart();
}

TwoLight::TwoLight()
{
}

void TwoLight::begin(LightComPins pinConf)
{
    this->pinConfig = pinConf;

    //set pin functionality
    pinMode(pinConfig.rx_clock_0, INPUT);
    pinMode(pinConfig.rx_clock_1, INPUT);
    pinMode(pinConfig.rx_data, INPUT);
    pinMode(pinConfig.tx_clock, OUTPUT);
    pinMode(pinConfig.tx_data, OUTPUT);

    //attach Interrupts, RISING and FALLING to debounce signal
    attachInterrupt(digitalPinToInterrupt(pinConfig.rx_clock_0), onRXInterruptRising, RISING);
    attachInterrupt(digitalPinToInterrupt(pinConfig.rx_clock_1), onRXInterruptFalling, FALLING);

    //just to make sure, set both tx pins to low
    digitalWrite(pinConfig.tx_clock, LOW);
    digitalWrite(pinConfig.tx_data, LOW);
}

void TwoLight::__recieveInterruptStart()
{
    //interrupt is called, after voltage from clock pin dropped
    //read data pin value, invert it, because of lm393
    int dataVal = !digitalRead(pinConfig.rx_data);
    //write single bit into temporary byte at location currentBit (it's saved temporary to debounce signal lateron)
    bitWrite(tempB, currentBit, dataVal);
}

void TwoLight::__recieveInterruptEnd()
{
    unsigned long delta = millis() - lastMillis;
    //ensure, that no random bit was dropped
    if(delta > TWO_LIGHT_BYTE_TIMEOUT){
        bool curBit = bitRead(tempB, currentBit);
        tempB = 0x0;
        currentBit = 7;
        bitWrite(tempB, currentBit, curBit);
    }
    //"debounce", lm393 generates some random voltage peaks, this and latency of leds and resistor limits transmission speeeds significantly
    if (delta > TWO_LIGHT_MIN_SIGNAL_DUR)
    {
        b = tempB;
        bitCallback(bitRead(b, currentBit));
        currentBit--;
        //if full byte was recieved
        if (currentBit < 0)
        {
            processChar(b);
            currentBit = 7;
            b = 0x0;
        }
        lastMillis = millis();
    }else //delete data pin read, due to false alarm, see debounce
        tempB = b;
}

void TwoLight::write(bool val)
{
    //I2C adaptation (two channels: clock, data)
    digitalWrite(pinConfig.tx_data, val);
    digitalWrite(pinConfig.tx_clock, HIGH);
    delay(TWO_LIGHT_DURATION_STATE);
    digitalWrite(pinConfig.tx_clock, LOW);
    digitalWrite(pinConfig.tx_data, LOW);
    delay(TWO_LIGHT_BITWISE_DELAY);
}

void TwoLight::print(char c)
{
    //write bits, MSB first
    for (int i = 7; 0 <= i; i--)
    {
        //get single bit at location i
        bool bit = bitRead(c, i);
        //write bit
        write(bit);
    }
}

void TwoLight::print(String s)
{
    //get chars from string
    const char* chars = s.c_str();
    for (unsigned int i = 0; i < s.length(); i++)
    {
        print(chars[i]);
    }
}
void TwoLight::processChar(char c){
    //call char callback
    charCallback(c);
    lineByteCount++;
    currentLine += String(b);
    //after line finished, call line callback and reset for new line to recieve
    if(b == '\n'){
        lineCallback(currentLine, lineByteCount);
        currentLine = "";
        lineByteCount = 0;
    }
}

void TwoLight::setLineRecievedCallback(void (*lineCallback)(String, int)){
    this->lineCallback = lineCallback;
}

void TwoLight::setCharRecievedCallback(void (*charCallback)(char)){
    this->charCallback = charCallback;
}

void TwoLight::setBitRecievedCallback(void (*bitCallback)(bool)){
    this->bitCallback = bitCallback;
}