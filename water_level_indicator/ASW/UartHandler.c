/*
 * UartHandler.c
 *
 * Created: 4/1/2017 4:04:44 AM
 *  Author: Nikhil
 */ 
#include "UartHandler.h"

void(*PrintOut)(const unsigned char*)=uart_string;
void UartHandlerMain()
{
	UartOutBuffer buff;
	static uint8_t FLAG=0;
	Rte_Uart_ReadIn_StringOUTBuffer(&buff);
	
		PrintOut(buff.Ustring);
		Rte_Uart_WriteBufferState(4);


	
}


void UartHandlerInit()
{
	
	//PrintOut=uart_string;
}