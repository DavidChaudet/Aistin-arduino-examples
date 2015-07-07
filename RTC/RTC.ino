/* 
 * RTC.ino
 * example code for Real Time Clock
 *
 * You can set time with message 't<unix timestamp>' 
 * 
 * On Linux, you can use "date +t%s\n > /dev/ttyACM0"
 * By J. Piippo iProtoXi 2015-07-07
*/ 
 
#include <Time.h>
#include <aistin.h>
#include <RV4162.h>
#include <Wire.h>

RV4162 RTC;

void setup()  {
  Wire.begin();
  Serial.begin(9600);
  setSyncProvider(rtcSync);  //set sync function
  while(!Serial);
  Serial.println("give time in unix format prefixed with 't' eg. 't1433123456'");
  //setSyncInterval(60); //set sync interval
}

void loop(){
  if(Serial.available())
    serialControl(); //set time by t[unix timestamp] eg. 't1433123456' or sync Arduino with RTC by entering 's'
  if(timeStatus() == timeSet)
    printTime();
  else{
    delay(1500-(millis()%1000)); //prevent second changing at the same time we are reading it later
    setTime(RTC.now());
  }
  delay(1000-(millis()%1000)); //delay 1s in 1ms accuracy
}

String stringNzeros(int number, int digits=2){
  uint8_t numberToArray[digits];
  String arrayToString = String();
  for(int i=1;i<=digits;i++){
    numberToArray[digits-i] = number%10;
    number = number/10;
  }
  for(int i=0;i<digits;i++)
    arrayToString += String(numberToArray[i]); 
  return arrayToString;
}

void printTime(){
  Serial.println(stringNzeros(year(), 4) +'/'+  //yyyy
                 //stringNzeros(year(), 2) +'/'+  //yy
                 //monthShortStr(month()) +'/'+ //Month short
                 monthStr(month()) +'/'+ //Month full
                 //stringNzeros(month() +'/'+ //MM
                 stringNzeros(day()) +' '+ //dd
                 dayShortStr(weekday()) +' '+ //Day of the week short
                 //dayShortStr(weekday()) +' '+ //Day of the week full
                 stringNzeros(hour()) +':'+ //hh
                 stringNzeros(minute()) +':'+ //mm
                 stringNzeros(second())); //ss
}
time_t rtcSync()
{
  Serial.println("Syncing..");
  return RTC.now();
}

void serialControl() {
  char serialData = Serial.read();
  if(serialData == 't') { // Sync RTC & Arduino to the time given through serial
    uint32_t serialTime = Serial.parseInt();
    delay(100);
    RTC.setTime(serialTime); 
    setTime(serialTime);
  }
  else if(serialData == 's') //Sync Arduino clock with the time of RTC
    setTime(RTC.now());
}

