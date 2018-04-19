/*
 * NVM_Handler.h
 *
 * Created: 12/2/2017 12:39:12 PM
 *  Author: Nikhil
 */ 


#ifndef NVM_HANDLER_H_
#define NVM_HANDLER_H_
#include <avr/io.h>
#include "EepromStructure.h"
#include "..\OS\EventQ.h"
void StoreNVM(Nvm_Id ID, void * ptr,uint8_t ReadorWrite);
uint16_t NVMTask(void *);
uint8_t NvmReadSync(Nvm_Id ID, void * ptr);

#endif /* NVM_HANDLER_H_ */