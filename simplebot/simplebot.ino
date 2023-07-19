#define pin 4
#define led 2
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(pin,INPUT);

}

void loop() {
  bool comparar = HIGH;
  if (HIGH == digitalRead(pin)) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}
