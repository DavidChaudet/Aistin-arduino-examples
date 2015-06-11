#include <Wire.h>
#include <LIS3DSH.h>
#include <L3GD20H.h>
#include <LIS3MDL.h>

LIS3DSH accel;
L3GD20H gyro;
LIS3MDL magn;

void setup(){
  digitalWrite(4,HIGH);
  Wire.begin();
  Serial.begin(9600);
  while(!Serial);
  accel.init();
  gyro.init();
  magn.init();
  delay(100);
}
void loop(){
  acceleration();
  rotation();
  magnetic();
}
void acceleration(void)
{
  int x, y, z;
  while(true)
  {
    delay(100);
    accel.readXYZ(x, y, z);
    accel.mgScale(x, y, z);
    Serial.print("x: "); //print everything
    Serial.print(x);
    Serial.print(" mg \ty: ");
    Serial.print(y);
    Serial.print(" mg \tz: ");
    Serial.print(z);
    Serial.println(" mg");
    if(Serial.available())
    {
      Serial.read();
      break;
    }
  }
}
void rotation(void)
{
  int x, y, z;
  while(true)
  {
    delay(100);
    gyro.readXYZ(x, y, z);
    Serial.print("x: "); //print everything
    Serial.print(x);
    Serial.print("    \ty: ");
    Serial.print(y);
    Serial.print("    \tz: ");
    Serial.println(z);
    if(Serial.available())
    {
      Serial.read();
      break;
    }
  }
}
void magnetic(void)
{
  int x, y, z;
  while(true)
  {
    delay(100);
    magn.readXYZ(x, y, z);
    Serial.print("x: "); //print everything
    Serial.print(x);
    Serial.print("    \ty: ");
    Serial.print(y);
    Serial.print("    \tz: ");
    Serial.println(z);
    if(Serial.available())
    {
      Serial.read();
      break;
    }
  }
}
