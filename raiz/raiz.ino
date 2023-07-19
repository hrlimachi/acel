void setup() {
  Serial.begin(115200);
}

void loop() {
  int hola[]={1,4,9,16,25,36,49,64,81,100};
  for(int i=0; i<=9;i++){
    Serial.println(sqrt(pow(hola[i],2)));
    delay(500);
    
  }
}
