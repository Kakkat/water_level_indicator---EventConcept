/*
 * CFile2.c
 *
 * Created: 8/6/2016 8:19:54 PM
 *  Author: neethu
 */ 
#include "Task.h"
#include "EventQ.h"
#include <util/delay.h>
#include "..\BaseLayer\NVM.h"
#include "..\MddleLayer\MaxDisp.h"
#include "..\ASW\StringOp.h"
#include "..\MddleLayer\NVM_Handler.h"
#include "..\MddleLayer\DebugHandler.h"
//#include "ExtInterrupt.h"
#include "..\BaseLayer\Timer2.h"
#include "..\BaseLayer\UART.h"
#include "..\ASW\ESP8266.h"
#include "..\ASW\Routines.h"
#include "..\RTE Base\RTEAdcRead.h"    
//#define TANKCAL (10000/130 )                                                                              ";
static unsigned char str1[] = "off";
static uint8_t SensorValue;
volatile uint8_t signal=0,Sigout,quality=0;
volatile uint16_t TIME=0;
static void FilterUltrasonic(uint8_t Distance);
static void num2CharArray(unsigned char num,unsigned char *Ustring);
static Nvm_T_Ping a,c,f;
static Nvm_T_OH hours;
static uint16_t TankSize;
static uint8_t EspConnected;
typedef uint16_t  (*funPtrDebug)(void *);
//Esp_Index=Mode_Command;
//Site[36]=name;
//background-color:#757575;height;100%;position:absolute;line-height:inherit;width:62%" ><center><span style="color:white">62</span></center></div></body></html>";
uint16_t task1(void)
{

	
	static uint16_t time1=0,time2=0;
	static uint16_t COUNT=0,Upcounter,DownCounter;
	static uint16_t Init_Flag=0;
	static uint8_t Toggle=0,Toggle1=1,ssdcount;
	uint16_t value,one,two,three;
	char SSDNUM[4];
	//PinOutput(0,PIN_OUT1);
	//PORTB=0X00;
	//PinOutput(1,PIN_OUT1,B);
	//PinOutput(1,PIN_OUT2,B);
   //uart_char('a');
  // uart_string(str1);
  uint16_t Out;
  //RTE_WriteBufferUart(str1);
	time1=time1+1;
	if(Init_Flag==0)
	{
		InitMax();
		Init_Flag=1;
		TankSize=10000/124;
	}
	DispChar(0x0d,7);
	if(time1==10)
	{  //ssd1036_chumma();
        
        uint16_t percnt;
		Out=(10000-(SensorValue*TankSize))/100;
		                        percnt=Out;
								SSDNUM[3]='\0';	
								Out=Out*127;
								Out=Out/100;														//ssdcount=one;
								num2CharArray(percnt,SSDNUM);
								ssd1306_String_font6x8(SSDNUM,74,3);
								ssd1306_String_font6x8("'/.",96,3);
		if(SensorValue<20 && Upcounter<40)
		{
		  Upcounter++; 
		  DownCounter=0;
		}
		else if(SensorValue>122 && DownCounter<40 && SensorValue<255)
		{
			Upcounter=0;
			DownCounter++;
		}
        else
		{
			Upcounter=0;
			DownCounter=0;	
			COUNT=0;
			PinOutput(0,PIN_OUT7,D);
		}
		DispDigits(Out);
		//DispDigits(COUNT);
            
			//PinOutput(Toggle,PIN_OUT1,B);
		//
		//COUNT=COUNT+1;
		
		Toggle1=Toggle1^1;

		//
		time1=0;

				   //a=0x0800;
				   //RTEModuleFirstCh(&a);

					//}
				 


	}
    if(Upcounter!=0||DownCounter!=0 )
	{
		
	if (COUNT>100)
	{
		COUNT=0;
		Toggle=Toggle^1;
       PinOutput(Toggle,PIN_OUT7,D);
	}
	COUNT++;
	}
		
    if(time2>1)
	{
				    uint16_t a=0x0000,c;
				    uint8_t *array=&c,*Val=&a;
				    RTEReadFirstCh(&a);
				    //uart_num(array[1]);
				    //if(a&0x8000==0x8000)
				    //{
				    //uart_string("in 1");
				    c=(a>>15)&0x0001;
				    if(array[0]==0x01)
				    {
						//a=(a&0x03ff);
						//a=a*(4882);
						//a=a/1000;
						a=a&0x03ff;
						one=(110*a);
						one=one/1024;
						one=(one);
						
						SSDNUM[3]='\0';															//ssdcount=one;
						num2CharArray(SensorValue,SSDNUM);
						ssd1306_String_font6x8(SSDNUM,92,0);
						ssd1306_String_font6x8("cm",112,0);
						if(one<12)
						{
							//SetBlink(PIN_OUT1,0x0008,B);
						}
						else
						{
							//SetBlink(PIN_OUT1,0x0000,B);
						}
						//uart_num(one);
						//uart_string("#1#");
					   // uart_num(Val[0]);
				    }	
					a=0x0800;			   		          
				    RTEReadFirstCh(&a);
				    //uart_num(array[1]);
				    //if(a&0x8000==0x8000)
				    //{
				    //uart_string("in 1");
				    c=(a>>15)&0x0001;
				    if(array[0]==0x01)
				    {
						a=a&0x03ff;
						two=(5*a)*10/1024;
						//uart_string("#2#");
						//uart_num(two);
						//uart_string("#2#");					   // uart_num(Val[0]);
				    }
					a=0x1000;
					RTEReadFirstCh(&a);
					//uart_num(array[1]);
					//if(a&0x8000==0x8000)
					//{
					//uart_string("in 1");
					c=(a>>15)&0x0001;
					if(array[0]==0x01)
					{
						a=a&0x03ff;
						three=(5*a)*10/1024;
						//uart_string("#3#");
						//uart_16Uint(a);
						//uart_string("#3#");						//uart_num(Val[0]);
					}
					time2=0;
		 if(ssdcount<127)
		 {
			 ssdcount++;
		 }
		 else
		 {
			 ssdcount=ssdcount-55;		 
		 }
         
		}


if(Out<127)
{
  ssd1306_Fill_Rectangle(0,5,Out);	
}

					time2++;
   //a=4;
   uart_string("nine\n");
	return 0;
}
uint16_t task2(void)
{
	static uint16_t time1=0,k;
	static uint8_t Errorcount;
	//quality=0;
	struct EventQ e;
	e.EventId=5;
	e.EventFunction=task4Open;

	
	//enq(e);
	//enq(e);
  //RTE_WriteBufferUart("count\n");
  //RTE_WriteBufferUart(countSize());
	time1=time1+1;
	uint16_t Pulse=0;
	uint8_t *check=&Pulse;
	//uart_string("Here");
	//RTE_ReadPulse(&Pulse);
	
	if(time1==500)
	{
		//enq(e);
        	signal=0;
	
			time1=0;
                //PushEventInterface(50,1,0,1);
			    //RTE_ReadPulse(&Pulse);
									uint8_t arr[3];
									arr[0]=0;
									arr[1]=0;
									arr[2]=1;
									((uint16_t*)arr)[0]=SignalHandlerFunc(arr);
									
               if(arr[1]==0x02)
                {
				//uart_num(arr[0]);
		    	//SendEsp=(uint8_t)TimerValue;
		    	//uart_num(check[0]);
		    	//uart_string("\n");
				//uart_num(check[0]);
				FilterUltrasonic(arr[0]);
				SetBlink(PIN_OUT1,0x1000,B);
			    Errorcount=0;
				quality=100;
				
				}
				else
				{
					Errorcount++;
					if(Errorcount>=10)
					{
						//uart_string("Connection error");
						//uart_string("\n");
					    SetBlink(PIN_OUT1,0x1002,B);
						Sigout=0xff;
						SensorValue=0xff;
						quality=0;
					}

					
				}
		    	

	}

	return 0;
}
uint16_t task3(void)
{   
   Blink();
	return 0;
}
uint16_t task4(void)
{	
	uint8_t value;
	static uint16_t countTask4;
	static uint8_t PreviousState,SWITCHCOUNT;
	uint8_t arr[3];
	arr[0]=0;
	arr[1]=1;
	arr[2]=2;
	((uint16_t*)arr)[0]=SignalHandlerFunc(arr);
	char val[4]	;
	if(arr[0])
	{
	  	//RTE_WriteBufferUart("data1");
    // uart_string("ON\n");
	 SWITCHCOUNT++;
	}
    if(SWITCHCOUNT>200)
	{
		//uart_string("data1:\n");
		 //uart_num(arr[0]);
		 SWITCHCOUNT=0;
	}
  /* PinValue(&value,PIN_OUT3,B );
   
   if(value==1)
   {
	   PinOutput(1,PIN_OUT5,D);
	   SetBlink(PIN_OUT1,0x2014,B);
   }
   else
   {
	   PinOutput(0,PIN_OUT5,D);
	    SetBlink(PIN_OUT1,0x2000,B);
   }*/

	countTask4++;
	if(countTask4>=100)
	{
		hours.OperatingHours++;
		//StoreNVM(Nvm_OH,(uint8_t*)&hours,0);;
		countTask4=0;
		//uart_num(countSize());
		//uart_num(deq().EventId);
	}
	//SetDataESP(&count);
}
uint16_t task5(void)
{ f.LargestValue++;
	if(f.LargestValue==201)
	{
		//StoreNVM(Nvm_Ping,&f,1);
		hours.OperatingHours++;
		//StoreNVM(Nvm_OH,(uint8_t*)&hours,0);
		//NVMTask();
		//StoreNVM(Nvm_TankOverflow,(uint8_t*)&hours,0);
		//uart_string("\n");
	}
	
  ESPRetVal RetVal;
  static uint8_t done=0,ConnectionLost,send=0;
  	 static uint16_t Tc;

 /* if (ConnectionLost==1)
  {
	  //ConnectionLost=0;
	  if(ESP_CmdSndOK==ConnectCommand())
	  {
		  ConnectionLost=0;
		  ESP_flags.Server_flag=0;
		  ESP_flags.Request_Flag=0;
		  done=0;
		  SetBlink(PIN_OUT1,0x3000,B);
	  }
  }*/
 /* if(ESP_flags.Connection_flag==0)
  {
	  RetVal=Connect_ESP();
	  
	  if(RetVal==ESP_CmdSndOK)
	  {
		uart_string("done");
	    ESP_flags.Connection_flag=1;
	    done=1;  
	  }
  }
  else*/ 
 if(ConnectionLost==0)
 {   
	 if(ESP_flags.Server_flag==0 && done==0)
  {
	  
	      RetVal=ESPAsServer();
	  
		if(RetVal==ESP_CmdSndOK)
		{
			ESP_flags.Server_flag=1;
			 done=1;
		}
	 
  }
  else if(ESP_flags.Request_Flag==0 && done ==1)
  {
	  //uart_string("DONE");
	  if(RetVal==RequestWait())
	  {
		  ESP_flags.Request_Flag=1;
		  done =2;
	  }
  }
   
  else if(ESP_flags.Request_Flag==1&& done ==2)
  {
	  
      CheckInput();
	 if(enable()==1)
	 {
//RTE_WriteBufferUart("HERE");
	 Tc++;
	 RetVal=ESP_CmdSNDFailed;
	 
	 if(send==0)
	 {
	   
	 }
	 
	  if(Tc>400)
	 {  
		RetVal=SendData(35);
		if(/* &&*/ ESP_CmdSndOK==RetVal)
		{
			send=0;
			Tc=0;
			char val[4]="255";
			val[3]='\0';
			if(quality==100)
			{
			
			val[3]='\0';
			num2CharArray(SensorValue,val);
			RTE_WriteBufferUart("Water Level Monitor");	
            RTE_WriteBufferUart("\n");
			RTE_WriteBufferUart("1.Level");	
			RTE_WriteBufferUart("2.Debug");
			RTE_WriteBufferUart("\n");
			done=3;
			EspConnected=1;
			//printBuffer();
			}
			else
			{
			RTE_WriteBufferUart(val);
			RTE_WriteBufferUart("\n");	
			}
			//uart_char('\n');
		}

	 }
	 }

  }
	 if(done==3)
	 {
		 task6(0);
	 }
  if(ESP_CmdSndOK==WifiDisconnectCheck())
  {
	  ConnectionLost=1;
	  SetBlink(PIN_OUT1,0x3028,B);
	  RTE_WriteBufferUart("HEREOff\n");
  }
 }
   	 if(ESP_CmdSndOK==ConnectCommand())
   	 {
	   	 RTE_WriteBufferUart("HEREON\n");
	   	 ConnectionLost=0;
	   	 ESP_flags.Server_flag=0;
	   	 ESP_flags.Request_Flag=0;
	   	 done=0;
	   	 SetBlink(PIN_OUT1,0x3000,B);
   	 }
}
uint16_t task6(void *callback)
{
	static uint8_t CommunicationStates;
    static funPtrDebug fp;
	static uint16_t pointersave;
				uint8_t *length;
	if(EspConnected==1)
	{
		switch (CommunicationStates)
		{
			case 0:
			if(RequestWait()==ESP_CmdSndOK)
			{
				CommunicationStates=1;
			}
			break;
			case 1:
			  CheckInput();
			  PushEventInterface(200,DebugHandlerFunc,ESPpop,0);
			  //DebugHandlerFunc(ESPpop);
			   CommunicationStates=2;
			  break;
			case 2:
			 if(((uint8_t*)callback)[1]==1)
			 {
                 pointersave=callback;
				 fp=(funPtrDebug*)(((uint16_t*)(callback+2))[0]);
				 CommunicationStates=3;
			 }
			break;
			case 3:
			length=pointersave;
			if(ESP_CmdSndOK==SendData(((length[6]*3))))
			{
				CommunicationStates=1;
				char val2[4]="255\0";
                fp(pointersave);
				//val[3]="\0";
				//RTE_WriteBufferUart(val2);
				//RTE_WriteBufferUart("\n");
			}
			
			
		}
	}
	return 0;
}
uint16_t task1Open(void)
{

	PinOutConfig(0,PIN_OUT2,C);
	PinOutConfig(0,PIN_OUT3,C);
	PinOutConfig(1,PIN_OUT1,B);
	//uart_string("In open 1");

	return 0;
}
uint16_t task2Open(void)
{

	//uart_string("In open 2");
	PinOutConfig(1,PIN_OUT2,B);
	PinOutConfig(1,PIN_OUT1,B);
	PinOutConfig(1,PIN_OUT8,D);
	
	return 0;
}
uint16_t task3Open(void)
{
	uart_string("In open 3");
	uart_num(countSize());
	return 0;
}
uint16_t task4Open(void)
{
	static uint16_t tracker;
	tracker++;
	if(tracker>500)
	{
	  RTE_WriteBufferUart("open4");	
	  //uart_string("open4c");
	  tracker=0;
	}
	
	PinOutConfig(0,PIN_OUT3,B);
	PinOutConfig(1,PIN_OUT7,D);
	PinOutput(1,PIN_OUT3,B);
	PinOutput(0,PIN_OUT7,D);
	return 0;
}

uint16_t task5Open(void)
{
	_delay_ms(2000);
	uart_init();
	PushEventInterface(125,ESPreadvalue,0,0);
	PushEventInterface(175,SignalHandlerFunc,0,0);
	uint16_t Address;
	Address=task6;
	ESPCallBack(&Address);
	OutPutVariableRegister(&SensorValue,1,0);
	/*i2c_init();
	uart_num(i2c_start(0x78));
	uart_num(ssd1036_Init());
	uart_num(ssd1036_chumma());
	for(uint16_t i=0;i<1024;i++)
	{
		ssd1036_chumma();
	}

	ssd1306_String_font6x8("Water Level",0,0);
	ssd1306_String_font6x8("Controller",68,1);
	_delay_ms(20000);
		for(uint16_t i=0;i<1024;i++)
		{
			ssd1036_chumma();
		}
	ssd1306_String_font6x8("Wifi",0,0);
	ssd1306_String_font6x8("Tank level :",0,3);
	
	ssd1306_Rectangle(0,5);
	ssd1306_String_font6x8("Menu",0,7);
	ssd1306_String_font6x8("Back",(127-6*4),7);*/
	//uart_string("In open 5");
	/*while(NvmReadSync(Nvm_OH,&hours)!=0)
	{
		
	}


	uint8_t * point=(uint8_t *)&hours.OperatingHours;
	uart_num(point[0]);
	uart_num(point[1]);
	uart_num(point[2]);
	uart_num(point[3]);*/
	static Nvm_T_TankOverflow Tankov;
	ESP_Init();
	static uint8_t testnvm=9;
	//Tankov.Tank=2;
	a.LargestValue=52;
	f.LargestValue=48;
	c.LargestValue=54;
	//hours.OperatingHours=255;
	//uart_string("\n");
	//StoreNVM(Nvm_Ping,(uint8_t*)&f,0);	
	//StoreNVM(Nvm_OH,(uint8_t*)&hours);
	//StoreNVM(Nvm_TankOverflow,(uint8_t*)&testnvm,0);
/*	while(NvmReadSync(Nvm_TankOverflow,&testnvm)!=0)
	{
			
	}*/
	//StoreNVM(Nvm_OH,(uint8_t*)&testnvm);
	//StoreNVM(Nvm_Ping,&c);
	/*uart_num(TakeAnEvent()->ptr[0]);
	uart_num(TakeAnEvent()->ptr[0]);
	uart_num(TakeAnEvent()->ptr[0]);
	uart_num(TakeAnEvent()->ptr[0]);
	uart_num(TakeAnEvent()->ptr[0]);
	uart_num(GetCurrentEvent()->ptr[0]);*/
	//uart_string("here\n");
	//PrintEvents();
	//uart_string("\n");
	return 0;
}
uint16_t task6Open(void)
{
	
}

static void FilterUltrasonic(uint8_t Distance)
{
	static uint16_t value, previousvalue=0,offset,onebyk;
	uint16_t multiplier;
	onebyk=181;
	//value=(Distance+previousvalue);
	if(Distance>value)
	{
		multiplier=(Distance-value)*100;
        if(multiplier<1804)
		{
			offset=((Distance-value)*100)/onebyk;
		}
		else
		{
			offset=((Distance-value)*100)/1804;
		}
		if(offset==0)
		{
			value=Distance;
		}
		else
		{
			value=value+offset;
		}
		
		
	}
	else
	{
		multiplier=(value-Distance)*100;
        if(multiplier<1804)
		{
			offset=((value-Distance)*100)/onebyk;
		}
		else
		{
			offset=((value-Distance)*100)/1804;
		}
			

		if(offset==0)
		{
			value=Distance;
		}
		else
		{
			value=value-offset;
		}		
	}
	previousvalue=value;
	Sigout=(uint8_t)previousvalue;
	SensorValue=(uint8_t)previousvalue;
	//uart_num(Sigout);
	quality=100;
	//uart_string("\n");
}

void HookupTasks(uint8_t * event1)
{
	//uart_num(event);
	//uart_string("\n");
	//if(event==0x01)
	//{

		if(UartEvents==0x01)
		{
			//DebugMode();
		}
		else
		{
		   // ESPreadvalue(PopInterface);
		    checkRecievedData();	
		}
		//event=0x00;
	//}
	
}

static void num2CharArray(unsigned char num,unsigned char *Ustring)
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));

	Ustring[0]=(H+48);
	Ustring[1]=(T+48);
	Ustring[2]=(O+48);
}