/*
 * EventQ.h
 *
 * Created: 3/13/2018 6:06:19 PM
 *  Author: Nikhil
 */ 


#ifndef EVENTQ_H_
#define EVENTQ_H_
#define NULL 0
#include <avr/io.h>

struct EventQ
{// int value;
	uint16_t  (*EventFunction)(void *);
	uint8_t State;
	uint8_t EventId;
	void *ptr;
};

int frontelement();
void enq(struct EventQ);
struct EventQ  deq(void);
void empty();
void display();
uint8_t countSize();
void create();
void queuesize();

typedef enum
{
	eBuffOk,
	eBuffEmpty,
	eBuffFull,
	eBuffStateEndOfList
}ebuffState_t;

typedef struct
{
	struct EventQ *buffer;
	uint8_t head;
	uint8_t tail;
	uint8_t MaxLen;
}ebuff_t;


ebuffState_t PushIntoCircularEventBuffer(ebuff_t*,struct EventQ );
ebuffState_t PopFromCircularEventBuffer(ebuff_t*,struct EventQ *);
ebuffState_t IsEventBuffempty(ebuff_t  *CircularBuffer);
void PushEventInterface(uint8_t eventid,uint16_t  (*EventFuncarg)(void),void *,uint8_t);
ebuffState_t PopEventInterface(struct EventQ *e);
#endif /* EVENTQ_H_ */