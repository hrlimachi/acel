#define pin 4
#define led 2
#define delayMillis 100
bool statePreviousButton = LOW;
bool stateCurrentButton;
unsigned long lastTime = 0;

int state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  stateCurrentButton = digitalRead(pin);
  if (statePreviousButton != stateCurrentButton) {
    if (HIGH == stateCurrentButton) {
      if ((millis() - lastTime) > delayMillis) {
        //inicio
        Serial.println(state);
        state++;
        //final
        statePreviousButton = stateCurrentButton;
        lastTime = millis();
      }
    }
    else {
      statePreviousButton = LOW;
    }
  }
}
