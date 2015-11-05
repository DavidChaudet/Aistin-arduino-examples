/*
	HTS221.cpp - HTS221 library for Aistin ATMega
	
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

#include <HTS221.h>
#include <Arduino.h>
uint8_t HTS221::sensorAddress = 0x5F;

uint8_t HTS221::init(void)
{
	uint8_t ctrl_reg_values[3] = {0x87, 0x00, 0x00};
	return writeReg(0xA0, ctrl_reg_values, sizeof(ctrl_reg_values));
}
void HTS221::readCalibration(void)
{
	int16_t C0; 
    int16_t C1; 
    int16_t T0; 
    int16_t T1; 
    int16_t RH0;
    int16_t RH1;
    int16_t H0; 
    int16_t H1; 
	
	uint8_t calibrationRegs[16];
	readReg(0xB0, calibrationRegs, 16);
    RH0 = calibrationRegs[0]; // e.g. 35.5
    RH1 = calibrationRegs[1]; // e.g. 70.5
    C0  = ((((uint16_t)(calibrationRegs[5] & 3))<<8) | ((uint16_t)calibrationRegs[2]));
    C1  = ((((uint16_t)(calibrationRegs[5] & 12))<<6) | ((uint16_t)calibrationRegs[3]));
    T0  = ((((uint16_t)calibrationRegs[13])<<8) | ((uint16_t)calibrationRegs[12]));
    T1  = ((((uint16_t)calibrationRegs[15])<<8) | ((uint16_t)calibrationRegs[14]));
    H0  = ((((uint16_t)calibrationRegs[7])<<8) | ((uint16_t)calibrationRegs[6])); // e.g. 4085
    H1  = ((((uint16_t)calibrationRegs[11])<<8) | ((uint16_t)calibrationRegs[10])); // e.g. 203.5
	
    CTf = ((float)C1 - (float)C0) / ((float)T1 - (float)T0) / 8.0;
    CTc = ((-1*(float)CTf * (float)T0) + (float)C0 )/ 8.0;
    RHf = ((float)RH1 - (float)RH0) / ((float)H1 - (float)H0) / 2.0;
    RHc = ((-1*(float)RHf * (float)H0) + (float)RH0 )/ 2.0;
}
int16_t HTS221::readHumidityRaw(void)
{
	uint8_t sensorData[2];
	readReg(0xA8, sensorData, 2);
	return ((int8_t)sensorData[1])*256+sensorData[0]; 
}
float HTS221::readHumidity(void)
{
	int16_t raw = readHumidityRaw();
	return (raw * RHf) + RHc;
}
uint16_t HTS221::readTemperatureRaw(void)
{
	uint8_t sensorData[2];
	readReg(0xAA, sensorData, 2);
	return ((int8_t)sensorData[1])*256+sensorData[0]; 
}
float HTS221::readTemperature(void)
{
	int16_t raw = readTemperatureRaw();
	return (CTf * raw) + CTc;
}
uint8_t HTS221::readReg(uint8_t regAddress)
{
	return aistin::readReg(sensorAddress, regAddress);
}

void HTS221::readReg(uint8_t regAddress, uint8_t *regValue, uint8_t quanity)
{
	regAddress = 0x80 | regAddress; //set MSB to 1 to auto increment
	aistin::readReg(sensorAddress, regAddress, regValue, quanity);
}
uint8_t HTS221::writeReg(uint8_t regAddress, uint8_t regValue)
{
	return aistin::writeReg(sensorAddress, regAddress, regValue);
}
uint8_t HTS221::writeReg(uint8_t regAddress, uint8_t *regValue, size_t quanity)
{
	regAddress = 0x80 | regAddress; //set MSB to 1 to auto increment
	return aistin::writeReg(sensorAddress, regAddress, regValue, quanity);
}