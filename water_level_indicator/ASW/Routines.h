/*
 * Routines.h
 *
 * Created: 12/12/2017 6:59:44 PM
 *  Author: Nikhil
 */ 


#ifndef ROUTINES_H_
#define ROUTINES_H_
#include "..\MddleLayer\NVM_Handler.h"
typedef struct  
{
	uint8_t IdoutineId;
	Nvm_Id  RoutineNvmId;
}Routines_t;
void DebugMode();
#endif /* ROUTINES_H_ */