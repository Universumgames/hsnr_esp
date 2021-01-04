//init variables
int Bit;
int Clock = 2;
int Data = 5;
int SerialBuffer[100];
int BitCounter = 0;
unsigned long TimeOut = 10000;
unsigned long ClockCounter = 0;
int BitArray[8];
byte recievedChar;

void setup() {
  //init serial interface
  Serial.begin(9600);
  //init input pins
  pinMode(Clock, INPUT);
  pinMode(Data, INPUT);
}

void loop() {
  //wait for clock pin change
  while(digitalRead(Clock)){
    delay(1);
    ClockCounter++;
    //implemented timeout to prevent hazards and glitches to take affect
    if(ClockCounter >= TimeOut){
      if(BitCounter > 0){
        BitCounter = 0;
      }
      ClockCounter = 0;
    }
  }
  delay(10);
  //write data pin value to array
  BitArray[7-BitCounter] = !digitalRead(Data);
  BitCounter++;
  //wait for clock signla to change to HIGH, to sync with sender
  while(!digitalRead(Clock));
  //if full byte recieved
  if(BitCounter >= 8){
    //iterate thorugh array
    for(int i = 0; i < 8; i++){
      //corrosponding to bitWrite
      RecievedChar |= BitArray[i] << i;
    }
    //reset and print recieved char
    BitCounter = 0;
    Serial.print(RecievedChar);
    RecievedChar = 0;
  }
  delay(5);
}
