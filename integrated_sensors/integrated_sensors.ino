/* 
 * integrated_sensors.ino
 * example code for Aistin CPU integrated sensors
 *
 * Prints acceleration, pressure, humidity, 
 * temperature sensor values into serial
 * Change sensor currently in use by sending 
 * anything to serial
 * By J. Piippo 2015-07-07
*/ 

#include <Wire.h>
#include <LIS2DH12.h>
#include <LPS25H.h>
#include <HTS221.h>

LIS2DH12 accel; //Accelerometer
LPS25H baro; //Barometer
HTS221 HTS; //Humidity & temperature sensor

void setup(){
  digitalWrite(4,HIGH);
  Wire.begin();
  Serial.begin(9600);
  accel.init();
  baro.init();
  HTS.init();
  delay(100);
}
void loop(){
  while(!Serial);
  Serial.println("Serial open");
  acceleration();
  pressure();
  humidityAndTemperature();
}
void acceleration(void)
{
  accel.init();
  int x, y, z;
  while(true)
  {
    delay(100);
    accel.readXYZ(x, y, z);
    accel.mgScale(x, y, z);
    Serial.print("Acceleration x: "); //print acceleration
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
void pressure(void)
{
  int32_t press;
  while(true)
  {
    delay(100);
    press = baro.readPressure();
    Serial.print("Pressure: "); //print pressure
    Serial.println(press);
    if(Serial.available())
    {
      Serial.read();
      break;
    }
  }
}
void humidityAndTemperature(void)
{
  int16_t humi, temp;
  while(true)
  {
    delay(100);
    humi = HTS.readHumidity();
    temp = HTS.readTemperature();
    Serial.print("Humidity: "); //print humidity & temperature
    Serial.println(humi);
    Serial.print("Temperature: ");
    Serial.println(temp);
    if(Serial.available())
    {
      Serial.read();
      break;
    }
  }
}
