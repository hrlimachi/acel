TaskHandle_t taskCore0;
bool flag= true;
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
  pinMode(2,OUTPUT);
}

void loop() 
{
  //Serial.println("************************");
  //Serial.println("Nucleo [loop] = " + String(xPortGetCoreID()));
  //Serial.println("************************");
  //delay(733);
  while(flag==true)
  {
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    delay(500);
  }
  while(flag==false)
  {
    digitalWrite(2,HIGH);
    delay(250);
    digitalWrite(2,LOW);
    delay(250);
  }
}
void readSensor(void *parameter)
{
  while(true)
  {
    //Serial.println("************************");
    //Serial.println("Nucleo [readSensor] = " + String(xPortGetCoreID()));
    //Serial.println("************************");
    flag=!flag;
    delay(2000);
  }
  vTaskDelay(10);   //Evitar advertencia de watchdog
}
