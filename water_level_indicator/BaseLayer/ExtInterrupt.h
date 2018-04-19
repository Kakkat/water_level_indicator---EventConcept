/*
 * ExtInterrupt.h
 *
 * Created: 10/23/2016 1:46:33 PM
 *  Author: Nikhil
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer2.h"

#ifndef EXTINTERRUPT_H_
#define EXTINTERRUPT_H_
static volatile uint8_t Status;
static volatile uint8_t Start;
void ExtIntInit();
uint16_t InterfacePulse(uint16_t Pulse);

#endif /* EXTINTERRUPT_H_ */