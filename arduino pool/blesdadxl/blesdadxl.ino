#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <BluetoothSerial.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"

TaskHandle_t taskCore0;
SemaphoreHandle_t mutex = xSemaphoreCreateMutex();
BluetoothSerial SerialBT;

bool readySend = false;
float copyTotal = 0;
char flagbt = '0';

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void writeFile(fs::FS &fs, const char * path, const char * message) {

  File file = fs.open(path, FILE_WRITE);
  if (!file.print(message)) {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_APPEND);
  if (!file.print(message)) {
    Serial.println("Append failed");
  }
  file.close();
}

void setup()
{
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(115200);
  SerialBT.begin("ESP32_BLE"); // Nombre del dispositivo BLE
  while (flagbt == '0') {
    if (SerialBT.available()) {
      flagbt = SerialBT.read(); // Leer desde BLE y enviar por puerto serie
    }
  }
  xTaskCreatePinnedToCore(
    readSensor,     //Nombre del loop creado
    "readSensor",   //Nombre
    10000,          //Tamaño de la pila
    NULL,           //Parametro casi siempre Nulo
    1,              //Prioridad de la tarea
    &taskCore0,     //Nombre de la tarea
    0);             //Nucleo donde se ejecuta

  if (!accel.begin())
  {
    // Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
  accel.setDataRate(ADXL345_DATARATE_50_HZ);

  if (!SD.begin())
  {
    // Serial.println("Card Mount Failed");
    return;
  }
  writeFile(SD, "/data.txt", "conteo\n");
  pinMode(2, OUTPUT);
  pinMode(33, OUTPUT);
}

void loop()
{
  //if(flagbt=='1'){
  //   digitalWrite(2,HIGH);
  //}
  while (flagbt == '1') {
    if (SerialBT.available()) {
     // flagbt = SerialBT.read();
      if(SerialBT.read() != NULL)
      {
        flagbt=SerialBT.read();
      }
      if (flagbt == '1') {
        digitalWrite(2, HIGH);
      }
    }
    //   digitalWrite(2,LOW);
  }
  if (SerialBT.available()) {
    flagbt = SerialBT.read();
  }
  float total = 0;
  sensors_event_t event;
  accel.getEvent(&event);
  total = sqrt(event.acceleration.x * event.acceleration.x + event.acceleration.y * event.acceleration.y + event.acceleration.z * event.acceleration.z);
  SerialBT.write('1');
  if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
    // Acceso a la variable copyTotal
    copyTotal = total;
    readySend = true;
    xSemaphoreGive(mutex);
  }
  delay(30);

}
void readSensor(void *parameter)
{
  bool flag;
  while (true)
  {
    if (readySend == true && flagbt == '1') {
      if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        char str[40];
        snprintf(str, sizeof(str), "%.2f \n", copyTotal);
        appendFile(SD, "/data.txt", str);
        readySend = false;
        xSemaphoreGive(mutex);
      }
    }
    else
    {
      flag = !flag;
      if (flag == true)
      {
        digitalWrite(33, HIGH);
      }
      else
      {
        digitalWrite(33, LOW);
      }
      delay(1);
    }
  }
  vTaskDelay(10);   //Evitar advertencia de watchdog
}
