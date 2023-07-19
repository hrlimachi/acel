#include <Wire.h>

#define ADXL345_ADDRESS 0x53

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Activar el ADXL345       
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2D);
  Wire.write(0x08);
  Wire.endTransmission();
  
  // Configurar el ADXL345
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x31);
  Wire.write(0x2B);//B
  Wire.endTransmission();

  // Establecer el rango de medición
  //Wire.beginTransmission(ADXL345_ADDRESS);
  //Wire.write(0x31);
  //Wire.write(0x09);
  //Wire.endTransmission();

  // Establecer la tasa de muestreo
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2C);
  Wire.write(0x08);
  Wire.endTransmission();
}

void loop() {
  // Leer los datos del ADXL345
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x32);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345_ADDRESS, 6);
  
  int16_t x = (Wire.read() | (Wire.read() << 8));
  int16_t y = (Wire.read() | (Wire.read() << 8));
  int16_t z = (Wire.read() | (Wire.read() << 8));

  float gx= x*(9.81/236);
  float gy= y*(9.81/236);
  float gz= z*(9.81/236);
  // Imprimir los datos en el monitor serie
 // Serial.print("X=");
  Serial.println(String(x)+" "+String(y)+" "+String(z));
//  Serial.print(" Y=");
//  Serial.print(y);
//  Serial.print(" Z=");
//  Serial.println(z);

  delay(40);
}
