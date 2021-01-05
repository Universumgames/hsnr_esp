int Clock = 2;
int Data = 5;
int SerialBuffer[100];
int SerialCounter = -1;
int HalfPeriod = 100;
int incomingByte, ByteToSend, Bit2Send;

void setup() {
  Serial.begin(9600);
  pinMode(Clock, OUTPUT);
  pinMode(Data, OUTPUT);
  digitalWrite(Clock, LOW);
  digitalWrite(Data, LOW);
}

void loop() {
  //read serial input if available
  if(Serial.available() > 0){
    //read serial input if available
    incomingByte = Serial.read();
    if (incomingByte >= 32){
      //increment serial counter
      SerialCounter++;
      //store recieved byte from serial into stack buffer
      SerialBuffer[SerialCounter] = incomingByte;
    }
    ByteToSend = SerialBuffer[SerialCounter];
    //send byte, iterate through every bit
    for(int i = 7; i >= 0; i--){
      digitalWrite(Data, LOW);
      //get bit to send
      Bit2Send = bitRead(ByteToSend,i));
      //set clock
      digitalWrite(Clock, HIGH);
      delay(1);
      //set/send bit
      digitalWrite(Data, Bit2Send);
      Serial.println(Bit2Send);
      delay(HalfPeriod);
      //reset clock and data
      digitalWrite(Clock, LOW);
      delay(1);
      digitalWrite(Data, LOW);
      delay(HalfPeriod);
    }
    SerialCounter--;
    Serial.println();
  }
  delay(100);
}
