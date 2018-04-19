/*
 * OSRR.c
 *
 * Created: 3/13/2018 8:26:33 PM
 *  Author: Nikhil
 */ 
#include "OSRR.h"
callbackarrayfuc callbackarray[10];
void callbackSetFunction(uint8_t pos,callbackarrayfuc arg)
{
	callbackarray[pos]=arg;
}
callbackarrayfuc callbackgetFunction(uint8_t pos)
{
	return callbackarray[pos];
}
void OSRR_Events()
{
  struct EventQ e;
  

  e=deq();
  
  if(e.EventId!=0)
  {
	//uart_string("taking\n");
	//uart_num(e.EventId);
	e.EventFunction(0);
	//
  }
  
}