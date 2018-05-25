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
/*------------------FRAME1-------------------------*/
const char F1ROW1[] PROGMEM ="        WLC          ";
//                           "                     ";
const char F1ROW3[] PROGMEM ="Tank Level :         ";
//                           "                     ";
//                           "                     ";
//                           "                     ";
//                           "                     ";
const char F1ROW8[] PROGMEM ="        MENU         ";

/*------------------FRAME2-------------------------*/
const char F2ROW1[] PROGMEM ="        MENU         ";
//                           "                     ";
const char F2ROW3[] PROGMEM ="1.Mode               ";
const char F2ROW4[] PROGMEM ="2.Settings           ";
const char F2ROW5[] PROGMEM ="3.Diag               ";
//                           "                     ";
//                           "                     ";
const char F2ROW8[] PROGMEM ="        BACK         ";

/*------------------FRAME3-------------------------*/
const char F3ROW1[] PROGMEM ="        Mode         ";
//                           "                     ";
const char F3ROW3[] PROGMEM ="1.Manual             ";
const char F3ROW4[] PROGMEM ="2.Auto               ";
const char F3ROW5[] PROGMEM ="3.Semi               ";
//                           "                     ";
//                           "                     ";
const char F3ROW8[] PROGMEM ="        BACK         ";

/*------------------FRAME4-------------------------*/
const char F4ROW1[] PROGMEM ="        Motor        ";
//                           "                     ";
const char F4ROW3[] PROGMEM ="1.Tank size          ";
const char F4ROW4[] PROGMEM ="2.Top level          ";
//                           "                     ";
//                           "                     ";
//                           "                     ";
const char F4ROW8[] PROGMEM ="        BACK         ";

/*------------------FRAME5-------------------------*/
const char F5ROW1[] PROGMEM ="        Daig         ";
//                           "                     ";
const char F5ROW3[] PROGMEM ="1.Opr Hr             ";
const char F5ROW4[] PROGMEM ="2.Full Tank Cnt      ";
//                           "                     ";
//                           "                     ";
//                           "                     ";
const char F5ROW8[] PROGMEM ="        BACK         ";


const uint16_t Frame1[] PROGMEM= {
	F1ROW1,
	FrameBlank,
	F1ROW3,
	FrameBlank,
	FrameBlank,
	FrameBlank,
	FrameBlank,
	F1ROW8,
};
const uint16_t Frame2[] PROGMEM= {
	F2ROW1,
	FrameBlank,
	F2ROW3,
	F2ROW4,
	F2ROW5,
	FrameBlank,
	FrameBlank,
	F2ROW8,
};
const uint16_t Frame3[] PROGMEM= {
	F3ROW1,
	FrameBlank,
	F3ROW3,
	F3ROW4,
	F3ROW5,
	FrameBlank,
	FrameBlank,
	F3ROW8,
};
const uint16_t Frame4[] PROGMEM= {
	F4ROW1,
	FrameBlank,
	F4ROW3,
	F4ROW4,
	FrameBlank,
	FrameBlank,
	FrameBlank,
	F4ROW8,
};
const uint16_t Frame5[] PROGMEM= {
	F5ROW1,
	FrameBlank,
	F5ROW3,
	F5ROW4,
	FrameBlank,
	FrameBlank,
	FrameBlank,
	F5ROW8,
};


const uint16_t Frames[] PROGMEM=
{
	&Frame1,
	&Frame2,
	&Frame3,
	&Frame4,
	&Frame5,
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
   
   if(ssdpos<8)
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

uint8_t SSDfullLitup()
{
	return 0;
}
