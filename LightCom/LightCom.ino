//declare variables
//declare pins
int sender_clock = 5;
int sender_data = 6;
int reciever_clock = 2;
int reciever_clock_2 = 3;
int reciever_data = 4;

int incomingByte = 0;
long long last_millis = 0;
byte temp = 0;
int recieve_index = 7;
byte b = 0;
bool lastClockState = 0;

//declare timing
int ledDuration = 300;
int minSignalDur = 100;
int clDelay = 50;

void setup()
{
  //initialize Serial Monitor
  Serial.begin(9600);
  //set pin modes
  pinMode(sender_clock, OUTPUT);
  pinMode(sender_data, OUTPUT);
  pinMode(reciever_clock, INPUT);
  pinMode(reciever_clock_2, INPUT);
  pinMode(reciever_data, INPUT);
}

void loop()
{
  //check if serial queue contains items
  if (Serial.available() > 0)
  {
    //read incoming byte (characters)
    incomingByte = Serial.read();
    
    Serial.write(incomingByte);
    Serial.print(": ");
    Serial.print(incomingByte);
    Serial.print(" ");
    //send each bit seperately to serial monitor for debugging and to other arduino
    for (int i = 7; i >= 0; i--)
    {
      sendBit(bitRead(incomingByte, i));
    }
    Serial.println();
  }

  bool state = !digitalRead(reciever_clock);
  if (state != lastClockState)
  {
     lastClockState = state;
     if (state == HIGH)
        clock_interrupt_start();
     else
        clock_interrupt_end();
  }
}

//read incoming bits
void clock_interrupt_start()
{
  bool dataval = !digitalRead(reciever_data);
  bitWrite(temp, recieve_index, dataval);
}

//verify incoming bit
void clock_interrupt_end()
{
  //calculate delta since clock fell, to check for hazards
  unsigned long delta = millis() - last_millis;
  //if delta > 100ms, it's nit a hazard or glitch from the photoresistor
  if (delta >= minSignalDur)
  {
    //write temporary byte to "longterm" byte
    b = temp;
    Serial.print(bitRead(b, recieve_index));
    //reduce recieve index to move to next bit
    recieve_index--;
    //if recieve_index < 0 we have successfully recieved a byte and print that to the serial monitor
    if (recieve_index < 0)
    {
      Serial.write(b);
      //reset recieving variables to default state
      recieve_index = 7;
      b = 0x0;
    }
    //reset for delta caluclation
    last_millis = millis();
  }
  else
  {
    //if a glitch was detected, delete temporarily recieved bit
    temp = b;
  }
}

//send single bit
void sendBit(bool bitt)
{
  Serial.print(bitt);
  //change data pin
  digitalWrite(sender_data, bitt);
  delay(clDelay);
  //change clock to HIGH
  digitalWrite(sender_clock, HIGH);
  //wait to be able to differentiate between valid bit and a hazard
  delay(ledDuration);
  //change both pins to default state
  digitalWrite(sender_clock, LOW);
  delay(clDelay);
  digitalWrite(sender_data, LOW);
  delay(ledDuration);
}
