/*
 * NVM.h
 *
 * Created: 10/18/2017 6:16:43 PM
 *  Author: Nikhil
 */ 


#ifndef NVM_H_
#define NVM_H_
uint8_t GetNVMState();
void SwitchNvmOn();
void NvmPopulateWriteSize(uint8_t size,uint8_t startadd,uint8_t WriteorRead,uint8_t *ptr);


#endif /* NVM_H_ */