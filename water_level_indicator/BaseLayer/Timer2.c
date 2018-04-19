/*
 * Timer2.c
 *
 * Created: 10/25/2016 9:20:19 PM
 *  Author: Nikhil
 */ 
#include "Timer2.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
void Timer2Enable()
{
	overflowfag=0;
	TimeReady=0;
	TCCR2B|=1<<CS21|1<<CS22;
	TIMSK2|=(1<<TOIE2);
	TCNT2 = 0;
	TimerValue=0;
	//TCCR1B|=1<<CS11|1<<CS10;
	//TCCR1A=0;
	//TIMSK1|=(1<<TOIE1);
	//TCNT1L = 0;
	//TCNT1H=0;
}

uint8_t Timer2Count()
{
    TimerValue=TCNT2;//((TCNT1L)*16)/58;//;	
	Timer2Disable();
	TCNT2=0;
	return TCNT2;
}
void Timer2Disable()
{
	TCCR2B=0;
	TimeReady=1;	
}
ISR(TIMER2_OVF_vect)
{
	overflowfag=overflowfag+1;
	//uart_num(overflowfag);
	//TIMSK2|=(1<<TOIE2);
	//TimerValue+=255;
}