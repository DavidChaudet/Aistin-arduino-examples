/*
  Basic led board engine example
  Generates breath engine code and uploads it into controller.
  
  By J. Piippo iProtoXi 2015-07-07
*/

#include <Wire.h>
#include <LP55231.h>

LP55231 led;


void setup()
{
  digitalWrite(4, HIGH); //Sensor enable
  Wire.begin(); // join i2c bus
  led.reset(); // reset the controller
  led.init(); // initialize the controller
  led.setLogDimm(true); // set logarithmic dimming
  led.setCurrent(1); // limit current to 1mA
  
  led.resetCode(); //reset opcode
  led.engineControl(ENGINE1, LOAD); //set engine1 to load mode
  opcodeBreath(); //generate breath opcode
  led.uploadCode(); //upload generated code
  led.engineControl(ENGINE1, FREE_RUN); //turn engine1 on
  delay(200);
}
void opcodeBreath(void) //
{ 
/*
  Breath opcode generating function.
  Basic example for opcode generation.
*/
  led.genCodePointer = 0x00;
  led.op_mux_map_addr(0x10); //get led mapping from program memory slot 0x10
  led.op_set_pwm(100); //set pwm to 100  
  led.op_ramp(STEP_15ms5, UP, 125); //increase pwm 125 times with 15.5ms interval
  led.op_ramp(STEP_32ms, DOWN, 125); //decrease pwm 125 times with 15.5ms interval
  led.op_wait(STEP_480ms); //wait 480ms
  led.op_branch(0, 2); //loop from 3rd instruction infinitely
  
  led.genCodePointer = 0x10; //set code pointer to 0x10
  led.op_ledMapping(LED1_B | LED2_B  | LED3_B); //map blue leds

  led.engineStartAddress(ENGINE1, 0x00); //set engine 1 start address to 0x00
}

void loop()
{
 //do nothing, led controller is controlling the leds
}
