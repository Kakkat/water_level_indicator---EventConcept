/*
 * CFile1.c
 *
 * Created: 4/13/2017 6:57:24 PM
 *  Author: Nikhil
 */ 
#include <avr/io.h>
void Rte_Base2AswLAYERADCReadConnector(uint16_t *DATA)
{
	RTE_BaseWriteCh1Data(DATA);
}

void Rte_Base2AswLayerPingEchoConnector(uint16_t *DATA)
{
	Rte_BaseWritePingEchoData(DATA);
}

Rte_Base2AswLayerUartWriteBuffer(unsigned char *ustring)
{
	Rte_BaseWriteUartData(ustring);
}