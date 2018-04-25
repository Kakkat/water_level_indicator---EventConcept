/*
 * SSDdataHandler.c
 *
 * Created: 4/20/2018 2:11:56 PM
 *  Author: U338583
 */ 
#include "SSDdataHandler.h"
#include <string.h>
#define  circularbuffSSD(x,y) \
volatile  SSDdata SSDQ[y];   \
volatile SSDbuff_t x={                \
	SSDQ,                    \
	0,                     \
	0,                     \
	y                      \
};

circularbuffSSD(CircularBufferSSD,21);                    
CbuffState_t PushIntoSSDCircularBuffer(SSDbuff_t* CircularBuffer,SSDdata data)
{
	uint8_t next=CircularBuffer->head+1;
	CbuffState_t ReturnVal=BuffStateEndOfList;
	if(next>=CircularBuffer->MaxLen)
	{
		next=0;
	}
	
	if(next==CircularBuffer->tail)
	{
		return BuffFull;
	}
	
	else
	{
		
		CircularBuffer->buffer[CircularBuffer->head]=data;
		CircularBuffer->head=next;
		ReturnVal=BuffOk;
	}
	return ReturnVal;
}

CbuffState_t PopFromSSDCircularBuffer(SSDbuff_t  *CircularBuffer,SSDdata *data)
{
	uint8_t next=CircularBuffer->tail+1;
	if(CircularBuffer->tail==CircularBuffer->head)
	{
		return BuffEmpty;
	}
	else if(next>=CircularBuffer->MaxLen)
	{
		next=0;
	}
	
	*data=CircularBuffer->buffer[CircularBuffer->tail];
	CircularBuffer->tail=next;
	
	return BuffOk;
}

CbuffState_t IsSSDBuffempty(SSDbuff_t  *CircularBuffer)
{
	if(CircularBuffer->tail==CircularBuffer->head)
	{
		return BuffEmpty;
	}
	return BuffOk;
}

uint8_t PopulateSSDbuffer(unsigned char* SSDstring,uint8_t x,uint8_t y)
{
	SSDdata SSDdataMediator;
	uint8_t SSDlen;
	SSDlen=strlen(SSDstring)-1;
	SSDdataMediator.SSDx=x;
	SSDdataMediator.SSDy=y;

	while(*SSDstring)	
	{
		//uart_char(*SSDstring);
		SSDdataMediator.SSDchar=*SSDstring++;
		PushIntoSSDCircularBuffer(&CircularBufferSSD,SSDdataMediator);
		SSDdataMediator.SSDx=0;
		SSDdataMediator.SSDy=0;
	}
	return 1;
}
uint8_t PopulateSSDbufferChar(unsigned char SSDChar,uint8_t x,uint8_t y)
{
	SSDdata SSDdataMediator;
	SSDdataMediator.SSDx=x;
	SSDdataMediator.SSDy=y;
	SSDdataMediator.SSDchar=SSDChar;	
	PushIntoSSDCircularBuffer(&CircularBufferSSD,SSDdataMediator);
	return 1;
}
CbuffState_t PopSSDinterface(SSDdata *SSDdataPara)
{
	return (PopFromSSDCircularBuffer(&CircularBufferSSD,SSDdataPara));
}

uint8_t SSDHeadTailDiff(SSDbuff_t  *CircularBuffer)
{
	//uart_num(CircularBuffer->tail);
	//uart_num(CircularBuffer->head);
	if(CircularBuffer->tail>CircularBuffer->head)
	{
		return ((CircularBuffer->MaxLen-CircularBuffer->tail)+CircularBuffer->head);
	}
	else if(CircularBuffer->tail==CircularBuffer->head)
	{
		return 15;
	}
	else
	{
		return (CircularBuffer->head-CircularBuffer->tail);
	}
}