/*
 * CircularQueue.c
 *
 * Created: 6/17/2017 6:16:54 PM
 *  Author: Nikhil
 */ 
#include "CircularQueue.h"
#include "UART.h"
CbuffState_t PushIntoCircularBuffer(Cbuff_t* CircularBuffer,unsigned char data)
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

CbuffState_t PopFromCircularBuffer(Cbuff_t  *CircularBuffer,unsigned char *data)
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

CbuffState_t IsBuffempty(Cbuff_t  *CircularBuffer)
{
		if(CircularBuffer->tail==CircularBuffer->head)
		{
			return BuffEmpty;
		}
	return BuffOk;
}

uint8_t HeadTailDiff(Cbuff_t  *CircularBuffer,uint8_t dat)
{
	if(CircularBuffer->tail>CircularBuffer->head)
	{
		return ((CircularBuffer->MaxLen-CircularBuffer->tail)+CircularBuffer->head);
	}
	else
	{
		return (CircularBuffer->head-CircularBuffer->tail);
	}
}