/*
 * EventQ.c
 *
 * Created: 3/13/2018 6:05:54 PM
 *  Author: Nikhil
 */ 
#include "EventQ.h"
#include "..\BaseLayer\UART.h"
#include <avr/interrupt.h>
#define  circularbuffevent(x,y) \
volatile  struct EventQ eQ[y];   \
volatile ebuff_t x={                \
	eQ,                    \
	0,                     \
	0,                     \
	y                      \
};                          \

static uint8_t count = 0;
static volatile struct EventQ *front,*rear,*temp,*front1;
circularbuffevent(CircularBufferEvent,15);
//
/* Create an empty queue */
void create()
{
front = rear = NULL;
}

/* Returns queue size */
void queuesize()
{
//printf("\n Queue size : %d", count);
}

/* Enqueing the queue */
void enq(struct EventQ data)
{

		
if(count<5)
{
	

if (rear == NULL)
{
rear = (struct EventQ *)malloc(1*sizeof(struct EventQ));
//rear =eQ;
rear->ptr = NULL;
rear->EventId = data.EventId;
//uart_string("en1");
rear->EventFunction=data.EventFunction;
front = rear;
}
else
{
temp=(struct EventQ *)malloc(1*sizeof(struct EventQ));
//temp=eQ+count;
rear->ptr = temp;
temp->EventId = data.EventId;
//uart_string("en2");
rear->EventFunction=data.EventFunction;
temp->ptr = NULL;

rear = temp;
}
count++;
	
}
}
/* Displaying the queue elements */
void display()
{
front1 = front;

if ((front1 == NULL) && (rear == NULL))
{
//printf("Queue is empty");
return;
}
while (front1 != rear)
{
//printf("%d ", front1->info);
front1 = front1->ptr;
}
if (front1 == rear)
{
	
	
}
//printf("%d", front1->info);
}

/* Dequeing the queue */
struct EventQ  deq(void)
{
struct EventQ Carrier={0};

front1 = front;
//uart_num(front->EventId);
if (front == NULL)
{
////printf("\n Error: Trying to display elements from empty queue");
//uart_string("1");
//return Carrier;
}
else
if (front1->ptr != NULL)
{
front1 = front1->ptr;
//uart_string("here2start\n");
Carrier.EventId=front->EventId;
Carrier.EventFunction=front->EventFunction;
//uart_string("here2\n");
free(front);
front = front1;
}
else
{
//uart_string("here3\n");
Carrier.EventId=front->EventId;
Carrier.EventFunction=front->EventFunction;
//uart_num(Carrier.EventId);
free(front);
front = NULL;
front1 = NULL;
rear=NULL;
//return Carrier;
}

if(count>0)
{
	//uart_string("\ninsidecount:");
	//uart_num(count);
	//uart_string("\sub:");
	count--;
	//uart_num(eQ[0].EventId);
}

return Carrier;
}

/* Returns the front element of queue */
int frontelement()
{
if ((front != NULL) && (rear != NULL))
return(front->EventId);
else
return ;
}

/* Display if queue is empty or not */
void empty()
{
if ((front == NULL) && (rear == NULL))
{
	
}
//printf("\n Queue empty");
else
{
	
	
}
//printf("Queue not empty");
}

uint8_t countSize()
{
	return count;
}

ebuffState_t PushIntoCircularEventBuffer(ebuff_t* CircularBuffer,struct EventQ data)
{
	uint8_t next=CircularBuffer->head+1;
	ebuffState_t ReturnVal=eBuffStateEndOfList;
	if(next>=CircularBuffer->MaxLen)
	{
		next=0;
	}
	
	if(next==CircularBuffer->tail)
	{
		return eBuffFull;
	}
	
	else
	{
		
		CircularBuffer->buffer[CircularBuffer->head]=data;
		CircularBuffer->head=next;
		ReturnVal=eBuffOk;
	}
	return ReturnVal;
}

ebuffState_t PopFromCircularEventBuffer(ebuff_t  *CircularBuffer,struct EventQ *data)
{
	//cli();
	uint8_t next=CircularBuffer->tail+1;
	if(CircularBuffer->tail==CircularBuffer->head)
	{
		return eBuffEmpty;
	}
	else if(next>=CircularBuffer->MaxLen)
	{
		next=0;
	}
	
	*data=CircularBuffer->buffer[CircularBuffer->tail];
	CircularBuffer->tail=next;
	//sei();
	return eBuffOk;
}

ebuffState_t IsEventBuffempty(ebuff_t  *CircularBuffer)
{
	if(CircularBuffer->tail==CircularBuffer->head)
	{
		return eBuffEmpty;
	}
	return eBuffOk;
}


void PushEventInterface(uint8_t eventid,uint16_t  (*EventFuncarg)(void),void *func,uint8_t dataid)
{
	cli();
	struct EventQ data;
	data.EventFunction=EventFuncarg;
	data.EventId=eventid;
	data.ptr=func;
	data.State=dataid;
	PushIntoCircularEventBuffer(&CircularBufferEvent,data);
	sei();
}

ebuffState_t PopEventInterface(struct EventQ *e)
{
    struct EventQ data;
	if(PopFromCircularEventBuffer(&CircularBufferEvent,&data)==eBuffOk)
	{
		*e=data;
		return eBuffOk;
	}
	return eBuffEmpty;
}