/*
	RV4162.cpp - RV4162 library for Aistin ATMega
	
	This program is free software under the MIT License (MIT)

	Copyright 2015 iProtoXi Oy

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
#include <Arduino.h>
#include <aistin.h>
#include <Time.h>
#include <RV4162.h>

uint8_t RV4162::deviceAddress = 0x68;

uint8_t RV4162::init(void)
{
	uint8_t reg01 = readReg(0x01) | 0x80;
	writeReg(0x01, reg01);
	return -1;
}
bool RV4162::enabled(void)
{
	return readReg(0x01) && 0x80;
}
bool RV4162::now(tmElements_t &tm)
{
	uint8_t time[8];
	readReg(0x00, time, 8);
	tm.Second = (bcd2dec(time[1] & 0x7F) + (bcd2dec(time[0])+50)/100)%60; //round to nearest second. 0x01 msb is OS bit  
	tm.Minute = bcd2dec(time[2] & 0x7F); //msb is OFIE bit
	tm.Hour = bcd2dec(time[3] & 0x3F); //[7:6] unused 
	tm.Wday = bcd2dec(time[4] & 0x07); //[2:0] day of the week, sunday == 1
	tm.Day = bcd2dec(time[5] & 0x3F); //[7:6] unused
	tm.Month = bcd2dec(time[6] & 0x3F); //[5:0] month
	tm.Year = CalendarYrToTm(2000 + ((time[6] & 0xC0)>>6) + bcd2dec(time[7])); //reg 0x06 [7:6] is century, reg 0x07 is the last 2 digits of the year
	if (time[1] & 0x80) return false; //clock is halted
	return true;
}
uint32_t RV4162::now(void)
{
	tmElements_t tm;
	now(tm);
	return (time_t)makeTime(tm);
}
bool RV4162::setTime(tmElements_t &tm)
{
	int16_t year = tmYearToCalendar(tm.Year)-2000;
	uint8_t time[8];
	readReg(0x01, &time[1], 7); //read current data to keep settings as they were
	time[0] = 0;
	time[1] = (time[1] & 0x80) | dec2bcd(tm.Second); //msb is OS bit
	time[2] = (time[2] & 0x80) | dec2bcd(tm.Minute); //msb is OFIE bit
	time[3] = (time[3] & 0xC0) | dec2bcd(tm.Hour); //[7:6] unused 
	time[4] = (time[4] & 0xF0) | dec2bcd(tm.Wday); //[2:0] day of the week, sunday == 1
	time[5] = (time[5] & 0xC0) | dec2bcd(tm.Day); //[7:6] unused
	time[6] = ((year/100)<<6) | dec2bcd(tm.Month); //[7:6] century, [5] unused, [4:0] month
	time[7] = dec2bcd(year%100); //reg 0x07 is the last 2 digits of the year
	writeReg(0x00, time, 8);
	return true;
}
bool RV4162::setTime(time_t t)
{
	tmElements_t tm;
	breakTime(t, tm);
	setTime(tm);
	return true;
}
uint8_t RV4162::readReg(uint8_t regAddress)
{
	return aistin::readReg(deviceAddress, regAddress);
}

void RV4162::readReg(uint8_t regAddress, uint8_t *regValue, uint8_t quanity)
{
	aistin::readReg(deviceAddress, regAddress, regValue, quanity);
}
uint8_t RV4162::writeReg(uint8_t regAddress, uint8_t regValue)
{
	return aistin::writeReg(deviceAddress, regAddress, regValue);
}
uint8_t RV4162::writeReg(uint8_t regAddress, uint8_t *regValue, size_t quanity)
{
	return aistin::writeReg(deviceAddress, regAddress, regValue, quanity);
}

uint8_t RV4162::dec2bcd(uint8_t dec)
{
  return ( ((dec/10)*16) + (dec%10) );
}

uint8_t RV4162::bcd2dec(uint8_t bcd)
{
  return ( ((bcd/16)*10) + (bcd%16) );
}