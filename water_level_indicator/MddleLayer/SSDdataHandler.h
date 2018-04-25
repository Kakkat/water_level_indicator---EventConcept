/*
 * SSDdataHandler.h
 *
 * Created: 4/20/2018 2:12:14 PM
 *  Author: U338583
 */ 


#ifndef SSDDATAHANDLER_H_
#define SSDDATAHANDLER_H_
#include "..\BaseLayer\CircularQueue.h"
typedef struct
{
	unsigned char SSDchar;
	uint8_t SSDx;
	uint8_t SSDy;
}SSDdata;

typedef struct
{
	SSDdata *buffer;
	uint8_t head;
	uint8_t tail;
	uint8_t MaxLen;
}SSDbuff_t;



CbuffState_t PushIntoSSDCircularBuffer(SSDbuff_t* CircularBuffer,SSDdata data);
CbuffState_t PopFromSSDCircularBuffer(SSDbuff_t  *CircularBuffer,SSDdata *data);
CbuffState_t IsSSDBuffempty(SSDbuff_t  *CircularBuffer);
uint8_t PopulateSSDbuffer(unsigned char* SSDstring,uint8_t x,uint8_t y);
CbuffState_t PopSSDinterface(SSDdata *SSDdataPara);
uint8_t PopulateSSDbufferChar(unsigned char SSDChar,uint8_t x,uint8_t y);
uint8_t SSDHeadTailDiff(SSDbuff_t  *CircularBuffer);

#endif /* SSDDATAHANDLER_H_ */