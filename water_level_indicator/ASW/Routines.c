/*
 * Routines.c
 *
 * Created: 12/12/2017 6:59:24 PM
 *  Author: Nikhil
 */ 

#include <avr/io.h>
#include "..\BaseLayer\UART.h"
#include "..\OS\Events.h"

static char DebugArray[10];
static uint8_t DebugStates;
static uint8_t DebugArrayindex;
static uint8_t populateArray();
static void  DebugBufferCheck();
void DebugMode()
{

   switch(DebugStates)
   {   
	   unsigned char data='&';
	   case 0:
	       PopInterface(&data);
		   if(data=='#')
		   {
			  DebugStates++; 
			  uart_string("IAM0");
		   }
		   break;
	   case 1:
	      if(populateArray()==0)
		  {
			DebugStates++;
		  }
		  break;
	   case 2:
	      DebugBufferCheck();
		  DebugStates=0;
		  DebugArrayindex=0;
		  break;
   }
   
}

static uint8_t populateArray()
{
	unsigned char data='&';
	uint8_t ret=1;
	PopInterface(&data);
	if(DebugArrayindex<10 && data!='&' )
	{
	   DebugArray[DebugArrayindex]=data;
	   DebugArrayindex++;
	   uart_char(data);
	}
	else if(DebugArrayindex==10)
	{
	  ret=0;
	}
	
	return ret;	
}

static void  DebugBufferCheck()
{ 
   static uint8_t debugdat=10;
   switch(DebugArray[0])
   {
	   case '2':
	       if(DebugArray[1]=='E')
		   {
			 //AddEvent((uint8_t *)&DebugArray[3],DebugArray[0]); 
			 //uart_num((uint8_t)(DebugArray[2]-'0'));
			 StoreNVM((uint8_t)(DebugArray[2]-'0'),&DebugArray[2],0);
			 uart_string("IAM");
		   }
		   else if (DebugArray[1]=='2')
		   {
		     StoreNVM((uint8_t)(DebugArray[2]-'0'),&DebugArray[2],1);
		   }
		  break;
	  
		 
   }	
}