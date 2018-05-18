/*
 * ExtInterrupt.c
 *
 * Created: 10/23/2016 1:46:13 PM
 *  Author: Nikhil
 */
 
#include "ExtInterrupt.h"
#include "pinout.h"
#include "UART.h"
void ExtIntInit()
{
	
	changeIntLogic(1);//MCUCR |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
	EIMSK  |= (1 << INT0);      // Turns on INT0
	Start=0;
	Status=1;
}

ISR (INT0_vect)
{   
	
	if(Start==0)
	{
		Timer2Enable();
		changeIntLogic(0);
		Start=1; 
		      
	}/* interrupt code here */
	else
	{   	
		Timer2Count();
		changeIntLogic(1);
		Start=0;
		Status=1;
		  
	}
	
}

static void TriggerUltraSonic(void)
{
	PinOutput(0,PIN_OUT8,D);
	_delay_us(2);
	PinOutput(1,PIN_OUT8,D);
	_delay_us(5);
	PinOutput(0,PIN_OUT8,D);
}

void changeIntLogic(uint8_t logic)
{
	 
	if(logic==1)
	{
		//EICRA  |= (1 << ISC00)| (1 << ISC01); 
		EICRA  |= (1 << ISC00);
	}
	else
	{
		//EICRA  &=~(1<<ISC00);
		//EICRA  |= (1 << ISC01); 
		EICRA  |= (1 << ISC00);
	}
}

uint16_t InterfacePulse(uint16_t Pulse)
{
	static uint8_t timeout=0;
	uint8_t *Data=&Pulse;
    
	if(timeout>2)
	{
		changeIntLogic(1);
		TriggerUltraSonic();
		Status=0;
		Start=0;
		timeout=0;
		Pulse|=0x0000;
		//uart_num(timeout);
	}
	else
	{
		
			if(Status==1)
			{
				//TriggerUltraSonic();
				TimerValue=TimerValue+(overflowfag*255);
				TimerValue=(16*TimerValue)/58;// PRESCALER IS 256 so 1 count is 16us
				Pulse=TimerValue;
				Pulse|=0X8000;
				timeout=0;
				Status=0;
				TriggerUltraSonic();
			}
			else
			{
				Pulse|=0x1000;
				timeout++;
			}

	}
	return Pulse;
}
	
