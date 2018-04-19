/*
 * DebugHandler.h
 *
 * Created: 3/26/2018 4:17:10 PM
 *  Author: Nikhil
 */ 


#ifndef DEBUGHANDLER_H_
#define DEBUGHANDLER_H_


uint16_t DebugHandlerFunc(void *fptr);
uint16_t ReadRambyte(void *Ptr);
uint16_t WriteRambyte(void *Ptr);
uint16_t ReadRambytesNonCnt(void *Ptr);

typedef struct
{
	uint16_t VariableAdd;
	uint8_t  VariableId;
	uint8_t  VariableSize;
}VariableManager;
uint8_t OutPutVariableRegister(uint16_t Outadd,uint8_t Varsize,uint8_t Varid);
#endif /* DEBUGHANDLER_H_ */