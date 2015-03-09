/*
	LP5523.h - LP5523 library for iProtoXi Micro
	
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
#include <stdint.h>
#ifndef BH1772_h
#define BH1772_h

#define BH1772_ADDR 0x38

enum sensor_mode_control_t {STANDBY_ALP, DISABLE_ALP, TRIGGER_ALP, ON_ALP};
enum led_current_t {current_5mA, current_10mA, current_20mA, current_50mA, current_100mA, current_150mA, current_200mA};
enum select_trigger_t {proximity = 1, ambient = 2};
enum meas_rate_t {meas_time_10ms, meas_time_20ms, meas_time_30ms, meas_time_50ms, meas_time_70ms, meas_time_100ms, meas_time_200ms, meas_time_500ms, meas_time_1000ms, meas_time_2000ms, max_meas_rate};

class BH1772 {
private:
	
public:
	void reset(void);
	void ambientMode(sensor_mode_control_t);
	void proximityMode(sensor_mode_control_t);
	void ledCurrent(led_current_t);
	void trigger(select_trigger_t);
	void proximityMeasRate(meas_rate_t);
	bool ambientMeasRate(meas_rate_t);
	uint16_t readAmbient(void);
	uint8_t readProximity(void);
	void selectInterrupt(select_trigger_t);
	void proximityInterruptTresholdHigh(uint8_t);
	void proximityInterruptTresholdLow(uint8_t);
	void ambientInterruptTresholdHigh(uint16_t);
	void ambientInterruptTresholdLow(uint16_t);
	void ambientSensitivity(uint8_t);
	bool proximityPersistence(uint8_t);
	bool ambientPersistence(uint8_t);
	uint8_t readReg(uint8_t);
	void writeReg(uint8_t, uint8_t);
	};

#endif