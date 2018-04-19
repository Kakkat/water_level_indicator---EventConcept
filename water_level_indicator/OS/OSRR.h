/*
 * OSRR.h
 *
 * Created: 3/13/2018 8:26:54 PM
 *  Author: Nikhil
 */ 


#ifndef OSRR_H_
#define OSRR_H_
#include "Taskadd.h"
#include "EventQ.h"

void OSRR_Events();
typedef void (*callbackarrayfuc) (uint16_t  (*callbackarg)(void ));
void callbackSetFunction(uint8_t,callbackarrayfuc);
callbackarrayfuc callbackgetFunction(uint8_t);
#endif /* OSRR_H_ */