/*
	TCS37725FN.cpp - TCS37725FN library for Aistin ATMega
	
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

#include <TCS37725FN.h>

uint8_t TCS37725FN::sensorAddress = 0x29;

uint8_t TCS37725FN::init(void)
{
	uint8_t reg_values[] = {0x07, 0xAD, 0xFF};
	writeReg(0x00, reg_values, sizeof(reg_values));
	uint8_t reg_values2[] = {0x10, 0xC0};
	return writeReg(0x0E, reg_values2, sizeof(reg_values2));
}
uint16_t TCS37725FN::readClear(void)
{
	uint8_t sensorData[2];
	readReg(0x14, sensorData, 2);
	return sensorData[1]*256+sensorData[0];
}
void TCS37725FN::readColors(uint16_t &red, uint16_t &green, uint16_t &blue) //read light color data
{
	uint8_t sensorData[6];
	readReg(0x16, sensorData, 6);
	red = sensorData[1]*256+sensorData[0]; //return values
	green = sensorData[3]*256+sensorData[2];
	blue = sensorData[5]*256+sensorData[4];
}
uint16_t TCS37725FN::readProximity(void)
{
	uint8_t sensorData[2];
	readReg(0x1C, sensorData, 2);
	return sensorData[1]*256+sensorData[0];
}
uint8_t TCS37725FN::readReg(uint8_t regAddress)
{
	regAddress = 0x80 | regAddress; //set MSB to 1 to inform sensor we are addressing COMMAND register
	return aistin::readReg(sensorAddress, regAddress);
}

void TCS37725FN::readReg(uint8_t regAddress, uint8_t *regValue, uint8_t quanity)
{
	regAddress = 0xA0 | regAddress; //set MSB & 5th bit to 1 to inform sensor we are addressing COMMAND register and it should auto increment
	aistin::readReg(sensorAddress, regAddress, regValue, quanity);
}
uint8_t TCS37725FN::writeReg(uint8_t regAddress, uint8_t regValue)
{
	regAddress = 0x80 | regAddress; //set MSB to 1 to inform sensor we are addressing COMMAND register
	return aistin::writeReg(sensorAddress, regAddress, regValue);
}
uint8_t TCS37725FN::writeReg(uint8_t regAddress, uint8_t *regValue, size_t quanity)
{
	regAddress = 0xA0 | regAddress; //set MSB & 5th bit to 1 to inform sensor we are addressing COMMAND register and it should auto increment
	return aistin::writeReg(sensorAddress, regAddress, regValue, quanity);
}