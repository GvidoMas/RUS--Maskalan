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
    delay(500);
    digitalWrite(ledDistance, LOW);
  }

  delay(10);
}

/**
 * @brief Funkcija koja se poziva aktivacijom timer-a.
 *
 * Mjenja flag timerFlag u TRUE zbog čega će se u loop() funkciji pozvati funkcija handleTimer()
 */
void onTimer() {
  timerFlag = true;
}

/**
 * @brief Funkcija koja se poziva ako je timerFlak TRUE.
 *
 * Provjerava da li je neki prekid u tijeku i ako nije pali ledTimer lampicu na 500ms te resetira timerFlag u FALSE.
 */
void handleTimer() {
  isInProgress = true;

  digitalWrite(ledTimer, HIGH);
  delay(500);
  digitalWrite(ledTimer, LOW);
  timerFlag = false;
  
  isInProgress = false;
}

/**
 * @brief Funkcija koja se poziva prekidom izazvanim pritiskom gumba 1.
 *
 * Poziva funkciju handleBtnPress() i prosljeđuje indeks lampice 1.
 */
void INT1() {
  if(!isInProgress){
    handleBtnPress(0);
  }
}

/**
 * @brief Funkcija koja se poziva prekidom izazvanim pritiskom gumba 2.
 *
 * Poziva funkciju handleBtnPress() i prosljeđuje indeks lampice 2.
 */
void INT2() {
  if(!isInProgress){
    handleBtnPress(1);
  }
}

/**
 * @brief Funkcija koja se poziva prekidom izazvanim pritiskom gumba 3.
 *
 * Poziva funkciju handleBtnPress() i prosljeđuje indeks lampice 3.
 */
void INT3() {
  if(!isInProgress){
    handleBtnPress(2);
  }
}

/**
 * @brief Funkcija koja se poziva iz prekida povezanih sa gumbima.
 *
 * Radi debounce gumba te postavlja btnFlag pritisnutog gumba u TRUE kako bi se lapica tog gumba upalila.
 *
 * @param [in] int btnNumber - indeks gumba za koji treba upaliti lampicu
 */
void handleBtnPress(int btnNumber) {
  if (millis() - lastInterruptTime > debounceDelay) {
    btnFlags[btnNumber] = true;
    lastInterruptTime = millis();
  }
}

/**
 * @brief Funkcija koja se poziva u loop() funkciji te pali lampice sa postavljenim flagom.
 *
 * Prolazi kroz btnFlags niz i mjenja stanje lapice ako je flag postavljen u TRUE
 */
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

/**
 * @brief Funkcija koja očitava udaljenost prepreke.
 *
 * Poziva se u loop() funkciji te očitava udaljenost do prepreke.
 *
 * @return float vrijednost udaljenosti do prepreke
 */
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
