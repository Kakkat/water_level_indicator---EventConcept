/*
 * Rte_ASW.h
 *
 * Created: 3/31/2017 5:39:55 PM
 *  Author: Nikhil
 */ 


#ifndef RTE_ASW_H_
#define RTE_ASW_H_
#include "..\RTE Middle\Rte_types.h"
#include "..\RTE Base\RTEAdcRead.h"
#include "..\RTE Middle\ConnectorLayer.h"
#include "..\BaseLayer\UART.h"
typedef struct
{
  UartBuffer *uBuffer;
}Rte_recievebuffer;




#endif /* RTE_ASW_H_ */