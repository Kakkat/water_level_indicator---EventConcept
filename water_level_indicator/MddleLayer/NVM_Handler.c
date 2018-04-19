/*
 * NVM_Handler.c
 *
 * Created: 12/2/2017 12:38:57 PM
 *  Author: Nikhil
 */ 
#include "NVM_Handler.h"
static uint8_t NVMStatex;
//struct Events_t *NVMEvent;
static uint8_t NVMDataArray[8];
static uint8_t NVMProcess;
uint16_t TEMP;
void StoreNVM(Nvm_Id ID, void * ptr,uint8_t ReadorWrite)
{

if(NVMProcess==0)
 {
   TEMP=NVMTask;
   NVMDataArray[0]=2;
   NVMDataArray[1]=1;
   NVMDataArray[2]=((uint8_t*)(&TEMP))[0];
   NVMDataArray[3]=((uint8_t*)(&TEMP))[1];
   TEMP=ptr;
   //uart_num(((uint8_t *)TEMP)[0]);
   //uart_num(((uint8_t *)TEMP)[1]);
   NVMDataArray[4]=((uint8_t*)(&TEMP))[0];
   NVMDataArray[5]=((uint8_t*)(&TEMP))[1];
   NVMDataArray[6]=ID;
   NVMDataArray[7]=ReadorWrite;
   PushEventInterface(52,1,NVMDataArray,0);	
 }
}
static uint32_t NVMdat=200; 
uint16_t NVMTask(void *NvmData)
{
	//uart_string("in nvm");
	uint8_t state;
	uint8_t *NVMDataPtr;
	NVMDataPtr=(uint8_t *)NvmData;
	state=GetNVMState();
	//uart_num(state);
	NVMdat++;
	if(state==2 && NVMProcess==0)
	{
	     //CurrentEvent()->EEid
		//uart_string("IN nvm task");
		NvmPopulateWriteSize(Nvm_Table_t[NVMDataPtr[6]].Nvm_Size,Nvm_Table_t[NVMDataPtr[6]].Id,NVMDataPtr[7],(uint8_t *)TEMP);
		//uart_num(((uint8_t *)((uint16_t*) NVMDataPtr[4])[0])[0]);
		SwitchNvmOn();
		NVMProcess=1;
	    return 1;
	}
	else if(state==2 && NVMProcess==1)
	{
	    NVMDataArray[1]=0;
	    PushEventInterface(52,1,NVMDataArray,0);	
		//uart_string("IN nvm task END");
        NVMProcess=0;
	    return 0;
	}
	
}


uint8_t NvmReadSync(Nvm_Id ID, void * ptr)
{
	static uint8_t WriteState;
	uint8_t restate=1;
    NvmPopulateWriteSize(Nvm_Table_t[ID].Nvm_Size,Nvm_Table_t[ID].Id,1,ptr);
	uart_num((Nvm_Table_t[ID].Id+Nvm_Table_t[ID].Nvm_Size));	
	uart_string("done\n");
	SwitchNvmOn();	
	while(GetNVMState()==0)		
	WriteState=1;
	restate=0;
	return restate;
}