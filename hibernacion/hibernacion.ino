//#define BUTTON_PIN_BITMASK 0x1000008000 //2^36+2^15 en hexa

RTC_DATA_ATTR int bootNum = 0;

void setup(){
  Serial.begin(115200);
  delay(10);

  //incrementa cada vez que se despierta
  bootNum++;
  Serial.println("numero de boot: " + String(bootNum));

  //imprime razon pro la cual se despertó...
  pinMode(15,INPUT);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,1); //1 = High, 0 = Low

  //EXT1 ESP_EXT1_WAKEUP_ANY_HIGH or EXT1 ESP_EXT1_WAKEUP_ALL_LOW
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);

  Serial.println("A dormir........................");
  Serial.flush();
  esp_deep_sleep_start();

  Serial.println("esto no se imprime");
}

void loop(){
  
}
