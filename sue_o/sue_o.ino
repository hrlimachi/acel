unsigned long tx = 0, ty = 0;
unsigned long tiempo1, tiempo2;
#define LEDP 2
#define TIME_SLEEP 30;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  tiempo1 = millis();
  tiempo2 = millis();
  if (tiempo1 - tx >= 40) {
    tx = tiempo1;
    
  }
  if (tiempo2 - ty >= 2000) {
    ty = tiempo2;
  }
  esp_sleep_enable_timer_wakeup(TIME_SLEEP*1000);
  esp_deep_sleep_start();
}
