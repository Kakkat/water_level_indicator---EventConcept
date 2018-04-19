/*
 * RTE_BSW.c
 *
 * Created: 4/13/2017 6:29:21 PM
 *  Author: Nikhil
 */ 
#include "..\MddleLayer\ADCread.h"
#include "..\BaseLayer\ExtInterrupt.h"
#include "..\MddleLayer\UartTransmit.h"

extern void RTE_BaseWriteCh1Data(uint16_t *ChannelValue)
{
	//uart_num(*ChannelValue);
	//*ChannelValue=2;
	uint16_t val=*ChannelValue;
	*ChannelValue=GetADC_Value(val);
}

void Rte_BaseWritePingEchoData(uint16_t *PingEcho)
{
	uint16_t val=*PingEcho;
	*PingEcho=InterfacePulse(val);
}

void Rte_BaseWriteUartData(unsigned char *Ustring)
{
	FillUartBuffer(Ustring);
}