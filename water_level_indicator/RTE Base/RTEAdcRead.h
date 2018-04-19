/*
 * RTEAdcRead.h
 *
 * Created: 4/13/2017 6:23:25 PM
 *  Author: Nikhil
 */ 


#ifndef RTEADCREAD_H_
#define RTEADCREAD_H_
#include <avr/io.h>
#define RTEReadFirstCh RTEModuleFirstCh
#define RTE_ReadPulse	RTE_ModuleReadPulse
#define RTE_WriteBufferUart Rte_Uart_WriteBuffer
extern void RTEModuleFirstCh(uint16_t *);
extern void RTE_ModuleReadPulse(uint16_t *);
extern void Rte_Uart_WriteBuffer(unsigned char *ustring);
#endif /* RTEADCREAD_H_ */