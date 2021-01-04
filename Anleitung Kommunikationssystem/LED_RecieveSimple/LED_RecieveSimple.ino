//init variables
int LDR = 2;
int ClockCounter = 0;
int FlashCounter = 0;
int MaxValue = 30;
int HighFlanke = 0;
int Flash;

void setup() {
  //init serial monitor
  Serial.begin(9600);
  //init pinmode
  pinMode(LDR, INPUT);
}

void loop() {
  ClockCounter++;
  //red LDR value
  Flash = digitalRead(LDR);
  if(Flash){
    HighFlanke = 1;
  }
  //if LDR value changes from HIGH to LOW
  if(!Flash && HighFlanke){
    HighFlanke = 0;
    //increment flashcounter
    FlashCounter++;
    ClockCounter = 0;
  }
  //if transmission for one character finished
  if(ClockCounter >= MaxValue) && FlashCounter > 0){
    //write flashcounter as character
    Serial.write(FlashCounter);
    //reset flashcounter for next character
    FashCounter = 0;
  }else delay(1);
}
