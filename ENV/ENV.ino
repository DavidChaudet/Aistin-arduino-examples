#include <Wire.h>
#include <UVIS25.h>
#include <LPS25H.h>
#include <HTS221.h>
#include <TCS37725FN.h>

UVIS25 UVS;
LPS25H baro;
HTS221 HTS;
TCS37725FN LPS;

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
                         /*
    Serial.print("clear: "); //print everything
    Serial.println(ambient);
    Serial.print("colours: ");
    Serial.print(red);Serial.print(' ');;Serial.print(green);;Serial.print(' ');Serial.println(blue);
    Serial.print("proximity: ");
    Serial.println(proximity);
    */
    if(Serial.available())
    {
      Serial.read();
      break;
    }
  }
}
