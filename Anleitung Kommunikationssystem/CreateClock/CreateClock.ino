//init variables
int ClockCounter = 0;
int MaxValue = 50;
int state = 0;

void setup() {
  //init serial interface from arduino
  Serial.begin(9600);
}

void loop() {
  //if counter >= 50
  if(ClockCounter >= MaxValue){
    //invert state
    state = !state;
    //reset counter
    ClockCounter = 0;
  }else{
    //increment counter
    ClockCounter++;
    //print state to serial interface
    Serial.println(state);
  }
}
