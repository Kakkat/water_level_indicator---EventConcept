/*
 * Timer2.h
 *
 * Created: 10/25/2016 9:20:41 PM
 *  Author: Nikhil
 */ 
#include <avr/io.h>

#ifndef TIMER2_H_
#define TIMER2_H_

void Timer2Enable();
uint8_t Timer2Count();
void Timer2Disable();
volatile uint16_t TimerValue;
volatile uint8_t  overflowfag;
volatile uint8_t  TimeReady;

#endif /* TIMER2_H_ */