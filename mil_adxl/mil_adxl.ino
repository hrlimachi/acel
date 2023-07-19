//#include "esp_bt.h"
//#include "esp_gap_ble_api.h"
//#include "esp_gatts_api.h"
#include <Wire.h>

unsigned long tx = 0, ty = 0;
unsigned long tiempo1, tiempo2;

bool flag_int = false;
bool flag = false;

//#define LEDP 2
#define TIME_SLEEP 10

#define ADXL345_ADDRESS 0x53

#define LED 2

class Adxl345 {
  public:
    Adxl345() {
    }
    void adxlBegin();
    void askAcel();
    int16_t getX();
    int16_t getY();
    int16_t getZ();
  private:
    int16_t x;
    int16_t y;
    int16_t z;
};

void Adxl345::adxlBegin() {
  Wire.begin();
  delay(100);
  // Activar el ADXL345
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2D);
  Wire.write(0x08);
  Wire.endTransmission();

  // Configurar el ADXL345
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x31);
  Wire.write(0x0B);
  Wire.endTransmission();

  // Establecer la tasa de muestreo
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2C);
  Wire.write(0x08);
  Wire.endTransmission();

  //  Wire.beginTransmission(ADXL345_ADDRESS);
  //  Wire.write(0x2E);
  //  Wire.write(0x00);
  //  Wire.endTransmission();
  //
  //  Wire.beginTransmission(ADXL345_ADDRESS);
  //  Wire.write(0x2F);
  //  Wire.write(0x80);
  //  Wire.endTransmission();
  //
  //  Wire.beginTransmission(ADXL345_ADDRESS);
  //  Wire.write(0x2E);
  //  Wire.write(0x80);
  //  Wire.endTransmission();
}
void Adxl345::askAcel() {
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x32);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345_ADDRESS, 6);
  x = (Wire.read() | (Wire.read() << 8));
  y = (Wire.read() | (Wire.read() << 8));
  z = (Wire.read() | (Wire.read() << 8));
}
int16_t Adxl345::getX() {
  return x;
}
int16_t Adxl345::getY() {
  return y;
}
int16_t Adxl345::getZ() {
  return z;
}

Adxl345 acel;

void setup() {
  Serial.begin(115200);
  acel.adxlBegin();
  pinMode(LED, OUTPUT);
}
int counter = 0;
void loop() {

  tiempo1 = millis();
  tiempo2 = millis();
  if (tiempo1 - tx >= 40) {
    tx = tiempo1;
    acel.askAcel();
    Serial.println(String(acel.getX()) + " " + String(acel.getY()) + " " + String(acel.getZ()));
    flag = !flag;
  }
  if (flag == true) {
    digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(LED, LOW);
  }
  if (tiempo2 - ty >= 80) {
    ty = tiempo2;
  }
  esp_sleep_enable_timer_wakeup(TIME_SLEEP * 1000);
  esp_deep_sleep_start();
}
