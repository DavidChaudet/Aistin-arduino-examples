/*
	aistin.cpp - Aistin library
	
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

#include <Wire.h>
#include <aistin.h>

uint8_t aistin::readReg(uint8_t sensorAddress, uint8_t regAddress)
{
	uint8_t regValue;
	Wire.beginTransmission(sensorAddress);
    Wire.write(regAddress);
    Wire.endTransmission();
    Wire.requestFrom(sensorAddress, (uint8_t)1);
	regValue = Wire.read();
	Wire.endTransmission(true);
	return regValue;
}

uint8_t aistin::readReg(uint8_t sensorAddress, uint8_t regAddress, uint8_t *regValue, uint8_t quanity, bool autoIncrement)
{
	Wire.beginTransmission(sensorAddress);
	if(autoIncrement){
		Wire.write(regAddress);
		Wire.endTransmission(false);
		Wire.requestFrom(sensorAddress, quanity);
		for(int i=0 ; i<quanity ; i++)
			regValue[i] = Wire.read();
	}
	else {
		for(size_t i=0 ; i<quanity ; i++){
			Wire.write(regAddress+i);
			Wire.endTransmission(false);
			Wire.requestFrom(sensorAddress, (uint8_t)1);
			regValue[i] = Wire.read();
			if( i<(quanity-1) ){
				Wire.endTransmission(false);
				Wire.beginTransmission(sensorAddress);
			}
		}
	}
		Wire.endTransmission(true);
}

uint8_t aistin::writeReg(uint8_t sensorAddress, uint8_t regAddress, uint8_t *regValue, size_t quanity, bool autoIncrement)
{
	Wire.beginTransmission(sensorAddress);
	if(autoIncrement) {
		Wire.write(regAddress);
		Wire.write(regValue, quanity);
	}
	else {
		for(size_t i=0 ; i<quanity ; i++){
			Wire.write(regAddress+i);
			Wire.write(regValue[i]);
			if( i<(quanity-1) ){
				Wire.endTransmission(false);
				Wire.beginTransmission(sensorAddress);
			}
		}
	}
	return Wire.endTransmission(true);
}
uint8_t aistin::writeReg(uint8_t sensorAddress, uint8_t regAddress, uint8_t regValue)
{
	Wire.beginTransmission(sensorAddress);
	Wire.write(regAddress);
	Wire.write(regValue);
	return Wire.endTransmission(true);
}