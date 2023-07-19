#include <Wire.h>

#define ADXL345_ADDRESS 0x53
#define BLINK_LED 4
volatile bool data_ready = false;
//unsigned long timer = 0;

void IRAM_ATTR isr() {
  data_ready = true;
}

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Inicializar comunicación I2C en pines 21 y 22
  delay(100);

  // Configurar el ADXL345
    Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2D);
  Wire.write(0x08);
  Wire.endTransmission();
  
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x31); // Registro DATA_FORMAT
  Wire.write(0x0B); // Establecer rango de +/-2g
  Wire.endTransmission();

  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2C); // Registro BW_RATE
  Wire.write(0x0A); // Establecer tasa de muestreo en 25Hz
  Wire.endTransmission();

  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2E); // Registro INT_ENABLE
  Wire.write(0x80); // Habilitar interrupción DATA_READY
  Wire.endTransmission();

  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2F); // Registro INT_MAP
  Wire.write(0x7F); // Mapear la interrupción DATA_READY al pin INT1
  Wire.endTransmission();

  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x24); // Registro THRESH_ACT
  Wire.write(10); // Establecer umbral de activación en 10 LSB
  Wire.endTransmission();

  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x27); // Registro ACT_INACT_CTL
  Wire.write(0x08); // Establecer tiempo de duración de interrupción en 625 us
  Wire.endTransmission();

  pinMode(2, INPUT_PULLUP); // Configurar el pin INT1 como entrada con pullup
  pinMode(BLINK_LED,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING); // Configurar interrupción en flanco de subida
}
bool led=true;
bool blink_p(bool flag){
  flag = !flag;
  if (flag)
  {
    digitalWrite(BLINK_LED,HIGH);
  }
  else
  {
    digitalWrite(BLINK_LED,LOW);
  }
  return flag;
}
void loop() {
  if (data_ready) {
    led=blink_p(led);
    data_ready = false;
    // Leer los valores de aceleración en los 3 ejes
    int16_t x, y, z;
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(0x32); // Registro X0
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345_ADDRESS, 6, true);
    x = (Wire.read() | (Wire.read() << 8));
    y = (Wire.read() | (Wire.read() << 8));
    z = (Wire.read() | (Wire.read() << 8));
    // Imprimir los valores de aceleración
    Serial.print("X = ");
    Serial.print(x);
    Serial.print(" Y = ");
    Serial.print(y);
    Serial.print(" Z = ");
    Serial.println(z);
  }
}
