/*
 * BaseTask.c
 *
 * Created: 3/22/2018 9:08:20 PM
 *  Author: Nikhil
 */ 
#include "..\BaseLayer\ExtInterrupt.h"
#include "..\BaseLayer\UART.h"
#include "..\BaseLayer\pinout.h"
#include "..\BaseLayer\SSDi2cHandler.h"

uint16_t BaseTask1(void)
{
	uint16_t PulseData=0;
	static uint8_t CountTaskTime,BTF;
	PulseData=InterfacePulse(PulseData);
	if(((uint8_t*)(&PulseData))[1]==0x80 || ((uint8_t*)(&PulseData))[1]==0x00 )
	{
		//CountTaskTime=CountTaskTime+2;
		if(CountTaskTime>127)
		{
			BTF=1;
		}
		if(BTF==1)
		{
			CountTaskTime=CountTaskTime-2;
		}
		else
		{
			CountTaskTime=CountTaskTime+2;
		}
		((uint8_t*)(&PulseData))[0]=CountTaskTime;
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
	return RetVal;
}

uint16_t BaseTask2Open(void)
{
	return 0;
}

uint16_t SSDtask(void)
{
	SSDi2cHandlerFunc(0);
	return 0xfffff;
}
uint16_t Testtask(void)
{
	static uint8_t count;
	count++;
	if(1)
	{
		count=0;
		testfuc(0);
	}
	
	return 0xfffff;
}