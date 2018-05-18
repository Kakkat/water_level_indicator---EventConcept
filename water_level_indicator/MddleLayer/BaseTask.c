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
		if(((uint8_t*)(&PulseData))[1]==0x00)
		{
			((uint8_t*)(&PulseData))[0]=255;
		}
		((uint8_t*)(&PulseData))[1]=0x00;
		/*if(CountTaskTime>127)
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
		}*/
		//((uint8_t*)(&PulseData))[0]=CountTaskTime;
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
	PinValue(&value,PIN_OUT2,B );
	//uart_num(value);
	if(value==previousButtonVal)
	{
		ButtonCount++;
		previousButtonVal=value;
		currenButtonvalue=value;
		((uint8_t *)&RetVal)[1]=0x03;
		if(value==0)
		{
			PinOutput(1,PIN_OUT7,D);
		}
	}
	else
	{
		if(value!=0)
		{
		PinOutput(0,PIN_OUT7,D);
		if(ButtonCount>100)	
		{
			((uint8_t *)&RetVal)[1]=0x02;
			((uint8_t *)&RetVal)[0]=currenButtonvalue+3;
		}
		
		else if(ButtonCount>50 )
		{
			((uint8_t *)&RetVal)[1]=0x02;
			((uint8_t *)&RetVal)[0]=currenButtonvalue+2;
		}
		else if(ButtonCount>5)
		{
			((uint8_t *)&RetVal)[1]=0x02;
			((uint8_t *)&RetVal)[0]=currenButtonvalue+1;
		}
		else
		{
			((uint8_t *)&RetVal)[1]=0x03;
		}
		}
		else{
			((uint8_t *)&RetVal)[1]=0x03;
		}
		ButtonCount=0;
		previousButtonVal=value;
	}
/*	if(ButtonCount>=5)
	{
		currenButtonvalue=value;
		//ButtonCount=0;
		((uint8_t *)&RetVal)[1]=0x02;
	}
	else if(ButtonCount>=50)
	{
		
	}
	else
	{
		((uint8_t *)&RetVal)[1]=0x03;
	}*/
	/*SuccessCount++;
	if(SuccessCount>50)
	{
	  	
	  	((uint8_t *)&RetVal)[1]=0x02;
		SuccessCount=0;	
	}
	else
	{
		((uint8_t *)&RetVal)[1]=0x03;
	}*/
    //0((uint8_t *)&RetVal)[0]=currenButtonvalue;
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
	if(count>3)
	{
		count=0;
		testfuc(0);
	}
	
	return 0xfffff;
}