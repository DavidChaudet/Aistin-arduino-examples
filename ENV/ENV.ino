/* 
 * ENV.ino
 * example code for ENV board
 *
 * Prints UV, pressure, humidity, temperature,
 * light & proximity sensor values into serial
 * Change sensor currently in use by sending 
 * anything to serial
 * By J. Piippo 2015-07-07
*/ 

#include <Wire.h>
#include <UVIS25.h>
#include <LPS25H.h>
#include <HTS221.h>
#include <TCS37725FN.h>

UVIS25 UVS; //Ultraviolet sensor
LPS25H baro; //Barometer
HTS221 HTS; //Humidity & temperature sensor
TCS37725FN LPS; //Light & proximity sensor

void setup(){
  digitalWrite(4, HIGH); //Sensor enable
  Wire.begin();
  Serial.begin(9600);
  UVS.init();
  baro.init();
  HTS.init();
  LPS.init();
  delay(100);
}
void loop(){
  while(!Serial);
  Serial.println("Serial open");
  lightAndProximity();
  uv();
  pressure();
  humidityAndTemperature();
}
void uv(void)
{
  int uv;
  while(true)
  {
    delay(100);
    uv = UVS.readUV();
    Serial.print("UV: "); //print everything
    Serial.println(uv);
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

void lightAndProximity(void)
{
  uint16_t ambient, red, green, blue, proximity;
  while(true)
  {
    delay(100);
    ambient = LPS.readClear();
    LPS.readColors(red, green, blue);
    proximity= LPS.readProximity();
    String printString = "clear: " + String(ambient) + "\r\n" +
                         "colours: " + String(red) + " " + String(green) + " " + String(blue) + "\r\n"
                         "proximity: " + String(proximity) + "\r\n";
    Serial.print(printString);
    if(Serial.available())
    {
      Serial.read();
      break;
    }
  }
}
