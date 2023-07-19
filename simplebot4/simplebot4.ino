#define led 2
int pin = 4;
bool statPrevBut = LOW;
unsigned long millisTime = 0;
int cont = 0;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (botonFun(pin, &statPrevBut, &millisTime) == true) {
    Serial.println(cont);
    cont++;
  }
}
bool botonFun(int pin, bool* statePreviousButton, unsigned long* lastTime ) {
  bool stateCurrentButton = digitalRead(pin);
  const int delayMillis = 200;
  bool flag = false;
  if (*statePreviousButton != stateCurrentButton) {
    if (HIGH == stateCurrentButton) {
      if ((millis() - *lastTime) > delayMillis) {
        //inicio
        flag = true;
        //final
        *statePreviousButton = stateCurrentButton;
        *lastTime = millis();
      }
    }
    else {
      *statePreviousButton = LOW;
    }
  }
  return flag;
}
