/*
 * Task.h
 *
 * Created: 8/6/2016 8:20:45 PM
 *  Author: neethu
 */ 

#include "..\BaseLayer\pinout.h"
#include "..\MddleLayer\ADCread.h"



#ifndef TASK_H_
#define TASK_H_
#include "Events.h"
uint16_t task1(void);
uint16_t task2(void);
uint16_t task3(void);
uint16_t task4(void);
uint16_t task5(void);
uint16_t task6(void *);
uint16_t task1Open(void);
uint16_t task2Open(void);
uint16_t task3Open(void);
uint16_t task4Open(void);
uint16_t task5Open(void);
uint16_t task6Open(void);
void HookupTasks(uint8_t *);
#endif /* TASK_H_ */