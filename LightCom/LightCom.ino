//declare variables
int sender_clock = 6;
int sender_data = 7;
int reciever_clock = 4;
int reciever_data = 3;
int incomingByte = 0;
int reciever_clock_2 = 2;
long long last_millis = 0;
byte temp;
int recieve_index = 7;
byte b;

void setup()
{
  //attach Interrupts to not having to worry about reading from one pin
  attachInterrupt(digitalPinToInterrupt(reciever_clock), clock_interrupt_start, FALLING);
  attachInterrupt(digitalPinToInterrupt(reciever_clock), clock_interrupt_end, RISING);
  //initialize Serial Monitor
  Serial.begin(9600);
  //set pin modes
  pinMode(sender_clock, OUTPUT);
  pinMode(sender_data, OUTPUT);
  pinMode(reciever_clock, INPUT);
  pinMode(reciever_data, INPUT);
  pinMode(reciever_clock_2, INPUT);
}

void loop()
{
  //check if serial queue contains items
  if (Serial.available() > 0)
  {
    //read incoming byte (charactere)
    incomingByte = Serial.read();
    //send each bit seperately to serial monitor for debugging and to other arduino
    for (int i = 7; i >= 0; i--)
    {
      Serial.print(bitRead(incomingByte, i));
      sendBit(bitRead(incomingByte, i));
    }
    Serial.println();
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
  if (delta > 100)
  {
    //write temporary byte to "longterm" byte
    b = temp;
    //reduce recieve index to move to next bit
    recieve_index--;
    //if recieve_index < 0 we have successfully recieved a byte and print that to the serial monitor
    if (recieve_index < 0)
    {
      Serial.print(b);
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
  //change data pin
  digitalWrite(sender_data, bitt);
  delayMicroseconds(10);
  //change clock to HIGH
  digitalWrite(sender_clock, HIGH);
  //wait to be able to differentiate between valid bit and a hazard
  delayMicroseconds(500);
  //change both pins to default state
  digitalWrite(sender_clock, LOW);
  digitalWrite(sender_data, LOW);
  delayMicroseconds(5);
}