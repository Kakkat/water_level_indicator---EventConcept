/*
 * UartTransmit.h
 *
 * Created: 10/15/2017 3:14:55 PM
 *  Author: Nikhil
 */ 


#ifndef UARTTRANSMIT_H_
#define UARTTRANSMIT_H_


void DataTransmit();
void FillUartBuffer(unsigned char *);
void TransmitBufferEmpty();
void FillUartBufferSiglechar(char Uchar);

#endif /* UARTTRANSMIT_H_ */