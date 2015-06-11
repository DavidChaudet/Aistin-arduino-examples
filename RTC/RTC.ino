/* 
 * TimeSerial.pde
 * example code illustrating Time library set through serial port messages.
 *
 * Messages consist of the letter T followed by ten digit time (as seconds since Jan 1 1970)
 * you can send the text on the next line using Serial Monitor to set the clock to noon Jan 1 2013
 T1357041600  
 *
 * A Processing example sketch to automatically send the messages is inclided in the download
 * On Linux, you can use "date +T%s\n > /dev/ttyACM0" (UTC time zone)
 */ 
 
#include <Time.h>
#include <aistin.h>
#include <RV4162.h>
#include <Wire.h>

RV4162 RTC;

void setup()  {
  Wire.begin();
  Serial.begin(9600);
  delay(1500-(millis()%1000)); //prevent second changing at the same time we are reading it later
  setSyncProvider(rtcSync);  //set sync function
  while(!Serial);
  Serial.println("give time in unix format eg. 't1433123456'");
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
     RTC.setTime(serialTime); 
     setTime(serialTime);
  }
  else if(serialData == 's') //Sync Arduino clock with the time of RTC
    setTime(RTC.now());
}

