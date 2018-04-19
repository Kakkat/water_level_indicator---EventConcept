/*
 * Taskadd.h
 *
 * Created: 8/8/2016 9:57:51 PM
 *  Author: neethu
 */ 

#include "../MddleLayer/NVM_Handler.h"
#ifndef TASKADD_H_
#define TASKADD_H_
#define dTask1Time 5
#define dTask2Time 1
#define dTask3Time 5
#define dTask4Time 5
#define dTask5Time 5
#define dON 1
#define dOFF 0
struct task
{// int value;
	uint16_t  (*taskfucntion)(void);
	uint16_t  (*Openfucntion)(void);
	uint8_t time;
	uint8_t    On;
	uint8_t counter;
};
struct NonPeriodictask
{// int value;
	uint16_t  (*taskfucntion)(void *);
	uint8_t    On;
	void * ptr;
};
struct EventList
{// int value;
	uint8_t taskid;
	uint16_t  (*taskfucntion)(void);
};
typedef struct EventList EventList;
typedef struct task task;
typedef struct NonPeriodictask NonPeriodictask;
typedef uint16_t  (*funPtrBase)(void);
enum eTask
{
 eTask1,
 eTask2,
 eTask3,
 eTask4,
 eTask5,
 eTask6,
 eTask7,
 eTaskEndoflist	
};
uint16_t tasks(void);
void ApplicationHookUP(uint8_t *);
uint16_t tasksBase();
uint16_t NonPeriodicTaskFuncCall( );
uint16_t NonPeriodicTaskFuncSet(void *ptr);
#endif /* TASKADD_H_ */