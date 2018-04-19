/*
 * BaseTask.c
 *
 * Created: 3/22/2018 9:08:20 PM
 *  Author: Nikhil
 */ 
#include "..\BaseLayer\ExtInterrupt.h"
#include "..\BaseLayer\UART.h"
#include "..\BaseLayer\pinout.h"
uint16_t BaseTask1(void)
{
	uint16_t PulseData=0;
	static uint8_t CountTaskTime;
   // uart_string("start\n");
	PulseData=InterfacePulse(PulseData);
	//uart_num(((uint8_t*)(&PulseData))[1]);
	if(((uint8_t*)(&PulseData))[1]==0x80 || ((uint8_t*)(&PulseData))[1]==0x00 )
	{
		((uint8_t*)(&PulseData))[0]=CountTaskTime++;
		return PulseData;
	}
    else
	{
		((uint8_t*)(&PulseData))[1]=0x01;
	}
	return PulseData;
}
uint16_t BaseTask1Open(void)
{
	return 0;
}

uint16_t BaseTask2(void)
{
	uint8_t value;
	uint16_t RetVal;
	static uint8_t ButtonCount,previousButtonVal,currenButtonvalue,SuccessCount;
	PinValue(&value,PIN_OUT3,B );
	//uart_num(value);
	if(value==previousButtonVal)
	{
		ButtonCount++;
		previousButtonVal=value;
	}
	else
	{
		ButtonCount=0;
		previousButtonVal=value;
	}
	if(ButtonCount>=10)
	{
		currenButtonvalue=value;
		ButtonCount=0;
	}
	SuccessCount++;
	if(SuccessCount>200)
	{
	  	
	  	((uint8_t *)&RetVal)[1]=0x02;
		SuccessCount=0;	
	}
	else
	{
		((uint8_t *)&RetVal)[1]=0x03;
	}
    ((uint8_t *)&RetVal)[0]=currenButtonvalue;
	
	//uart_string("\n");
	return RetVal;
}

uint16_t BaseTask2Open(void)
{
	return 0;
}