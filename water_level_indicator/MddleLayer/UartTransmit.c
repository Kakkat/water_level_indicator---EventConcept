/*
 * UartTransmit.c
 *
 * Created: 10/15/2017 3:14:40 PM
 *  Author: Nikhil
 */ 
#include "..\BaseLayer\UART.h"
#include "..\BaseLayer\CircularQueue.h"
#include "UartTransmit.h"
#include "..\OS\EventQ.h"
//ToTransmit=dataUart;
#define  circularbuffOut(x,y) \
static volatile unsigned char  ESPUartDataOut[y];   \
volatile Cbuff_t x={                \
	ESPUartDataOut,           \
	0,                     \
	0,                     \
	y                      \
};                          \

circularbuffOut(CircularBufferOut,100);
void DataTransmit()
{
	static unsigned char data='&';
	if(CheckUartReadyToSend()==0 && PopFromCircularBuffer(&CircularBufferOut,&data)==BuffOk)
	{    

			//UDR=data;
		SendByte(data);

	}

}

void FillUartBuffer(unsigned char *Uchar)
{
	
	while(*Uchar)
	{
	   //uart_char(*Uchar);
	   PushIntoCircularBuffer(&CircularBufferOut,*Uchar++);	
	}
	
}
void FillUartBufferSiglechar(char Uchar)
{
	PushIntoCircularBuffer(&CircularBufferOut,Uchar);	
}
void TransmitBufferEmpty()
{
	if(IsBuffempty(&CircularBufferOut)==BuffOk)
	{

		PushEventInterface(3,DataTransmit,0,0);
	}
}
