/*
 * Rte_Uart.h
 *
 * Created: 3/31/2017 5:31:26 PM
 *  Author: Nikhil
 */ 


#ifndef RTE_UART_H_
#define RTE_UART_H_


#include "..\RTE Middle\Rte_types.h"
#include "..\ASW\UartHandler.h"
//void Rte_Uart_WriteBuffer(UartBuffer *Ubuff);
void Rte_Uart_ReadBuffer(UartBuffer *Ubuff);
Cmd_State Rte_Uart_WriteOUT_StringOUTBuffer(const unsigned char *);
void Rte_Uart_ReadIn_StringOUTBuffer(UartOutBuffer *);
void Rte_Uart_WriteBufferState(uint8_t state);
extern void(*PrintOut)(const unsigned char*);
#endif /* RTE_UART_H_ */ 