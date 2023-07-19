#include <MPU6050.h>

MPU6050 mpu;
int16_t ax,ay,az,gx,gy,gz;
const int numReadings = 40;
int readings[numReadings];
int index = 0;
int total = 0;
float averageX =0;

const int numReadings2 = 40;
int readings2[numReadings2];
int index2 = 0;
int total2 = 0;
float averageY =0;

const int numReadings3 = 40;
int readings3[numReadings3];
int index3 = 0;
int total3 = 0;
float averageZ =0;

void setup()
{
  Serial.begin(9600);
  for(int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;
  for(int thisReading2 = 0; thisReading2 < numReadings2; thisReading2++)
    readings2[thisReading2] = 0;
  for(int thisReading3 = 0; thisReading3 < numReadings3; thisReading3++)
    readings3[thisReading3] = 0;
  mpu.initialize();
  if(mpu.testConnection()){
    while(1)
      Serial.println("error de conexion");
  }
}
void loop()
{
  mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
  ax=-(ax/1000);
  ay=(ay/1000);
  az=(az/1000)-16;

  total = total - readings[index];
  readings[index]=ax;
  total = total + readings[index];
  index = index + 1;

  if(index >= numReadings)
    index = 0;
  averageX = total / numReadings;
  
  total2 = total2 - readings2[index2];
  readings2[index2]=ay;
  total2 = total2 + readings2[index2];
  index2 = index2 + 1;

  if(index2 >= numReadings2)
    index2 = 0;
  averageY = total2 / numReadings2;

  total3 = total3 - readings3[index3];
  readings3[index3]=az;
  total3 = total3 + readings3[index3];
  index3 = index3 + 1;

  if(index3 >= numReadings3)
    index3 = 0;
  averageZ = total3 / numReadings3;
//  Serial.print(ax);
//  Serial.print(",");
//  Serial.print(ay);
//  Serial.print(",");
  Serial.print(averageX);
  Serial.print(",");
  Serial.print(averageY);
  Serial.print(",");
  Serial.println(averageZ);
}
