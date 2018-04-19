/*
 * Events.c
 *
 * Created: 12/1/2017 10:02:45 PM
 *  Author: Nikhil
 */ 
#include "Events.h"
#include <avr/interrupt.h>
struct Events_t *Head=0;
struct Events_t *Prvious=0;
struct Events_t CurrentEvent; 
struct Events_t *Links;
uint8_t dumy=48;
void AddEvent(uint8_t *Ptr, Nvm_Id id,uint8_t Rorw)
{
	static uint8_t nvmcount;
	if (Head==0)
	{
		Head=(struct Events_t *)malloc(sizeof(struct Events_t));
		Head->ptr=Ptr;
		Head->TaskId=Rorw;	
		Head->next=0;
		Head->EEid=id;
		Prvious=Head;
		eventount++	;
		//uart_num(eventount);
	}
	else
	{
	  Links=(struct Events_t *)malloc(sizeof(struct Events_t));
	  Links->ptr=Ptr;
	  Links->TaskId=Rorw;
	  Links->next=0;
	  Links->EEid=id;
	  Prvious->next=Links;
	  Prvious=Links;
	  eventount++;
	  //uart_num(eventount);
	}
	nvmcount=nvmcount+1;
}

void PrintEvents()
{
	struct Events_t *Links1=Head;
	while(Links1!=0)
	{
		uart_num(Links1->ptr[0]);//
		Links1=Links1->next;
	}
	
}
struct Events_t * TakeAnEvent()
{ 
  if(Head!=0)
  {
	struct Events_t *Links=Head;
	CurrentEvent.ptr=Head->ptr;
	CurrentEvent.TaskId=Head->TaskId;
	CurrentEvent.EEid=Head->EEid;
	free(Head);
	Head=Links->next;
	eventount--;
	//uart_num(eventount);
	return (&CurrentEvent);
	
    
  }
  

return 0;
}

uint8_t checkNvm(Nvm_Id id)
{
  	struct Events_t *Links2=Head;
  	if(Links2!=0)
	{
  	while(Links2!=0)
  	{

	  if(id==Links2->EEid)
	{
	  return 1;
	}
	  	Links2=Links2->next;
     
  	}
	  return 0;
    }
	else
	{
	  return 0;	
	}
}

uint8_t checkEvent()
{
	if(Head==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

struct Events_t * GetCurrentEvent()
{
	return (&CurrentEvent);
}