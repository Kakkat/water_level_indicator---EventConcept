/*
 * ESP8266.c
 *
 * Created: 10/30/2016 3:32:31 PM
 *  Author: Nikhil
 */ 
//C:\Users\Nikhil\Documents\Atmel Studio\6.1\water_level_indicator\water_level_indicator\BaseLayer\UART.c
#include "..\OS\EventQ.h"
#include "..\RTE Base\RTEAdcRead.h"
#include "..\RTE Base\Rte_Uart.h"
#include "ESP8266.h"
#include "..\BaseLayer\UART.h"
#include "..\RTE Middle\Rte_types.h"
#include <string.h>
#define close 0
#define open 1
unsigned char str[] = "I am here.";
unsigned char Check[]="AT\r\n";
unsigned char Mode[]="AT+CWMODE=3\r\n";
unsigned char MUX[]="AT+CIPMUX=1\r\n";
unsigned char SERVER[]="AT+CIPSERVER=1,80\r\n";
unsigned char GETIP[]="AT+CIFSR\r\n";
unsigned char WIFISET[]="AT+CWJAP=\"nikhil\",\"12345678\"\r\n";
unsigned char SEND[]="AT+CIPSEND=";
unsigned char DATA[]="NIKHIL";
unsigned char Connection_Response[]="GOT IP";
unsigned char Close_Channel[]="AT+CIPCLOSE=0\r\n";
unsigned char Wait[]="";
unsigned char Response1[]="OK";
unsigned char ResponseGET1[]="+IPD";
unsigned char ResponseSend1[]=">";
unsigned char uartDebug[]="#Uart#";
static unsigned char EspDataBuffer[31];
static unsigned char EspPortBuffer[15];
static uint8_t PortLen;
volatile ESP_CommandIndex Esp_Index;
unsigned char DisConnection_Response1[]="WIFI DISCONNECT";
uint16_t EspGlobalCounter(uint8_t state);
uint8_t findpos(const unsigned char *ustring,uint8_t pos,char sub);
ESPRetVal CipSend(void);
static uint16_t counter1,counter2;
static uint8_t datagot,BUFFEREnable;
static uint8_t PortStart,PortEnd;
static uint8_t PortSel,LENGTH;
static uint8_t channelState;
static ESP_PortConnection PortConnection=initiated;
static char Recieved[10];
static EspDataCount;
uint16_t print(void *);
void test1();
void test2();
typedef uint8_t (*PopFuncPointer) (char*);
static void num2CharArrayESP(unsigned char num,unsigned char *Ustring);

//static uint8_t Purpose[2];
ESP_DataRead_t ESP_DataRead_a[2]=
{
	{"START",0},
	{"DAIG#",0}
}; 
Esp_Commands Esp_Commands_a[Cmd_EndofList]=
{
   //-------------------------------------------------------------
   //Command|Response|State|Match counter|Response Length|Position 
   //-------------------------------------------------------------
	{WIFISET,Response1,0,0,0,10},
	{Wait,Connection_Response,0,0,0,100},
	{Mode,Response1,0,0,0,100},
	{MUX,Response1,0,0,0,100},
	{SERVER,Response1,0,0,0,100},
	{GETIP,Response1,0,0,0,100},
	{Wait,ResponseGET1,0,0,0,100},
	{SEND,ResponseSend1,0,0,0,100},
	{DATA,Response1,0,0,0,1000},
	{Close_Channel,Response1,0,0,0,1000},
	{Wait,DisConnection_Response1,0,0,0,1000},
	{Wait,uartDebug,0,0,0,1000}                                       
};

uint16_t ESPreadvalue(void *fptr)
{
	 unsigned char data='&';
	while((*((PopFuncPointer)fptr))(&data)==0)
	{
   
	if(data!='&' && data=='#' )
	{

	}
	if(data!='&' && data=='*')
	{
		unsigned char *reg;
		uint8_t i;
	}
	static uint8_t Datalog,k=0;
	for(int i=Wifi_Command;i<Cmd_EndofList;i++)
	{
		
		if(Esp_Commands_a[i].state==1 && data!='&' )
		{  

			if(data==Esp_Commands_a[i].Response[Esp_Commands_a[i].MatchCounter]) 
			{
			  if(Esp_Commands_a[i].MatchCounter<Esp_Commands_a[i].ResposeLength )
			  {
				  Esp_Commands_a[i].MatchCounter=Esp_Commands_a[i].MatchCounter+1;
			  }
			  if(Esp_Commands_a[i].MatchCounter==(Esp_Commands_a[i].ResposeLength))
			  {

					  Datalog=1;
					  k=0;
			  }
			}
			else if(Esp_Commands_a[i].MatchCounter<(Esp_Commands_a[i].ResposeLength))
			{
				Esp_Commands_a[i].MatchCounter=0;
				//k=0;
			}
			
		}
	}
	if(Datalog==1)
	{
		if(data!='&'){
		EspDataBuffer[k]=data;
		k++;
		//uart_char(data);
		}
		if(k==28 || data=='\n')
		{
			Datalog=0;
			k=0;
			datagot=1;
			BUFFEREnable==0;
			//Esp_Commands_a[Wait_Command].MatchCounter=0;
		}
	}
	}
	return 0;
}

ESPRetVal CommandSend(ESP_CommandIndex Index)
{
	static uint8_t ConnectionFlag;
	uint16_t counter=0;
	//static ESP_CommandIndex Index=Wifi_Command;
	ESPRetVal ReturnValue=ESP_CmdSndBusy;
	if(ConnectionFlag==0)
	{
		RTE_WriteBufferUart(Esp_Commands_a[Index].ustring);//uart_string(Esp_Commands_a[Index].ustring);
		if(Index==Send_Command)
		{
			(void)CipSend();
		}
		Esp_Commands_a[Index].state=1;
		ConnectionFlag=1;
		EspGlobalCounter(1);
	}
	if((Esp_Commands_a[Index].MatchCounter)==Esp_Commands_a[Index].ResposeLength)
	{
		if(Index!=Wait_Command)
		{
			Esp_Commands_a[Index].state=0;
		    Esp_Commands_a[Index].MatchCounter=0;
		}
		ConnectionFlag=0;
		ReturnValue=ESP_CmdSndOK;
	}
	counter=EspGlobalCounter(2);
	
	if(counter>Esp_Commands_a[Index].WaitTime)
	{
	  Esp_Commands_a[Index].state=0;
	  Esp_Commands_a[Index].MatchCounter=0;
	  counter1=0;
	  ConnectionFlag=0;
	  EspGlobalCounter(1);
	  ReturnValue=ESP_CmdSNDFailed;
	  
	}
	
    
	return ReturnValue;
}

void ESP_Init()
{
	for(int i=Wifi_Command;i<Cmd_EndofList;i++)
	{
		Esp_Commands_a[i].ResposeLength=strlen(Esp_Commands_a[i].Response);
        
	}
	
	Esp_Commands_a[Disconnect_Command].state=1;
    Esp_Commands_a[Connection_Wait].state=1;
	Esp_Commands_a[Uart_command].state=1;
	
}

ESPRetVal CipSend(void)
{
  ESPRetVal ReturnValue=ESP_CmdSndBusy;
      char Val[4];
	  Val[0]=(char)PortSel;
	  Val[1]='\0';
	  RTE_WriteBufferUart(Val);//uart_char(PortSel);
	  RTE_WriteBufferUart(",");
	  //Val[0]=(char)(EspDataCount+48);
	  num2CharArrayESP(EspDataCount,Val);
	  Val[3]='\0';
	  if(EspDataCount<10)
	  {
		  Val[0]=Val[2];
		  Val[1]='\0';		  
	  }
	  else if(EspDataCount<100)
	  {
		  Val[0]=Val[1]; 
		  Val[1]=Val[2]; 
		  Val[2]='\0'; 
	  }
	  RTE_WriteBufferUart(Val);//uart_char(Recieved[0]);
	  //uart_char(Recieved[1]); 
	  RTE_WriteBufferUart("\r\n");//uart_string("\r\n");

}

ESPRetVal WifiDisconnectCheck()
{
		if(Esp_Commands_a[Disconnect_Command].MatchCounter==Esp_Commands_a[Disconnect_Command].ResposeLength)
		{
			//Esp_Commands_a[Connection_Wait].MatchCounter=0;
			Esp_Commands_a[Disconnect_Command].MatchCounter=0;
			return ESP_CmdSndOK;
		}
	return ESP_CmdSNDFailed;
}

ESPRetVal Connect_ESP()
{
	
	return CommandSend(Mode_Command);
}
ESPRetVal ESPAsServer()
{
  static uint8_t index;
  static uint8_t flag=0;
  static uint8_t RetryCounts;
  ESPRetVal ReturnValue,FuncRet=ESP_CmdSndBusy;
  if(flag==0)
  {
	index=Server_Command;
	flag=1;
  }
  
	  ReturnValue=CommandSend(index);
	  if(ReturnValue==ESP_CmdSndOK)
	  {
		  index=index+1;
		    if(index==Wait_Command)
		    {
			    FuncRet= ESP_CmdSndOK;
				flag=0;
		    }
	  }
	 else if(ReturnValue==ESP_CmdSNDFailed)
	  {
		   if(RetryCounts>4)
		   {
			   if(index==Mode_Command)
			   {
				   RetryCounts=0;
				   FuncRet= ESP_CmdSNDFailed;
				   flag=0;
			   }
			   else
			   {
				   
				   Esp_Commands_a[index].state=0;
				   Esp_Commands_a[index].MatchCounter=0;
				   index=index-1;
				   RetryCounts=0;
			   }
		   }
		  RetryCounts++;
		 
	  }
	  



  return FuncRet;
}
ESPRetVal RequestWait()
{
	  static uint8_t indexReq;
	  static uint8_t FlagReq=0;
	  static uint8_t RetryCountsReq;
	  ESPRetVal FuncRet=ESP_CmdSndBusy;
	  static ESPRetVal ReturnValue=ESP_CmdSndBusy;
	  if(FlagReq==0)
	  {
		    indexReq=Wait_Command;
		    FlagReq=1;
	        BUFFEREnable=1;
			 
			
	  }

 
	  	  if(ReturnValue!=ESP_CmdSndOK )
	  	  { 
				ReturnValue=CommandSend(Wait_Command);

		  }
		  else
		  {
					if(datagot==1)
					{
						FlagReq=0;
						BUFFEREnable=0;
						CheckInput();
						//Esp_Commands_a[Wait_Command].state=1;
						//Esp_Commands_a[Wait_Command].MatchCounter=0;
						FuncRet= ESP_CmdSndOK;
						ReturnValue=ESP_CmdSndBusy;
					}		   
		  }

	  	  
return FuncRet;
}
uint16_t EspGlobalCounter(uint8_t state)
{
	
	if(state==1)
	{
	  	counter1=0;
	}
	else if(state==2)
	{
		counter1++;
	}

return	counter1;
}

void printBuffer()
{
	uint16_t STA;
	uint16_t DDD;
	uint8_t *regdata;
	uint8_t length;
	regdata=0x00c9;
	DDD=(uint16_t)( EspPortBuffer[0]-48)*100;
	STA=STA+DDD;
	DDD=(uint16_t)( EspPortBuffer[1]-48)*10;
	STA=STA+DDD;
	DDD=(uint16_t)( EspPortBuffer[2]-48);
	STA=STA+DDD;
	regdata=STA;
	if(EspPortBuffer[3]=='R')
	{
		length=((uint8_t)( EspPortBuffer[7]-48)*10)+((uint8_t)( EspPortBuffer[8]-48));
		if(EspPortBuffer[9]=='S')
		{
		  while(length)	
		  {
			 //if((unsigned char)*regdata>='0' && (unsigned char)*regdata<='9' )
			 //{
				//uart_char(((unsigned char)*regdata-'0')+48);
			 //}
			 //else
			 //{
				uart_char(*regdata);
				//uart_num(*regdata);
			 //}
			 
			 regdata++;
			 length--;
		  }
		}
		else if(EspPortBuffer[9]=='I')
		{
		  uart_num(*regdata);
		}
		uart_char('\n');
	}
	else if(EspPortBuffer[3]=='W')
	{
    DDD=(uint16_t)( EspPortBuffer[4]-48)*100;
	STA=STA+DDD;
	DDD=(uint16_t)( EspPortBuffer[5]-48)*10;
	STA=STA+DDD;
	DDD=(uint16_t)( EspPortBuffer[6]-48);
	STA=STA+DDD;
	uart_string("Current value:");
	uart_num(*regdata);
	*regdata=((uint8_t)( EspPortBuffer[4]-48)*100)+((uint8_t)( EspPortBuffer[5]-48)*10)+(uint8_t)( EspPortBuffer[6]-48);
	uart_string("  changed value:");
	uart_num(*regdata);
	uart_char('\n');
	}

}
uint16_t print(void *fptr)
{
	uart_string("h");
	return 0;
	//test1();
}
void test1()
{
	RTE_WriteBufferUart("test1");
	test2();
}
void test2()
{
	RTE_WriteBufferUart("test2");
}
uint8_t findpos(const unsigned char *ustring,uint8_t pos,char sub)
{
	while(ustring[pos]!='\0')
	{
		if(ustring[pos]==sub)
		{
			return pos+1;
		}
		pos++;
	}
	return 0;
}

void PortCopy(const unsigned char *ustring,unsigned char *copy,uint8_t start,uint8_t end)
{
	uint8_t pos=0;
	while(start<end && pos<4 )
	{
		copy[pos]=ustring[start];
		pos++;
		start++;
	}
	copy[pos]=ustring[start];
	PortLen=pos;
	
}

ESPRetVal SendData(uint8_t count)
{
	EspDataCount=count;
	return CommandSend(Send_Command);
}


ESPRetVal ConnectCommand()
{
	//uart_num(Esp_Commands_a[Connection_Wait].MatchCounter);
	if(Esp_Commands_a[Connection_Wait].MatchCounter==Esp_Commands_a[Connection_Wait].ResposeLength)
	{
		//uart_string("wifi connected");
		Esp_Commands_a[Connection_Wait].MatchCounter=0;
		//Esp_Commands_a[Disconnect_Command].MatchCounter=0;
		return ESP_CmdSndOK;
	}
	return ESP_CmdSNDFailed;
}
uint8_t CheckInput()
{
	//uart_string(EspDataBuffer);
	if(datagot==1)
	{
		if(Esp_Commands_a[Wait_Command].MatchCounter==Esp_Commands_a[Wait_Command].ResposeLength)
		{ 
			Esp_Commands_a[Wait_Command].state=1;
			Esp_Commands_a[Wait_Command].MatchCounter=0;	
			PortStart=findpos(EspDataBuffer,0,',');
			PortEnd=findpos(EspDataBuffer,PortStart,',');
			PortCopy(EspDataBuffer,EspPortBuffer,PortStart,PortEnd);
			PortSel=EspPortBuffer[0];
			PortStart=findpos(EspDataBuffer,PortEnd,':');
			PortCopy(EspDataBuffer,EspPortBuffer,PortEnd,PortStart);
			Recieved[0]=EspPortBuffer[0];
			Recieved[1]=EspPortBuffer[1];
			uint8_t initial ;
			initial=(uint8_t )EspPortBuffer[0];
			PortEnd=PortStart;
			PortStart=PortStart+(uint8_t )EspPortBuffer[0];
			PortCopy(EspDataBuffer,EspPortBuffer,PortEnd,PortStart);
			/*uint8_t posi;
			for( posi=PortEnd;posi<PortStart;posi++)
			{
				Recieved[posi]=EspDataBuffer[posi];
				
			}*/
			EspPortBuffer[PortStart-2]='\0';
			//RTE_WriteBufferUart(EspPortBuffer);//uart_string(EspPortBuffer);
			//RTE_WriteBufferUart(EspDataBuffer);
			
		}
		//uart_string(EspDataBuffer);
		datagot=0;
	}
	if(Esp_Commands_a[Uart_command].MatchCounter==Esp_Commands_a[Uart_command].ResposeLength)
	{
		//uart_string("uart debug mode enabled");
		UartEvents=0x01;
	}
	
}

uint8_t enable()
{
	
   return ESP_DataRead_a[0].Purpose;
}

void checkRecievedData()
{
	for(uint8_t i=0;i<2;i++)
	{
			if(strcmp(EspPortBuffer,ESP_DataRead_a[i].strp))
			{
				ESP_DataRead_a[i].Purpose=0;
			}
			else
			{
				ESP_DataRead_a[i].Purpose=1;
			}
				
	}
}

void Uart_DebugMode(void)
{
   unsigned char data='&';
   static uint8_t UartDebugFlag,UartDebugState;
   PopInterface(&data);
   if(UartDebugFlag>0 && data!='&'&& UartDebugFlag<=10)
   {
	   EspPortBuffer[UartDebugFlag-1]=data;
	   if(UartDebugFlag==3 || UartDebugFlag==1 || UartDebugFlag==2)
	   {
		   uart_char(data);
	   }   
	   UartDebugFlag++;
   }
   if(UartDebugFlag==11)
   {
	   if(EspPortBuffer[3]=='W')
	   {
		 UartDebugState=1;
		 if(data=='Y')
		 {
			printBuffer();
			UartDebugFlag=0;
		 }
	   }
	   else
	   {
		  printBuffer();
		  UartDebugFlag=0;  
	   }

   }
   if(data=='#' && UartDebugFlag==0)
   {
	 UartDebugFlag=1;
   }
}

uint8_t ESPpop(char *Bytex)
{
	static uint8_t PosByte;
	EspDataBuffer[30]='!';
	*Bytex=EspDataBuffer[PosByte+7];
	if(PosByte==23)
	{
		PosByte=0;
		return 1;
	}
	else
	{
		PosByte++;
	}
	return 0;
}

void ESPCallBack(void *fillcallback)
{
	char* mediator;
	mediator=(char*)fillcallback;
	EspDataBuffer[28]=mediator[0];
	EspDataBuffer[29]=mediator[1];

}

static void num2CharArrayESP(unsigned char num,unsigned char *Ustring)
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));

	Ustring[0]=(H+48);
	Ustring[1]=(T+48);
	Ustring[2]=(O+48);
}

