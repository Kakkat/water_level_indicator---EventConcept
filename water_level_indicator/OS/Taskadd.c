/*
 * Taskadd.c
 *
 * Created: 8/8/2016 9:57:20 PM
 *  Author: neethu
 */ 
#include "Task.h"
#include "..\os\Taskadd.h"
#include "..\os\OSRR.h"
#include "..\ASW\UartHandler.h"
#include "..\ASW\ESP8266.h"
#include "..\MddleLayer\ADCread.h"
#include "..\MddleLayer\UartTransmit.h"
#include "..\MddleLayer\BaseTask.h"
#include "..\MddleLayer\SignalHandler.h"
struct Events_t *ProcessEvent;
static uint16_t  EventState =2;
uint16_t BaseHandler(void *ptr);
task taskfunc[8] = {{task1,task1Open,dTask1Time,dOFF,0},
	               {task2,task2Open,dTask2Time,dON,0},
				   {task3,task3Open,dTask3Time,dON,0},
				   {task4,task4Open,dTask4Time,dON,0},
				   {task5,task5Open,dTask5Time,dON,0},
				   {TaskFrames,task2Open,dTask5Time,dON,0},
				   {TransmitBufferEmpty,TransmitBufferEmpty,dTask1Time,dOFF,0},
				   {tasksBase,tasksBase,dTask1Time,dON,0}};
					   
task taskfuncbase[3] = {{BaseTask1,BaseTask1Open,1,dOFF,0},
	                    {BaseTask2,BaseTask2Open,1,dOFF,0},
						{Testtask,BaseTask2Open,1,dON,0}};	
NonPeriodictask NonPeriodictaskArr[5]={0};			   
EventList EventFunc[1]={{0,NVMTask}};

static uint8_t openDone;
uint16_t tasks( )
{
	static uint8_t opentask=0;
	if(opentask==0)
	{
		callbackSetFunction(1,BaseHandler);
		callbackSetFunction(3,NonPeriodicTaskFuncSet);
		Nvm_TableInit();
		for(int i=0;i<eTaskEndoflist;i++)
		{
			if(taskfunc[i].On==dON)
			{
				
				taskfunc[i].Openfucntion();
			}
		}
		opentask=1;
		openDone=1;
		UartHandlerInit();
		
	}
	
	for(int i=0;i<eTaskEndoflist;i++)
	{
		taskfunc[i].counter++;
		if(taskfunc[i].On==dON && taskfunc[i].counter>=taskfunc[i].time )
		{
			taskfunc[i].taskfucntion();
			taskfunc[i].counter=0;
			
			//UartHandlerMain();
		}
	}
    ReadEveryValueADC();
	
	return 0;
}
uint16_t tasksBase()
{
	static uint8_t opentaskbase=0;
	if(opentaskbase==0)
	{
		for(int i=0;i<3;i++)
		{
			if(taskfuncbase[i].On==dON)
			{
				
				taskfuncbase[i].Openfucntion();
			}
		}
		opentaskbase=1;
		
	}
	
	for(int i=0;i<3;i++)
	{
		taskfuncbase[i].counter++;
		if(taskfuncbase[i].On==dON && taskfuncbase[i].counter>=taskfuncbase[i].time )
		{
			uint16_t Temp;
			uint8_t arr[3];
			Temp=taskfuncbase[i].taskfucntion();
			//uart_num((((uint8_t*)&Temp)[1]&0x01));
			if((((uint8_t*)&Temp)[1]&0x01)==0)
			{
				//uart_string("done");
				arr[0]=1;
				arr[1]=(((uint8_t*)&Temp)[1]>>1)&0x7f;
				arr[2]=((uint8_t*)&Temp)[0];
				callbackarrayfuc func;
				func=callbackgetFunction(2);
				func(arr);
				taskfuncbase[i].On=0;
			}
			taskfuncbase[i].counter=0;
			//uart_string("base");
			//UartHandlerMain();
		}
	}
	
	return 0;
}
uint16_t NonPeriodicTaskFuncCall( )
{
	    static uint16_t tasktime;
		for(int i=0;i<5;i++)
		{
			tasktime++;
			if(NonPeriodictaskArr[i].On==dON&&tasktime>900  )
			{
				NonPeriodictaskArr[i].taskfucntion(NonPeriodictaskArr[i].ptr);	
				tasktime=0;			
			}
		}
		return 0;
}
uint16_t NonPeriodicTaskFuncSet(void *ptr)
{
	uint8_t *data;
	uint8_t funcpoint[2];
	data=(uint8_t*)ptr;
	NonPeriodictaskArr[data[0]].taskfucntion=(funPtrBase*)(((uint16_t*)(data+2))[0]);
	NonPeriodictaskArr[data[0]].On=data[1];
	NonPeriodictaskArr[data[0]].ptr=ptr;	
}
uint16_t BaseHandler(void *ptr)
{
	uint8_t *data;
	data=(uint8_t*)ptr;
    taskfuncbase[*data-1].On=1;
	//uart_string("bhandler\n");
}
void CallEvents()
{
if(eventount!=0)
{
	
	static uint8_t currenteventstate;
	if(EventState==2)
	{
		
		if(checkEvent()==0)
		{
		
		ProcessEvent=TakeAnEvent();
        //uart_string("here");
		EventState=0;			
		}

	}
 else  if(EventState==0||EventState==1 &&ProcessEvent!=0)
	{
		//if(ProcessEvent!=0)
		///{
			//currenteventstate=EventFunc[ProcessEvent->TaskId].taskfucntion();
		//}
		
		//while(currenteventstate==0 &&checkEvent()==0)
		//{
		  //ProcessEvent=TakeAnEvent();
		  //if(ProcessEvent!=0)
		  ///{
			  
			 currenteventstate=EventFunc[0].taskfucntion();	 
		  //}
		  
		  //uart_num(1);
		///}	
		if(currenteventstate!=0)
		{
			EventState=1;
		}
		else 
		{
			EventState=2;
		}
    }
	}
}
void ApplicationHookUP(uint8_t * event)
{
	SSDtask();
	if(openDone==1)
	{
		HookupTasks(event);
		//DataTransmit();
	}
	if(UartEvents==1)
	{
		taskfunc[5].On=1;
	}
	
}