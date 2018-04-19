/*
 * CircularQueue.h
 *
 * Created: 6/17/2017 6:17:18 PM
 *  Author: Nikhil
 */ 


#ifndef CIRCULARQUEUE_H_
#define CIRCULARQUEUE_H_
#include<avr/io.h>
typedef enum
{
 BuffOk,
 BuffEmpty,
 BuffFull,
 BuffStateEndOfList	
}CbuffState_t;

typedef struct
{
	unsigned char *buffer;
	uint8_t head;
	uint8_t tail;
	uint8_t MaxLen;
}Cbuff_t;


CbuffState_t PushIntoCircularBuffer(Cbuff_t*,unsigned char);
CbuffState_t PopFromCircularBuffer(Cbuff_t*,unsigned char *);
CbuffState_t IsBuffempty(Cbuff_t  *CircularBuffer);
uint8_t HeadTailDiff(Cbuff_t  *CircularBuffer,uint8_t dat);
#endif /* CIRCULARQUEUE_H_ */