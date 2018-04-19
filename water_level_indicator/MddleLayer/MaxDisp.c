/*
 * MaxDisp.c
 *
 * Created: 9/17/2016 5:16:06 AM
 *  Author: neethu
 */ 
#include "MaxDisp.h"
#include "..\BaseLayer\SPI.h"
#include "..\BaseLayer\pinout.h"
void WriteMax(uint8_t address,uint8_t data)
{
	PinOutput(OFF,PIN_OUT2,B);
	spi_tranceiver(address);
	spi_tranceiver(data);
	PinOutput(ON,PIN_OUT2,B);
}
void InitMax()
{
	 PinOutput(OFF,PIN_OUT2,B);
	 spi_init_master();
	 spi_dataorder(0);
	 spi_clockspeed(Divby0);
	 spi_clockphase(2);
	 PinOutput(OFF,PIN_OUT2,B);
	 spi_tranceiver(DECODEMODE);
	 spi_tranceiver(0xFF);
	 PinOutput(ON,PIN_OUT2,B);
	 PinOutput(OFF,PIN_OUT2,B);
	 spi_tranceiver(SCANLIMIT);
	 spi_tranceiver(0x01);
	 PinOutput(ON,PIN_OUT2,B);
	 PinOutput(OFF,PIN_OUT2,B);
	 spi_tranceiver(POWERON);
	 spi_tranceiver(0x01);
	 PinOutput(ON,PIN_OUT2,B);
	 PinOutput(OFF,PIN_OUT2,B);
	 spi_tranceiver(INTENSITY);
	 spi_tranceiver(0x03);
	 PinOutput(ON,PIN_OUT2,B);
	 PinOutput(OFF,PIN_OUT2,B);
	 spi_tranceiver(0x07);
	 spi_tranceiver(0x03);
	 PinOutput(ON,PIN_OUT2,B);
	 PinOutput(OFF,PIN_OUT2,B);
}

void ScanlimitExpand(uint8_t num)
{

	PinOutput(OFF,PIN_OUT2,B);
	spi_tranceiver(SCANLIMIT);
	spi_tranceiver(num);
	PinOutput(ON,PIN_OUT2,B);	
}

void DispDigits(uint16_t num)
{
		WriteMax(Digit5,0x0f);
		WriteMax(Digit4,0x0f);
		WriteMax(Digit3,0x0f);
		WriteMax(Digit2,0x0f);
		uint8_t count=0,digit=0;
		while (num)
		{
			digit=num%10;
			WriteMax(count+1,digit);
			num=num/10;
			count++;
		}
		if(count>0)
		{
			count=count-1;
		}
		
	//ScanlimitExpand(count);
}

void DispChar(uint16_t num,uint8_t MaxDispPos)
{
	static uint8_t count,DigitScrollPos,Digitpos;
	static Digits d[4]={Digit8,Digit7,Digit6,Digit5};
	//static uint8_t Dispval dis[4]={13,num,5,8};
	count++;
	if(count>100)
	{
		if(DigitScrollPos<4)
		{
        if(DigitScrollPos==3)
		{
	 	WriteMax(d[0],num);
	 	WriteMax(d[1],5);		
	 	WriteMax(d[2],8);
		WriteMax(d[3],0x0f);
		}
		        if(DigitScrollPos==0)
		        {
			        WriteMax(d[1],num);
			        WriteMax(d[2],5);
			        WriteMax(d[3],8);
			        WriteMax(d[0],0x0f);
		        }
				        if(DigitScrollPos==1)
				        {
					        WriteMax(d[2],num);
					        WriteMax(d[3],5);
					        WriteMax(d[0],8);
					        WriteMax(d[1],0x0f);
				        }
						        if(DigitScrollPos==2)
						        {
							        WriteMax(d[3],num);
							        WriteMax(d[0],5);
							        WriteMax(d[1],8);
							        WriteMax(d[2],0x0f);
						        }
		 DigitScrollPos++;
		}
		else
		{
			DigitScrollPos=0;
		}
		count=0;
	}


	ScanlimitExpand(MaxDispPos);
}