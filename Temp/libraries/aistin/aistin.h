/*
	aistin.h - Aistin library
	
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

#ifndef aistin_h
#define aistin_h

#include <stdint.h>
#include <stdlib.h>
//enum enum_example {EXAMPLE_VALUE1 = 1, EXAMPLE_VALUE2, EXAMPLE_VALUE3 };

class aistin {
private:
	
public:
	static uint8_t readReg(uint8_t, uint8_t);
	static uint8_t readReg(uint8_t, uint8_t, uint8_t *, uint8_t, bool autoIncrement=true);
	static uint8_t writeReg(uint8_t, uint8_t, uint8_t);
	static uint8_t writeReg(uint8_t, uint8_t, uint8_t *, size_t, bool autoIncrement=true);
};

#endif