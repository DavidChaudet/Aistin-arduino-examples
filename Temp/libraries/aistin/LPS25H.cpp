/*
	LPS25H.cpp - LPS25H library for Aistin ATMega
	
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
// #include <LPS25H.h>
// #include <Wire.h>
// #include <math.h>
// #include <stdint.h>
// #include <arduino.h>

#include <LPS25H.h>

uint8_t LPS25H::sensorAddress = 0x5D;

uint8_t LPS25H::init(void)
{
	uint8_t ctrl_reg_values[4] = {0xC0, 0x00, 0x00, 0x00};
	return writeReg(0x20, ctrl_reg_values, sizeof(ctrl_reg_values));
}
void LPS25H::siScale(int16_t &x, int16_t &y, int16_t &z)
{
	
}
int32_t LPS25H::readPressure()
{
	uint8_t sensorData[3];
	readReg(0x28, sensorData, 3);
	return ((int8_t)sensorData[2])*65536+sensorData[1]*256+sensorData[0]; 
}
uint8_t LPS25H::readReg(uint8_t regAddress)
{
	return aistin::readReg(sensorAddress, regAddress);
}

void LPS25H::readReg(uint8_t regAddress, uint8_t *regValue, uint8_t quanity)
{
	regAddress = 0x80 | regAddress; //set MSB to 1 to auto increment
	aistin::readReg(sensorAddress, regAddress, regValue, quanity);
}
uint8_t LPS25H::writeReg(uint8_t regAddress, uint8_t regValue)
{
	return aistin::writeReg(sensorAddress, regAddress, regValue);
}
uint8_t LPS25H::writeReg(uint8_t regAddress, uint8_t *regValue, size_t quanity)
{
	regAddress = 0x80 | regAddress; //set MSB to 1 to auto increment
	return aistin::writeReg(sensorAddress, regAddress, regValue, quanity);
}