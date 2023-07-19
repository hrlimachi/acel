#define pin 4
#define led 2
#define delayMillis 50
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
  Serial.println("-----------------------");
  Serial.print("estado previo boton: ");
  Serial.println(statePreviousButton);
  Serial.print("estado actual boton: ");
  Serial.println(stateCurrentButton);
  delay(1000);
  if (statePreviousButton != stateCurrentButton) {
    if (HIGH == stateCurrentButton) {
      if ((millis() - lastTime) > delayMillis) {
        //inicio
        Serial.println(state);
        state++;
        //final
        statePreviousButton = stateCurrentButton;
        Serial.print("estado previo boton dentro del if: ");
        Serial.println(statePreviousButton);
        Serial.print("estado actual boton dentro del if: ");
        Serial.println(stateCurrentButton);
        delay(1000);
        lastTime = millis();
      }
    }
    else {
      statePreviousButton = LOW;
    }
  }
}
