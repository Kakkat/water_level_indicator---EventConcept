/*
 * Events.h
 *
 * Created: 12/1/2017 10:03:00 PM
 *  Author: Nikhil
 */ 
#include <avr/io.h>
#include "..\MddleLayer\EepromStructure.h"
#ifndef EVENTS_H_
#define EVENTS_H_
volatile uint8_t eventount;
 struct Events_t 
{   
   uint8_t TaskId;
   Nvm_Id  EEid; 
   uint8_t *ptr;
   struct Events_t *next;   	
};

void AddEvent(uint8_t *Ptr, Nvm_Id id,uint8_t Rorw);
void PrintEvents();
uint8_t checkNvm(Nvm_Id id);
struct Events_t * TakeAnEvent();
uint8_t checkEvent();
struct Events_t * GetCurrentEvent();
#endif /* EVENTS_H_ */