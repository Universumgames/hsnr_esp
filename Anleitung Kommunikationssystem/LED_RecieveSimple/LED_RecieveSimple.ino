//init variables
int LDR = 2;
int ClockCounter = 0;
int FlashCounter = 0;
int MaxValue = 2500;
int HighFlanke = 0;
int Flash;
unsigned long long lastmillis = 0;
int skippedMillis = 0;

void setup()
{
  //init serial monitor
  Serial.begin(9600);
  //init pinmode
  pinMode(LDR, INPUT);
}

void loop()
{
  ClockCounter++;
  //red LDR value
  Flash = digitalRead(LDR);
  if (Flash)
  {
    HighFlanke = 1;
  }
  //if LDR value changes from HIGH to LOW
  if (!Flash && HighFlanke)
  {
    HighFlanke = 0;
    //increment flashcounter
    long delta = millis() - lastmillis;
    if (delta >= 500 || skippedMillis >= 500)
    {
      FlashCounter++;
      ClockCounter = 0;
      skippedMillis = 0;
    }
    else
    {
      skippedMillis += delta;
    }
    Serial.print(FlashCounter);
    Serial.print(": ");
    Serial.print(delta);
    Serial.print("ms ");
    Serial.println(skippedMillis);
    lastmillis = millis();
  }
  //if transmission for one character finished
  if (ClockCounter >= MaxValue && FlashCounter > 0)
  {
    //write flashcounter as character
    Serial.write(FlashCounter);
    Serial.println(FlashCounter);
    //reset flashcounter for next character
    FlashCounter = 0;
  }
  else
    delay(1);
}