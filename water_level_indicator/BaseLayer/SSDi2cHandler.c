/*
 * SSDi2cHandler.c
 *
 * Created: 4/20/2018 3:54:13 PM
 *  Author: U338583
 */ 
#include <avr/io.h>
#include <util/twi.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "UART.h"
#include "..\MddleLayer\SSDdataHandler.h"
static uint8_t FramePos,ssdpos;
const char FrameBlank[] PROGMEM="          ";
/*Frame1 start*/
const char F1FROW1[] PROGMEM ="WIFI";
const char F1FROW2[] PROGMEM ="";
const char F1FROW3[] PROGMEM ="Tank Level :";
const char F1FROW4[] PROGMEM ="";
const char F1FROW5[] PROGMEM ="";
const char F1FROW6[] PROGMEM ="";
const char F1FROW7[] PROGMEM ="";
const char F1FROW8[] PROGMEM ="";
const char F1SROW1[] PROGMEM ="";
const char F1SROW2[] PROGMEM ="";
const char F1SROW3[] PROGMEM ="";
const char F1SROW4[] PROGMEM ="";
const char F1SROW5[] PROGMEM ="";
const char F1SROW6[] PROGMEM ="";
const char F1SROW7[] PROGMEM ="";
const char F1SROW8[] PROGMEM ="Menu";
const char F1MROW1[] PROGMEM ="";
const char F1MROW2[] PROGMEM ="";
const char F1MROW3[] PROGMEM ="";
const char F1MROW4[] PROGMEM ="";
const char F1MROW5[] PROGMEM ="";
const char F1MROW6[] PROGMEM ="";
const char F1MROW7[] PROGMEM ="";
const char F1MROW8[] PROGMEM ="";
/*Frame1 over*/

/*Frame2 start*/
const char F2FROW1[] PROGMEM ="WIFI";
const char F2FROW2[] PROGMEM ="";
const char F2FROW3[] PROGMEM =" 1.Settings";
const char F2FROW4[] PROGMEM =" 2.Motor";
const char F2FROW5[] PROGMEM =" 3.Debug";
const char F2FROW6[] PROGMEM =" 4.Sensor state";
const char F2FROW7[] PROGMEM ="";
const char F2FROW8[] PROGMEM ="";
const char F2SROW1[] PROGMEM ="";
const char F2SROW2[] PROGMEM ="";
const char F2SROW3[] PROGMEM ="";
const char F2SROW4[] PROGMEM ="";
const char F2SROW5[] PROGMEM ="";
const char F2SROW6[] PROGMEM ="";
const char F2SROW7[] PROGMEM ="";
const char F2SROW8[] PROGMEM ="BACK";
const char F2MROW1[] PROGMEM ="";
const char F2MROW2[] PROGMEM ="";
const char F2MROW3[] PROGMEM ="";
const char F2MROW4[] PROGMEM ="";
const char F2MROW5[] PROGMEM ="";
const char F2MROW6[] PROGMEM ="";
const char F2MROW7[] PROGMEM ="";
const char F2MROW8[] PROGMEM ="";
/*Frame2 over*/

const uint16_t Frame1[] PROGMEM=
{
	F1FROW1,
	F1FROW2,
	F1FROW3,
	F1FROW4,
	F1FROW5,
	F1FROW6,
	F1FROW7,
	F1FROW8,
	F1SROW1,
	F1SROW2,
	F1SROW3,
	F1SROW4,
	F1SROW5,
	F1SROW6,
	F1SROW7,
	F1SROW8,
	F1MROW1,
	F1MROW2,
	F1MROW3,
	F1MROW4,
	F1MROW5,
	F1MROW6,
	F1MROW7,
	F1MROW8 
};

const uint16_t Frame2[] PROGMEM=
{
	F2FROW1,
	FrameBlank,
	F2FROW3,
	F2FROW4,
	F2FROW5,
	F2FROW6,
	FrameBlank,
	FrameBlank,
	FrameBlank,
	FrameBlank,
	FrameBlank,
	F2SROW4,
	F2SROW5,
	F2SROW6,
	F2SROW7,
	F2SROW8,
	F2MROW1,
	F2MROW2,
	F2MROW3,
	F2MROW4,
	F2MROW5,
	F2MROW6,
	F2MROW7,
	F2MROW8
};

const uint16_t Frames[] PROGMEM=
{
	&Frame1,
	&Frame2
};
static uint8_t ssdposy=1,ssdposx,Unknown;
static uint8_t ErasePoints[5]={0};
static uint8_t ssd1306_AsyncStart(uint8_t address);
static uint8_t ssd1306_AsyncWrite(uint8_t SSDbyte);
uint8_t SSDsetXY(uint8_t x,uint8_t y);
uint8_t SSDWritechar_font6x8(char ch);
static uint8_t ssd1306_AsyncStart(uint8_t address)
{
	static uint8_t ssdStartState;
	uint8_t RetVal=2;
	switch (ssdStartState)
	{
		case 0:
		// reset TWI control register
		TWCR = 0;
		// transmit START condition
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		ssdStartState=1;
		break;
		case 1:
		if(EOTi2c()==1)
		{
			
			if((TWSR & 0xF8) == TW_START)
			{
				ssdStartState=2;
				
			}
			else
			{
				RetVal=0; //failed
			}
		}
		break;
		case 2:
		// load slave address into data register
		TWDR = address;
		// start transmission of address
		TWCR = (1<<TWINT) | (1<<TWEN);
		ssdStartState=3;
		break;
		case 3:
		if(EOTi2c())
		{
			uint8_t twst = TW_STATUS & 0xF8;
			if((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) )
			{
				RetVal=0;//failed
			}
			else
			{
				ssdStartState=0;
				RetVal=1;
			}
		}
        break;
		default:
		/* Your code here */
		break;
	}
	
	return RetVal;
}

static uint8_t ssd1306_AsyncWrite(uint8_t SSDbyte)
{   
	static uint8_t SSDwriteState;
	uint8_t RetVal=2;
	
	switch (SSDwriteState)
	{
			case 0:
			// load slave address into data register
			TWDR = SSDbyte;
			// start transmission of address
			TWCR = (1<<TWINT) | (1<<TWEN);
			SSDwriteState=1;
			break;
			case 1:
			//uart_num(SSDbyte);
			if(EOTi2c())
			{
				
				//uart_string("value:");
				//uart_num((TWSR & 0xF8));
				//uart_string("\n");
				if((TWSR & 0xF8) == TW_MT_DATA_ACK )
				{
					SSDwriteState=0;
					RetVal=1;
				}
				else
				{
					SSDwriteState=0;
					RetVal=0; //failed
				}
			}
			break;
		default:
		/* Your code here */
		break;
	}
	return RetVal;
}


uint8_t SSDi2cHandlerFunc(void * data)
{
	//uart_string("1.\n");
	static SSDdata SSDdataObj;
	static uint8_t SSDhandlerstates;
	char buffer[12];
	static uint8_t SSDR=0,SSDC=0;

	switch (SSDhandlerstates)
	{
		case 0:
		if(ErasePoints[0]==0)
		{
			if(PopSSDinterface(&SSDdataObj)==BuffOk)
			{
			   SSDhandlerstates=1;
			}
		}
	else
		{

		}
		/* Your code here */
		break;
        case 1:
		if((SSDdataObj.SSDx>0 )||(SSDdataObj.SSDy>0) )
		{
		 if(SSDsetXY(SSDdataObj.SSDx,SSDdataObj.SSDy)==1)
		   {
			  SSDhandlerstates=2; 
		   }
		}
		else
		{
		   SSDhandlerstates=2; 	
		}
		
		break;
		case 2:
		//ssd1306_String_font6x8_test("nikhil",0,0);
		if(SSDWritechar_font6x8(SSDdataObj.SSDchar)==1)
		{
			SSDhandlerstates=0;
			//uart_string("end\n");
		}
		break;
		default:
		/* Your code here */
		break;
	}
	
}


uint8_t SSDsetXY(uint8_t x,uint8_t y)
{
	static uint8_t SSDsetXYstates,SSDsetXYWritestates;
	uint8_t Reval=2;
	switch (SSDsetXYstates)
	{
		case 0:
		//uart_string("4\n");
		if(ssd1306_AsyncStart(0x78)==1)
		{
			SSDsetXYstates=1;
		}
		/* Your code here */
		break;
		case 1:
           switch (SSDsetXYWritestates)
           {
	           case 0:
			   if(ssd1306_AsyncWrite(0x00)==1)
			   {
				   SSDsetXYWritestates=1;
			   }
	           /* Your code here */
	           break;
	           case 1:
	           if(ssd1306_AsyncWrite(0xb0 + y)==1)
	           {
				   
		           SSDsetXYWritestates=2;
	           }
	           /* Your code here */
	           break;
	           case 2:
	           if(ssd1306_AsyncWrite((x & 0x0f))==1)
	           {
		           SSDsetXYWritestates=3;
	           }
	           /* Your code here */
	           break;
	           case 3:
	           if(ssd1306_AsyncWrite(((x & 0xf0) >> 4) | 0x10)==1)
	           {
		           SSDsetXYWritestates=0;
				   SSDsetXYstates=2;
	           }
	           /* Your code here */
	           break;
	           default:
	           /* Your code here */
	           break;
           }
		/* Your code here */
		break;
		case 2:
		i2c_stop();
		SSDsetXYstates=0;
		Reval=1;
		/* Your code here */
		break;
		default:
		/* Your code here */
		break;
	}
	
	return Reval;
}

uint8_t SSDWritechar_font6x8(char ch)
{
   	static uint8_t SSDWritecharstates,Tablepointer;
   	uint8_t Reval=2;
	   uint8_t fc;
   	switch (SSDWritecharstates)
   	{
	   	case 0:
	   	if(ssd1306_AsyncStart(0x78|0x00)==1)
	   	{
		   	SSDWritecharstates=1;
	   	}
	   	/* Your code here */
	   	break;
	   	case 1:
		fc=ssd1306_AsyncWrite(0x40);
		if(fc==1)
		{
			SSDWritecharstates=2;
		}
		else if(fc==0)
		{
			SSDWritecharstates=0;
		}
		break;
		case 2:
		if(ssd1306_AsyncWrite(SSDGetByte(ch,Tablepointer))==1)
		{
			Tablepointer++;
			if(Tablepointer==6)
			{
				SSDWritecharstates=3;
				Tablepointer=0;
			}
		}
		break;
		case 3:
	   	i2c_stop();
	   	SSDWritecharstates=0;
	   	Reval=1;
	   	/* Your code here */
	   	break;
	   	default:
	   	/* Your code here */
	   	break;
   	}
   	
   	return Reval;

}


uint8_t testfuc(void * data)
{
   char buffer[25];
   uint16_t address=0;
   
   if(ssdpos<24)
   {

	//strcpy_P(buffer,(PGM_P)pgm_read_word(Frame1+ssdpos));  
	 //&Frame1[ssdpos];//pgm_read_word(&Frames[1]);
	 address=(pgm_read_word(&Frames[FramePos])+(ssdpos*2));
	 strcpy_P(buffer,(PGM_P)pgm_read_word(address));
	 PopulateSSDbuffer(buffer,ssdposy,ssdposx);
	 
	 ssdposx++;
	 ssdpos++;
   }

  if(ssdpos==8||ssdpos==16)
  {
	  ssdposy=ssdposy+60;
	  ssdposx=0;
	 // ssdpos=0;
  }
  Unknown++;
	return 0;
}

uint8_t SSDSetFramePos(uint8_t Pos)
{
	FramePos=Pos;
	ssdpos=0;
    ssdposy=1;
    ssdposx=0;
	return 0;
}
/*uint8_t SSDBlankCodset(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
{
	if(ErasePoints[4]==0)
	{
	  	ErasePoints[0]=x1;
	  	ErasePoints[1]=y1;
	  	ErasePoints[2]=x2;
	  	ErasePoints[3]=y2;
		ErasePoints[4]=1;	
		return 1;
	}
    else
	{
		return 0;
	}
	
}*/