#include <Wire.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define ADXL345_ADDRESS 0x53
#define led 2
//millis adxl
//-----------
unsigned long adxlmillis = 0;
int adxlDelay = 100;
//---------
//boton
//---------------------------------------------------------------------------------------
int cont = 0;
RTC_DATA_ATTR int bootNum = 0;
int pinButton = 15;

bool statPrevBut = LOW;
unsigned long millisTime = 0;

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
//-----------------------------------------------------------------------------------------
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
  Wire.write(0x07);
  Wire.endTransmission();
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
  delay(10);
  acel.adxlBegin();
  bootNum++;
  Serial.println("numero de boot: " + String(bootNum));

  pinMode(pinButton , INPUT);
  pinMode(led, OUTPUT);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, 1); //1 = High, 0 = Low

  if (!SD.begin())
  {
    for (int i = 0; i <= 3; i++) {
      digitalWrite(led, HIGH);
      delay(250);
      digitalWrite(led, LOW);
      delay(250);
    }
    esp_deep_sleep_start();
  }
  writeFile(SD, "/data.txt", "conteo\n");
  digitalWrite(led, HIGH);
}

void loop() {
  if ((millis() - adxlmillis) > adxlDelay) {
    adxlmillis = millis();
    acel.askAcel();
    int pastX = (int)acel.getX();
    int pastY = (int)acel.getY();
    int pastZ = (int)acel.getZ();
    //Serial.println(String(pastX) + " " + String(pastY) + " " + String(pastZ));
    char str[16]="";
    snprintf(str, sizeof(str), "%d %d %d\n",pastX,pastY,pastZ);
    Serial.print(str);
    appendFile(SD,"/data.txt",str);
    
  }
  if (botonFun(pinButton , &statPrevBut, &millisTime)) {
    //Serial.println(cont);
    //cont++;
    Serial.println("A dormir.............");
    digitalWrite(led,LOW);
    delay(700);
    digitalWrite(led,HIGH);
    delay(1300);
    esp_deep_sleep_start();
  }
}
