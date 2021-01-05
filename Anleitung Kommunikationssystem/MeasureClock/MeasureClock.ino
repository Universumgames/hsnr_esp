//init variables
int ClockCounter = 0;
int MaxValue = 100;
int state = 0;
int Edge1 = 0;
unsigned long Start, Ende;

void setup() {
  //init serial interface
  Serial.begin(9600);
  //init measure variables
  Start = 0;
  Ende = 0;
}

void loop() {
  //if counter >= 100 & state = 1 & edge1 = 1
  if((ClockCounter >= MaxValue) && (state == 1) && (Edge1 == 1)){
    //reset egdge
    Edge1 = 0;
    //set end variable
    Ende = micros();
    //print delta micros to serial interface
    Serial.println(Ende-Start);
  }
  //if counter >= 100 & state = 1
  if((ClockCounter >= MaxValue) && (state == 1)){
    //set edge to 1
    Edge1 = 1;
    //set start variable
    Start = micros();
  }
  //if counter >= 100
  if(ClockCounter >= MaxValue){
    //invert state
    state = !state;
    //reset counter
    ClockCounter = 0;
  }
  //increment counter
  ClockCounter++;
}
