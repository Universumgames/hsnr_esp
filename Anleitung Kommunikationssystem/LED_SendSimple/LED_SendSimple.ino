//init variables
int LED = 2;
int incomingByte, ByteToSend;
int SerialCounter = -1;
//serial input buffer used as a stack
int SerialBuffer[10];
int MaxValue = 4;
int ClockCounter = 0;
boolean state = 0;
int BitsToSend = -1;


void setup() {
  //init serial interface
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  //read serial input if available
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    if (incomingByte >= 32){
      //increment serial counter
      SerialCounter++;
      //store recieved byte from serial into stack buffer
      SerialBuffer[SerialCounter] = incomingByte;
    }
  }
  ClockCounter++;
  if(ClockCounter >= MaxValue){
    ClockCounter = 0;
    state = !state;
    //if serial buffer is not empty
    if(SerialCounter > -1){
      //if current byte to send is not set
      if(BitsToSend <= -1){
        //set byte to send
        BitsToSend = SerialBuffer[SerialCounter];
        Serial.print("Sending byte: ");
        Serial.println(BitsToSend);
      }else{
        digitalWrite(LED, state);
        delay(70);
        //if led is on
        if(state){
          //decrease bit to send
          BitsToSend--;
          //if byte is sent, finish transmission
          if(BitsToSend <= 0){
            BitsToSend = -1;
            SerialCounter--;
            delay(4*70);
            digitalWrite(LED, LOW);
            delay(5000);
          }
        }
      }
    }
  }
  delay(70);
}
