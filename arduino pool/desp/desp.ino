#include <Wire.h>
#include <Kalman.h>
#include <MPU6050.h>

// Inicialización del sensor MPU6050
MPU6050 mpu;
// Variables para el cálculo del desplazamiento
double posX = 0;
double posY = 0;

// Variables para el cálculo de la velocidad
double velX = 0;
double velY = 0;
double prevX = 0;
double prevY = 0;

// Variables para el cálculo de la aceleración
int ax = 0;
int ay = 0;
int az = 0;

// Tiempo de muestreo en milisegundos
const int dt = 10;
class Kalman {
  public:
    Kalman();
    double getAngle(double newAngle, double newRate);
    void setAngle(double angle);

  private:
    double Q_angle = 0.001;
    double Q_bias = 0.003;
    double R_measure = 0.03;

    double angle = 0;
    double bias = 0;
    double P[2][2] = {{0, 0}, {0, 0}};
    double K[2];

    void update();
};

Kalman::Kalman() {}

double Kalman::getAngle(double newAngle, double newRate) {
  angle += dt*(newRate - bias);
  P[0][0] += dt*(dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt*P[1][1];
  P[1][0] -= dt*P[1][1];
  P[1][1] += Q_bias*dt;
  double S = P[0][0] + R_measure;
  K[0] = P[0][0]/S;
  K[1] = P[1][0]/S;
  double y = newAngle - angle;
  angle += K[0]*y;
  bias += K[1]*y;
  P[0][0] -= K[0]*P[0][0];
  P[0][1] -= K[0]*P[0][1];
  P[1][0] -= K[1]*P[0][0];
  P[1][1] -= K[1]*P[0][1];
  return angle;
}

void Kalman::setAngle(double angle) {
  this->angle = angle;
}

void Kalman::update() {
  P[0][0] += dt*(dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt*P[1][1];
  P[1][0] -= dt*P[1][1];
  P[1][1] += Q_bias*dt;
}
// Inicialización del filtro de Kalman
Kalman kalmanX;
Kalman kalmanY;


void setup() {
  // Inicialización del puerto serial
  Serial.begin(9600);

  // Inicialización del sensor MPU6050
  Wire.begin();
  mpu.initialize();

  // Configuración del filtro de Kalman
  kalmanX.setAngle(0);
  kalmanY.setAngle(0);
}

void loop() {
  // Lectura de los valores del sensor MPU6050
  mpu.getAcceleration(&ax, &ay, &az);

  // Filtro de Kalman para la aceleración en el eje X
  double accXangle = kalmanX.getAngle(ax, dt);

  // Filtro de Kalman para la aceleración en el eje Y
  double accYangle = kalmanY.getAngle(ay, dt);

  // Cálculo del desplazamiento en el eje X
  posX = posX + velX*dt + 0.5*accXangle*dt*dt;

  // Cálculo del desplazamiento en el eje Y
  posY = posY + velY*dt + 0.5*accYangle*dt*dt;

  // Cálculo de la velocidad en el eje X
  velX = velX + (accXangle+prevX)*dt/2;

  // Cálculo de la velocidad en el eje Y
  velY = velY + (accYangle+prevY)*dt/2;

  // Actualización de las variables para el cálculo de la velocidad
  prevX = accXangle;
  prevY = accYangle;

  // Impresión de los valores en el monitor serial
  Serial.print("Desplazamiento en X: ");
  Serial.println(posX);
  Serial.print("Desplazamiento en Y: ");
  Serial.println(posY);

  // Espera de un tiempo de muestreo
  delay(dt);
}
