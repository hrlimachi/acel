//#include <Wire.h>
//
//#define ADXL345_ADDRESS 0x53
//
//void setup() {
//  Serial.begin(9600);
//  Wire.begin();
//
//  // Activar el ADXL345
//  Wire.beginTransmission(ADXL345_ADDRESS);
//  Wire.write(0x2D);
//  Wire.write(0x08);
//  Wire.endTransmission();
//  
//  // Configurar el ADXL345
//  Wire.beginTransmission(ADXL345_ADDRESS);
//  Wire.write(0x31);
//  Wire.write(0x0B);
//  Wire.endTransmission();
//
//  // Establecer el rango de medición
//  //Wire.beginTransmission(ADXL345_ADDRESS);
//  //Wire.write(0x31);
//  //Wire.write(0x09);
//  //Wire.endTransmission();
//
//  // Establecer la tasa de muestreo
//  Wire.beginTransmission(ADXL345_ADDRESS);
//  Wire.write(0x2C);
//  Wire.write(0x08);
//  Wire.endTransmission();
//}
//
//void loop() {
//  // Leer los datos del ADXL345
//  Wire.beginTransmission(ADXL345_ADDRESS);
//  Wire.write(0x32);
//  Wire.endTransmission();
//  Wire.requestFrom(ADXL345_ADDRESS, 6);
//  
//  int x = (Wire.read() | (Wire.read() << 8));
//  int y = (Wire.read() | (Wire.read() << 8));
//  int z = (Wire.read() | (Wire.read() << 8));
//
//  // Imprimir los datos en el monitor serie
//  Serial.print("X=");
//  Serial.print(x);
//  Serial.print(" Y=");
//  Serial.print(y);
//  Serial.print(" Z=");
//  Serial.println(z);
//
//  delay(40);
//}
#include <Wire.h>

#define ADXL345_ADDRESS (0x53) // Dirección del sensor ADXL345 en I2C bus
#define ADXL345_TO_READ (6) // Número de bytes a leer en una sola lectura

int16_t accel_x, accel_y, accel_z; // Variables para almacenar los valores de aceleración
bool x_sign, y_sign, z_sign; // Variables para almacenar el signo de cada eje

void setup() {
  Wire.begin(); // Iniciar el bus I2C
  Serial.begin(9600); // Iniciar la comunicación serial
  // Configurar el sensor ADXL345 en modo de medición continua
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x31); // Seleccionar el registro POWER_CTL
  Wire.write(0x0B); // Activar la medición continua
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(ADXL345_ADDRESS); // Iniciar una transmisión I2C al sensor
  Wire.write(0x32); // Seleccionar el registro DATAX0 para iniciar la lectura de los datos de aceleración
  Wire.endTransmission(false); // Finalizar la transmisión sin liberar el bus I2C

  // Leer los datos de aceleración y almacenarlos en las variables correspondientes
  Wire.requestFrom(ADXL345_ADDRESS, ADXL345_TO_READ, true);
  accel_x = Wire.read() | (Wire.read() << 8);
  accel_y = Wire.read() | (Wire.read() << 8);
  accel_z = Wire.read() | (Wire.read() << 8);

  // Obtener el signo de cada eje
  x_sign = (accel_x < 0);
  y_sign = (accel_y < 0);
  z_sign = (accel_z < 0);

  // Imprimir los valores de aceleración y los signos en la consola serial
  Serial.print("X: ");
  Serial.print(abs(accel_x));
  if (x_sign) {
    Serial.print("-");
  } else {
    Serial.print("+");
  }
  Serial.print("\tY: ");
  Serial.print(abs(accel_y));
  if (y_sign) {
    Serial.print("-");
  } else {
    Serial.print("+");
  }
  Serial.print("\tZ: ");
  Serial.print(abs(accel_z));
  if (z_sign) {
    Serial.print("-");
  } else {
    Serial.print("+");
  }
  Serial.println();

  delay(40); // Esperar 25 ms para tomar la siguiente lectura de aceleración
}
