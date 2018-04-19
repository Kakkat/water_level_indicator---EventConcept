#ifndef PINOUT_H_
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#define ON 1
#define OFF 0
typedef enum
{
 PIN_OUT1,
 PIN_OUT2,
 PIN_OUT3,
 PIN_OUT4,
 PIN_OUT5,
 PIN_OUT6,
 PIN_OUT7,
 PIN_OUT8
}Pin;
typedef enum
{
B,
C,
D		
}Ports;
void PinOutConfig(uint8_t,Pin,Ports);
void PinOutput(uint8_t b , Pin a, Ports c);
void PinValue(uint8_t *Value,Pin Pin_s,Ports Port_s);
#endif


