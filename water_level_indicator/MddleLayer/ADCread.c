/*
 * ADCread.c
 *
 * Created: 8/6/2016 8:54:25 PM
 *  Author: neethu
 */ 

#include "..\BaseLayer\ADC.h"
#include "ADCread.h"
#include "..\RTE Base\RTEAdcBase.h"
#include "..\BaseLayer\UART.h"
#define CHANNEL 0x07
#define ChannelSize 6
#define Buffer_empty 0
#define start 0
#define busy 1
#define done 2
static volatile uint8_t ChannelSelect;
static volatile uint8_t ChannelStatus;
static ChannelBuffer channelBuffer_s[6]={{0xff,0,0},{0xff,0,0},{0xff,0,0},{0xff,0,0},{0xff,0,0},{0xff,0,0}};
static uint8_t BufferLength;
static volatile uint16_t ADC_Array[10];
static uint8_t checkAlreadyThere(ChannelBuffer *Channel);
uint16_t ReadEveryValueADC(void)
{
	uint16_t Channel=0,status;
	static uint8_t position,conversionFlag;
	uint16_t Value;
	  if(conversionFlag==0)
	  { 
		  
		 if(channelBuffer_s[position].filled==1&&channelBuffer_s[position].State==start)
		 {
			 //uart_num(channelBuffer_s[position].channel);
			 adc_read(channelBuffer_s[position].channel);
			 channelBuffer_s[position].State=busy;
			 conversionFlag=1;
		 } 	
		 else
		 {
			 position++;
		 }
	  }
	  else if(ADC_State()==0)
	  {   
		  if(channelBuffer_s[position].State==busy)
		  {  
			 //uart_string("in Second");
			 ADC_Array[channelBuffer_s[position].channel]=ADCValue();
			 channelBuffer_s[position].State=done;
			 position++;
			 conversionFlag=0;
		  }
	  }
	  if(position==6)
	  {
		  position=0;
	  }

	
	return 0;
}

uint16_t GetADC_Value(uint16_t ADC_ChannelAndValue)
{
	uint16_t returnValue=0;
	uint8_t *array=&ADC_ChannelAndValue;
	static uint8_t FreeBuffer,bufferpos;
	ChannelBuffer channelProp={0};
	ChannelSelect=(array[1]>>3)&CHANNEL;
	channelProp.channel=ChannelSelect;
    bufferpos=checkAlreadyThere(&channelProp);
	
	if(channelProp.filled==0)
	{
        
		if(BufferLength==6)
		{
			if(channelBuffer_s[Buffer_empty].filled=Buffer_empty)
			    {
						BufferLength=0;
				}
		}
		else
		{
			if(channelBuffer_s[BufferLength].filled!=Buffer_empty)
			{
				FreeBuffer=1;
			}
		}
		if(FreeBuffer==Buffer_empty)
		{
			channelBuffer_s[BufferLength].channel=ChannelSelect;
			channelBuffer_s[BufferLength].filled=1;
			BufferLength++;
			//uart_num(BufferLength);
		}
		
	}
	if(channelProp.State==done)
	{
		returnValue=ADC_Array[channelProp.channel];
		returnValue|=0x8000;
		channelBuffer_s[bufferpos].channel=ChannelSelect;	
		channelBuffer_s[bufferpos].State=0;
		channelBuffer_s[bufferpos].filled=1;
	}
	else
	{
		returnValue|=0x0000;
	}
    //returnValue|=0x8000;
	return returnValue;
}

static uint8_t checkAlreadyThere(ChannelBuffer *Channel)
{
	uint8_t state=0,buffpos;
	
	for(int index=0;index<6;index++)
	{
		if(channelBuffer_s[index].channel==Channel->channel)
		{
          Channel->State=channelBuffer_s[index].State;
		  Channel->filled=1;
		  buffpos=index;
		  break;
		}
	}
	return buffpos;
}