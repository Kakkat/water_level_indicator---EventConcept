/*
 * Rte_ASW.c
 *
 * Created: 3/31/2017 5:35:58 PM
 *  Author: Nikhil
 */ 


#ifndef RTE_ASW_H_
#define RTE_ASW_H_
#include <avr/io.h>
extern void RTEModuleFirstCh(uint16_t *ChannelValue)
{
    Rte_Base2AswLAYERADCReadConnector(ChannelValue)	;
}
void RTE_ModuleReadPulse(uint16_t *PulseValue)
{
	Rte_Base2AswLayerPingEchoConnector(PulseValue);	
}
/*static Rte_recievebuffer Rte_recievebuffer0;

void Rte_Esp_ReadBuffer(const unsigned char *ustring)
{
	ustring=Rte_recievebuffer0.ustring;
}

void Rte_Uart_WriteBuffer(const unsigned char *ustring)
{
	Rte_recievebuffer0.ustring=ustring;
}*/
void Rte_Uart_WriteBuffer(unsigned char *ustring)
{
	Rte_Base2AswLayerUartWriteBuffer(ustring);	
}

#endif /* RTE_ASW_H_ */