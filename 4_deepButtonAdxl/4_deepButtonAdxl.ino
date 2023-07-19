//#define BUTTON_PIN_BITMASK 0x1000008000 //2^36+2^15 en hexa
#define led 2
int pin = 15;
bool statPrevBut = LOW;
unsigned long millisTime = 0;


int cont=0;
RTC_DATA_ATTR int bootNum = 0;

void setup() {
  Serial.begin(115200);
  delay(10);

  //incrementa cada vez que se despierta
  bootNum++;
  Serial.println("numero de boot: " + String(bootNum));

  //imprime razon pro la cual se despertó...
  pinMode(pin, INPUT);
  pinMode(led,OUTPUT);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, 1); //1 = High, 0 = Low

  //EXT1 ESP_EXT1_WAKEUP_ANY_HIGH or EXT1 ESP_EXT1_WAKEUP_ALL_LOW
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);

  Serial.println("Despierto........");
  
 // delay(200);
  digitalWrite(led,HIGH);
}

void loop() {
  
  if(botonFun(pin, &statPrevBut, &millisTime)){
    //Serial.println(cont);
    //cont++;
    Serial.println("A dormir.............");
    delay(200);
    esp_deep_sleep_start();
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
