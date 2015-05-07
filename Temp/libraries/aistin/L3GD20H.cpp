/*
	L3GD20H.cpp - L3GD20H library for Aistin ATMega
	
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
// #include <L3GD20H.h>
// #include <Wire.h>
// #include <math.h>
// #include <stdint.h>
// #include <arduino.h>

#include <L3GD20H.h>

uint8_t L3GD20H::sensorAddress = 0x6A;

uint8_t L3GD20H::init(void)
{
	uint8_t ctrl_reg_values[5] = {0x0F, 0x00, 0x00, 0x00, 0x00};
	return writeReg(0xA0, ctrl_reg_values, sizeof(ctrl_reg_values));
}

void L3GD20H::readXYZ(int16_t &x, int16_t &y, int16_t &z) //read x, y, z data
{
	uint8_t sensorData[6];
	readReg(0xA8, sensorData, 6);
	x = ((int8_t)sensorData[1])*256+sensorData[0]; //return values
	y = ((int8_t)sensorData[3])*256+sensorData[2];
	z = ((int8_t)sensorData[5])*256+sensorData[4];
}
void L3GD20H::mgScale(int16_t &x, int16_t &y, int16_t &z)
{
	int scale = 2;
	//int32_t xAxis = x, yAxis = y, zAxis = z;
	x = (int32_t)x*1000/(1024*32/scale); //transform data to millig, for 2g scale xAxis*1000/(1024*16),
	y = (int32_t)y*1000/(1024*32/scale); //for 4g scale xAxis*1000/(1024*8),
	z = (int32_t)z*1000/(1024*32/scale); //for 8g scale xAxis*1000/(1024*4)
}
int L3GD20H::readX()
{
	uint8_t sensorData[2];
	readReg(0xA8, sensorData, 2);
	return ((int8_t)sensorData[1])*256+sensorData[0]; 
}
uint8_t L3GD20H::readReg(uint8_t regAddress)
{
	return aistin::readReg(sensorAddress, regAddress);
}

void L3GD20H::readReg(uint8_t regAddress, uint8_t *regValue, uint8_t quanity)
{
	//regAddress = 0x80 & regAddress; //set MSB to 1 to auto increment
	aistin::readReg(sensorAddress, regAddress, regValue, quanity);
}
uint8_t L3GD20H::writeReg(uint8_t regAddress, uint8_t regValue)
{
	return aistin::writeReg(sensorAddress, regAddress, regValue);
}
uint8_t L3GD20H::writeReg(uint8_t regAddress, uint8_t *regValue, size_t quanity)
{
	return aistin::writeReg(sensorAddress, regAddress, regValue, quanity);
}