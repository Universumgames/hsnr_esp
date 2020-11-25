#include <Arduino.h>

//led pins
#define RED 6
#define GREEN 3
#define YELLOW 5
//ultrasonic sensor pins
#define TRIGGER 2
#define ECHO 4
//potentiometer
#define POT A0
//led offset
#define GREEN_END 400
#define GREEN_BEGIN 250
#define YELLOW_END 300
#define YELLOW_BEGIN 150
#define RED_END 200
#define RED_BEGIN 0

//if serial output is needed uncomment next line
//#define SERIAL_DEBUG true
//switch between pwm and default
#define USE_PWM

//1 == true == HIGH
//0 == false == LOW

int mappedVals[10] = {0};
int currentIndex = 0;

//set value for all LEDS
void allLED(bool value)
{
  digitalWrite(RED, value);
  digitalWrite(GREEN, value);
  digitalWrite(YELLOW, value);
}

void setSimpleLED(int value)
{
  allLED(LOW);
  if (value >= 0 && value <= 100)
  {
    digitalWrite(GREEN, HIGH);
  }
  else if (value > 100 && value <= 200)
  {
    digitalWrite(YELLOW, HIGH);
  }
  else if (value > 200)
  {
    digitalWrite(RED, HIGH);
  }
}

void setComplexLED(int pin, int mappedVal, int begin, int end)
{
  if (mappedVal >= begin)
  {
    double val = mappedVal - begin;
    double m = map(val, 0, end - begin, 0, 255);
    if (val > 0)
#ifdef USE_PWM
      analogWrite(pin, m);
#else
      digitalWrite(pin, HIGH);
#endif
#ifdef SERIAL_DEBUG
    Serial.print(m);
#endif
  }
#ifdef SERIAL_DEBUG
  Serial.println();
#endif
}

//get Distance from ultrasonic Sensor
double getDistance()
{
  long time = 0;
  double distance = 0;
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  time = pulseIn(ECHO, HIGH);
  distance = time * 0.017;
  delay(50);
  return distance;
}

void setup()
{
  //initialise Serial if needed
#ifdef SERIAL_DEBUG
  Serial.begin(9600);
  delay(500);
  Serial.println("G\t Y\t R");
#endif

  //define pin usage
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(POT, INPUT);
}

void loop()
{
  //turn all LEDs off
  double dist = getDistance();

  //Smooth transition between three leds
  double mappedVal = map(dist, 0, 37, 0, 370);
  mappedVals[currentIndex] = mappedVal;
  currentIndex++;

//average of last 10 measurements
  if (currentIndex >= 9)
  {
    currentIndex = 0;
    double avgVal = 0;
    for (int i = 0; i <= 9; i++)
    {
      avgVal += mappedVals[i];
    }
    avgVal /= 9;
    //set all LEDs off
    allLED(LOW);

    //set all three leds with pwm
    setComplexLED(RED, avgVal, RED_BEGIN, RED_END);
    setComplexLED(YELLOW, avgVal, YELLOW_BEGIN, YELLOW_END);
    setComplexLED(GREEN, avgVal, GREEN_BEGIN, GREEN_END);
  }
}