#define btn1 16
#define btn2 2
#define btn3 4

#define trig 12
#define echo 14

#define ledTimer 19
#define ledBtn1 17
#define ledBtn2 5
#define ledBtn3 18
#define ledDistance 22

int ledState1 = 0;
int ledState2 = 0;
int ledState3 = 0;

bool timerFlag = false;
bool isInProgress = false;

int lastInterruptTime = 0;
int debounceDelay = 100;

bool btnFlags[3] = {false, false, false};   

hw_timer_t *timer = NULL;

void setup() {
  Serial.begin(115200);
  
  timer = timerBegin(1000000);

  pinMode(ledTimer, OUTPUT);
  pinMode(ledBtn1, OUTPUT);
  pinMode(ledBtn2, OUTPUT);
  pinMode(ledBtn3, OUTPUT);
  pinMode(ledDistance, OUTPUT);

  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  attachInterrupt(digitalPinToInterrupt(btn1), INT1, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2), INT2, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn3), INT3, FALLING);
  timerAttachInterrupt(timer, &onTimer);

  timerAlarm(timer, 1000000, true, 0);

}

void loop() {
  if (timerFlag) handleTimer();

  handleButtons();

  if (distance() != 0 && !isInProgress) {
    digitalWrite(ledDistance, HIGH);
    delay(200);
    digitalWrite(ledDistance, LOW);
    delay(100);
  }

  delay(10);
}

void onTimer() {
  timerFlag = true;
}

void handleTimer() {
  isInProgress = true;

  digitalWrite(ledTimer, HIGH);
  delay(500);
  digitalWrite(ledTimer, LOW);
  timerFlag = false;
  
  isInProgress = false;
}

void INT1() {
  if(!isInProgress){
    handleBtnPress(0);
  }
}

void INT2() {
  if(!isInProgress){
    handleBtnPress(1);
  }
}

void INT3() {
  if(!isInProgress){
    handleBtnPress(2);
  }
}

void handleBtnPress(int btnNumber) {
  if (millis() - lastInterruptTime > debounceDelay) {
    btnFlags[btnNumber] = true;
    lastInterruptTime = millis();
  }
}

void handleButtons() {
  isInProgress = true;

  if (btnFlags[0]) {
    if(ledState1 == 0) ledState1 = 1;
    else ledState1 = 0;
    digitalWrite(ledBtn1, ledState1);
    btnFlags[0] = false;
  } 
  else if (btnFlags[1]) {
    if(ledState2 == 0) ledState2 = 1;
    else ledState2 = 0;
    digitalWrite(ledBtn2, ledState2);
    btnFlags[1] = false;
  } 
  else if (btnFlags[2]) {
    if(ledState3 == 0) ledState3 = 1;
    else ledState3 = 0;
    digitalWrite(ledBtn3, ledState3);
    btnFlags[2] = false;
  }

  isInProgress = false;
}

float distance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);

  if(duration > 0 && duration < 30000) {
    return (duration / 2.0) * 0.0343;
  }

  return 0;
}