TaskHandle_t taskCore0;
void setup() 
{
  xTaskCreatePinnedToCore(
    readSensor,     //Nombre del loop creado
    "readSensor",   //Nombre
    10000,          //Tamaño de la pila
    NULL,           //Parametro casi siempre Nulo
    1,              //Prioridad de la tarea
    &taskCore0,     //Nombre de la tarea
    0);             //Nucleo donde se ejecuta
    
  Serial.begin(115200);
}

void loop() 
{
  Serial.println("************************");
  Serial.println("Nucleo [loop] = " + String(xPortGetCoreID()));
  Serial.println("************************");
  delay(733);
}
void readSensor(void *parameter)
{
  while(true)
  {
    Serial.println("************************");
    Serial.println("Nucleo [readSensor] = " + String(xPortGetCoreID()));
    Serial.println("************************");
    delay(250);
  }
  vTaskDelay(10);   //Evitar advertencia de watchdog
}
