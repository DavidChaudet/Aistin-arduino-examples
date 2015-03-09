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
#ifndef LP5523_h
#define LP5523_h

#define LP5523_ADDR 0x34
#define LED1 0
#define LED2 1
#define LED3 2


enum led_selection_t { 	LED1_R = 0x0040, LED1_G = 0x0001, LED1_B = 0x0002, LED2_R = 0x0080, LED2_G = 0x0004, 
						LED2_B = 0x0008, LED3_R = 0x0100, LED3_G = 0x0010, LED3_B = 0x0020, GPO  = 0x8000 };
enum sign_t { UP, DOWN };
enum prescale_t { NOPRESCALE, PRESCALE };
enum step_time_t {	time_0ms5 = 1, time_1ms, time_1ms5, time_2ms, time_2ms5, time_3ms, time_3ms5, time_4ms, time_4ms5, time_5ms,
					time_5ms5, time_6ms, time_6ms5, time_7ms, time_7ms5, time_8ms, time_8ms5, time_9ms, time_9ms5, time_10ms,
					time_10ms5, time_11ms, time_11ms5, time_12ms, time_12ms5, time_13ms, time_13ms5, time_14ms, time_14ms5, time_15ms, 
					time_15ms5, time_16ms = 33, time_32ms, time_48ms, time_64ms, time_80ms, time_96ms, time_112ms, time_128ms, time_144ms,
					time_160ms, time_176ms, time_192ms, time_208ms, time_224ms, time_240ms, time_256ms, time_272ms, time_288ms, time_304ms,
					time_320ms, time_336ms, time_352ms, time_368ms, time_384ms, time_400ms, time_416ms, time_432ms, time_448ms, time_464ms,
					time_480ms, time_496ms };
enum engines_t { ENGINE1 = 1, ENGINE2 = 2, ENGINE3 = 4 };
enum eng_instr_t { DISABLE = 0b0000, LOAD = 0b0100, HOLD = 0b1000, STEP = 0b1001, FREE_RUN = 0b1010, EXEC_ONCE = 0b1011, HALT = 0b1100 };
enum variable_t { VARIABLE_A, VARIABLE_B, VARIABLE_C, VARIABLE_D }; //variables A & B are per engine, C is public and D is value from register address 0x3C
enum trigger_t { 	SEND_ENGINE1 = 0x0002, SEND_ENGINE2 = 0x0004, SEND_ENGINE3 = 0x0008, SEND_EXTERNAL = 0x0040, 
					WAIT_ENGINE1 = 0x0080, WAIT_ENGINE2 = 0x0100, WAIT_ENGINE3 = 0x0200, WAIT_EXTERNAL = 0x1000};
enum temperature_control_t {USER_DEFINED = 1, READ_ONCE = 4, CONTINUOUS_CONV = 6};

class LP5523 {
private:
	bool genCodePointerIncrement(void);
public:
	uint8_t genCodePointer; //pointer used in generating opcode
	uint16_t genCode[96]; //generated opcode
	bool op_ledMapping(uint16_t); //led mapping instruction for op code
	bool op_ramp(step_time_t, sign_t, uint8_t);
	bool op_ramp(uint8_t, sign_t, uint8_t, prescale_t); 
	bool op_set_pwm(uint8_t); 
	bool op_wait(step_time_t); 
	bool op_wait(uint8_t, prescale_t);
	bool op_mux_ld_start(uint8_t); 
	bool op_mux_map_start(uint8_t);
	bool op_mux_ld_end(uint8_t);
	bool op_mux_sel(led_selection_t);
	bool op_mux_sel(uint8_t);
	bool op_mux_clr(void);
	bool op_mux_map_next(void);
	bool op_mux_map_prev(void);
	bool op_mux_ld_next(void);
	bool op_mux_ld_prev(void);
	bool op_mux_ld_addr(uint8_t);
	bool op_mux_map_addr(uint8_t);
	bool op_rst(void);
	bool op_branch(uint8_t, uint8_t);
	bool op_int(void);
	bool op_end(bool, bool);
	bool op_trigger(trigger_t);
	bool op_variable_load(variable_t, uint8_t);
	bool op_variable_add(variable_t, uint8_t);
	bool op_variable_add(variable_t, variable_t, variable_t);
	bool op_variable_sub(variable_t, uint8_t);
	bool op_variable_sub(variable_t, variable_t, variable_t);
	bool op_jump_if_not_equal(uint8_t, variable_t, variable_t);
	bool op_jump_if_less(uint8_t, variable_t, variable_t);
	bool op_jump_if_greater(uint8_t, variable_t, variable_t);
	bool op_jump_if_equal(uint8_t, variable_t, variable_t);
	void resetCode(void);
	void uploadCode(void);
	void engineStartAddress(uint8_t, uint8_t);
	void engineControl(uint8_t, eng_instr_t);
	void init(void);
	void reset(void);
	void setCurrent(uint8_t);
	void setLogDimm(bool);
	void setLed(uint8_t, uint8_t, uint8_t, uint8_t);
	void tempControl(temperature_control_t);
	int8_t readTemperature(void);
	void writeTemperature(uint8_t);
	uint8_t readReg(uint8_t);
	void writeReg(uint8_t, uint8_t);
	};

#endif