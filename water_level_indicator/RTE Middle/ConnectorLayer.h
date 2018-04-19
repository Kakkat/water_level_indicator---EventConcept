/*
 * IncFile2.h
 *
 * Created: 4/13/2017 6:53:42 PM
 *  Author: Nikhil
 */ 


#ifndef INCFILE2_H_
#define INCFILE2_H_

#define Rte_Base2AswADCReadConnector Rte_Base2AswLAYERADCReadConnector

#define Rte_Base2AswPingEchoConnector Rte_Base2AswLayerPingEchoConnector

#define Rte_Base2AswUartWriteBuffer Rte_Base2AswLayerUartWriteBuffer

extern void Rte_Base2AswLAYERADCReadConnector(uint16_t *);

extern void Rte_Base2AswLayerPingEchoConnector(uint16_t *);

extern void Rte_Base2AswLayerUartWriteBuffer(unsigned char *ustring);

#endif /* INCFILE2_H_ */