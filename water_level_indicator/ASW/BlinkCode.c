/*
 * BlinkCode.c
 *
 * Created: 10/17/2017 6:01:30 PM
 *  Author: Nikhil
 */ 
#include "BlinkCode.h"
#define Timeslice 5
static Pin BlinkPin;
static uint8_t DurationTime;
static uint16_t CurrentBlink;

static Ports Prt;
void SetBlink(Pin p,uint16_t Duration /*higher for the id and lower nibble for number of blinks in a second*/,Ports port)
{   
	
	if((Duration&0x00ff)>DurationTime)
	{
			BlinkPin=p;
			DurationTime=Duration&0x00FF;
			CurrentBlink=Duration&0xf000;
			Prt=port;
	}
    else if((Duration&0x00ff)==0)
	{
		if((Duration&0xf000)==CurrentBlink)
		{
			
			DurationTime=0;
		}
	}
}

void Blink()
{
	static uint16_t countBlink;
	static uint8_t BlinkOut;
	if(DurationTime)
	{ 
		
	if(countBlink>=((5000/Timeslice)/DurationTime))
	{
		BlinkOut=BlinkOut^1;
		PinOutput(BlinkOut,BlinkPin,Prt);
		countBlink=0;
		countBlink++;
	}
	else
	{
		countBlink++;		
	}
	}
	else
	{
		PinOutput(0,BlinkPin,Prt);
	}
}