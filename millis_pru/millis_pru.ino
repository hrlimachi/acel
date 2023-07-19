unsigned long tx=0, ty=0;
unsigned long tiempo1,tiempo2;
int estadoL1=LOW, estadoL2=LOW;

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
}

void loop() {
  digitalWrite(2,estadoL1);
  digitalWrite(4,estadoL2);
  tiempo1=millis();
  tiempo2=millis();

    if (tiempo1-tx>=500){
      tx=tiempo1;
      estadoL1=!estadoL1;
      }
    if (tiempo2-ty>=2000){
      ty=tiempo2;
      estadoL2=!estadoL2;
      }
}
