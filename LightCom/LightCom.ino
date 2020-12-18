int sender_clock = 6;
int sender_data = 7;
int reciever_clock= 4;
int reciever_data= 3;
int incomingByte = 0;
int reciever_clock_2 = 2;
long long last_millis = 0; 
byte temp;
int recieve_index = 7;
byte b;



void setup(){  

  attachInterrupt(digitalPinToInterrupt(reciever_clock),clock_interrupt_start,FALLING);
  attachInterrupt(digitalPinToInterrupt(reciever_clock),clock_interrupt_end,RISING);
  Serial.begin(9600);
  pinMode(sender_clock, OUTPUT);
  pinMode(sender_data, OUTPUT);
  pinMode(reciever_clock, INPUT);
  pinMode(reciever_data, INPUT);
  pinMode(reciever_clock_2, INPUT);
  
  
}

void loop()
{
if (Serial.available() > 0) {
    incomingByte = Serial.read();
 for (int i = 7; i >=0; i--){
     Serial.print(bitRead(incomingByte,i));
     sendBit(bitRead(incomingByte,i));
    }
  Serial.println();
  
  }

  
  
}

void clock_interrupt_start () {
  bool dataval = !digitalRead(reciever_data);
  bitWrite( temp,recieve_index, dataval);
}

void clock_interrupt_end (){
  unsigned long delta= millis() -last_millis;
  if(delta>100){
    b= temp;
    recieve_index--;
    if(recieve_index<0){
      Serial.print(b);
      recieve_index = 7;
      b = 0x0;
    }
    last_millis = millis (); 
  }
  else{
    temp =b;
  }
}

void sendBit (bool bitt){
  
  digitalWrite(sender_data, bitt);
  delayMicroseconds(10);
  digitalWrite(sender_clock, HIGH);
  delayMicroseconds(500);
  digitalWrite(sender_clock, LOW);
  digitalWrite(sender_data, LOW);
  delayMicroseconds(5);
  }
