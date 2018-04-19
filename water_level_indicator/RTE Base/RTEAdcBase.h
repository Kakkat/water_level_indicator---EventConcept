/*
 * RTEAdcBase.h
 *
 * Created: 4/13/2017 6:33:02 PM
 *  Author: Nikhil
 */ 


#ifndef RTEADCBASE_H_
#define RTEADCBASE_H_

#define Rte_WriteCh1Data RTE_BaseWriteCh1Data
#define Rte_WritePingEchoData Rte_BaseWritePingEchoData
#define  Rte_WriteUartData Rte_BaseWriteUartData
extern void RTE_BaseWriteCh1Data(uint16_t *);
extern void Rte_BaseWritePingEchoData(uint16_t *);
extern void  Rte_BaseWriteUartData(unsigned char *Ustring);
#endif /* RTEADCBASE_H_ */