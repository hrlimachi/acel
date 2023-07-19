void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}
int i = 0;
void loop() {
  bool flag = false;
  // put your main code here, to run repeatedly:
  Serial.println(i);
  i++;
  delay(1000);
}
