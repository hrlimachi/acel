#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"

TaskHandle_t taskCore0;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void setup()
{
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  xTaskCreatePinnedToCore(
    readSensor,     //Nombre del loop creado
    "readSensor",   //Nombre
    10000,          //Tamaño de la pila
    NULL,           //Parametro casi siempre Nulo
    1,              //Prioridad de la tarea
    &taskCore0,     //Nombre de la tarea
    0);             //Nucleo donde se ejecuta

  Serial.begin(115200);
  if (!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  Serial.begin(115200);
  if (!SD.begin()) 
  {
    Serial.println("Card Mount Failed");
    return;
  }
  writeFile(SD, "/data.txt", "conteo");
  pinMode(2,OUTPUT);
}

void loop()
{
  float total;
  sensors_event_t event;
  accel.getEvent(&event);
  total = sqrt(event.acceleration.x * event.acceleration.x + event.acceleration.y * event.acceleration.y + event.acceleration.z * event.acceleration.z);

  Serial.println(String(event.acceleration.x) + " " + String(event.acceleration.y) + " " + String(event.acceleration.z) + " " + String(total));
  delay(20);
}
void readSensor(void *parameter)
{
  bool flag = true;
  while (true)
  {
    flag = !flag;
    if(flag==true)
    {
      digitalWrite(2,HIGH);
    }
    else
    {
      digitalWrite(2,LOW);
    }
    delay(100);
  }
  vTaskDelay(10);   //Evitar advertencia de watchdog
}
