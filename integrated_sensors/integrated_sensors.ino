#include <Wire.h>
#include <LIS2DH12.h>
#include <LPS25H.h>
#include <HTS221.h>

LIS2DH12 accel;
LPS25H baro;
HTS221 HTS;

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
void pressure(void)
{
  int32_t press;
  while(true)
  {
    delay(100);
    press = baro.readPressure();
    Serial.print("Pressure: "); //print everything
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
    Serial.print("Humidity: "); //print everything
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
