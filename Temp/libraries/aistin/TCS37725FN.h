/*
	TCS37725FN.h - TCS37725FN library for Aistin ATMega
	
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
#include "aistin.h"
#include <stdint.h>

#ifndef TCS37725FN_h
#define TCS37725FN_h

class TCS37725FN {
public:
	static uint8_t sensorAddress;
	uint8_t init(void);
	uint16_t readClear(void);
	void readColor(uint16_t&, uint16_t&, uint16_t&);
	uint16_t readProximity(void);
	void siScale(int16_t&, int16_t&, int16_t&);
	uint8_t readReg(uint8_t);
	void readReg(uint8_t, uint8_t *, uint8_t);
	uint8_t writeReg(uint8_t, uint8_t);
	uint8_t writeReg(uint8_t, uint8_t *, size_t);
	};
	
#endif