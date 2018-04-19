/*
 * SignalHandler.c
 *
 * Created: 3/23/2018 6:04:22 PM
 *  Author: Nikhil
 */ 
#include "..\OS\EventQ.h"
static uint16_t SignalData[5];
uint16_t SignalHandlerFunc(void *data)
{
	uint8_t *ptr=(uint8_t*)data;
	uint16_t reval;
	if(ptr[0]==0)
	{
		
		if(((uint8_t*)&SignalData[ptr[1]])[1]==2)
		{
			reval= SignalData[ptr[1]];
			((uint8_t*)&SignalData[ptr[1]])[1]=0;
		}
		else 
		{
			PushEventInterface(50,SignalHandlerFunc,0,ptr[2]);
			reval= SignalData[ptr[1]];
			((uint8_t*)&SignalData[ptr[1]])[1]=1;
		}
	}
	else if(ptr[0]==1)
	{
		((uint8_t*)&SignalData[ptr[1]])[0]=ptr[2];
		((uint8_t*)&SignalData[ptr[1]])[1]=2;
		//uart_string("here");
	}
	
	return reval;
}