/*
 * Rte_Uart.c
 *
 * Created: 3/31/2017 6:07:06 PM
 *  Author: Nikhil
 */ 

#ifndef RTE_UART_H_
#define RTE_UART_H_

#include "Rte_Uart.h"
#include "..\RTE ASW\Rte_ASW.h"
static Rte_recievebuffer Rte_recievebuffer0={0};





void Rte_Uart_ReadBuffer(UartBuffer *Ubuff)
{
	UartBuffer *buff;
	buff=Rte_recievebuffer0.uBuffer;
	Ubuff->Ustring=buff->Ustring;
	Ubuff->pos=buff->pos;
}

Cmd_State Rte_Uart_WriteOUT_StringOUTBuffer(const unsigned char *OutBuff )
{
	Cmd_State Buffstate=AL_CmdOk;
	uart_string(OutBuff);
	/*if(buff.State==4)
	{
		Buffstate=AL_CmdOk;
		
	}
	buff.Ustring=OutBuff->Ustring;
	buff.State=OutBuff->State;
	//buff=1;	*/


	return Buffstate;
}

void Rte_Uart_ReadIn_StringOUTBuffer(UartOutBuffer *OutBuff)
{

	 
	 
}

void Rte_Uart_WriteBufferState(uint8_t state)
{
	
}
#endif /* RTE_UART_H_ */