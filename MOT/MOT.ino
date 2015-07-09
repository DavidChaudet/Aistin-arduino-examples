/* 
 * MOT.ino
 * example code for MOT board
 *
 * Prints Acceleration, gyroscope & 
 * magnetometer sensor values into serial
 * Change sensor currently in use by sending 
 * anything to serial
 * By J. Piippo iProtoXi 2015-07-07
*/ 

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
    Serial.print("acceleration \tx: "); //print everything
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
    Serial.print("gyroscope \tx: "); //print everything
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
    Serial.print("magnetometer \tx: "); //print everything
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
