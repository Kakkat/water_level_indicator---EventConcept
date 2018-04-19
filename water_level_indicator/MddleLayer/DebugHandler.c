/*
 * DebugHandler.c
 *
 * Created: 3/26/2018 4:16:53 PM
 *  Author: Nikhil
 */ 

#include "..\BaseLayer\UART.h"
#include "UartTransmit.h"
#include "DebugHandler.h"
uint8_t Datastore[20];
typedef uint8_t (*PopFuncPointer) (char*);
uint8_t charHex[]={0,1,2,3,4,5,6,7,8,9,0x0a,0x0b,0x0c,0x0d,0x0e,0x0F};
char    HexChar[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
VariableManager VariableManager_t[5];
static	uint8_t chartohex(char arg);
typedef uint16_t (*argp)(void *);
argp argp1;
uint16_t DebugHandlerFunc(void *fptr)
{
	static uint8_t Pos[12];
	char data;
	void *CallBackptr;
	uint8_t i=0,k=0;
	uint16_t TEMP=ReadRambyte;
	
	while((*((PopFuncPointer)fptr))(&data)==0)
	{
		
		if(i<10)
	{
		if(k==0)
		{
        Pos[i]=(0xF0 &((chartohex(data))<<4));
		}
		if(k==1)
		{
		Pos[i]=Pos[i]|((0x0F &(chartohex(data))));	
		}
		k++;
		if(k==2)
		{
		  i++;
		  k=0;	
		}
	}
	else
	{
	  Pos[i]=data;
	  i++;
	}
			
	}

	if(Pos[0]==0xab)
	{
	   
        TEMP=ReadRambyte;
		if(Pos[3]==0)
		{
		  //uart_string((char*)0x01ed/*(char*)((uint16_t)(Pos[1]<<8)|Pos[2])*/);	
          Datastore[0]=0;
          Datastore[1]=1;
          Datastore[2]=((uint8_t*)(&TEMP))[0];
          Datastore[3]=((uint8_t*)(&TEMP))[1];
          Datastore[4]=Pos[2];
          Datastore[5]=Pos[1];
          Datastore[6]=Pos[4];
		  Datastore[12]=Pos[4];
		 //ReadRambyte(Datastore);;
		 //PushEventInterface(52,1,Datastore,0);
		}
		else if(Pos[3]==1)
		{
		  //
		  Datastore[1]=0;
		  PushEventInterface(52,1,Datastore,0);
		} else if(Pos[3]==2)
		{
			
		}
	}
	else if(Pos[0]==0xac)
	{
		 TEMP=WriteRambyte;
          Datastore[0]=0;
          Datastore[1]=1;
          Datastore[2]=((uint8_t*)(&TEMP))[0];
          Datastore[3]=((uint8_t*)(&TEMP))[1];
          Datastore[4]=Pos[2];
          Datastore[5]=Pos[1];
          Datastore[6]=Pos[3];
		  Datastore[7]=Pos[4];
		  Datastore[8]=Pos[5];
		  Datastore[9]=Pos[6];
	      Datastore[10]=Pos[7];
		  Datastore[11]=Pos[8];
		  Datastore[12]=Pos[9];
		  //PushEventInterface(52,1,Datastore,0);	
	}
	else if(Pos[0]==0xfd)
	{
		TEMP=ReadRambytesNonCnt;
		Datastore[0]=0;
		Datastore[1]=1;
		Datastore[2]=((uint8_t*)(&TEMP))[0];
		Datastore[3]=((uint8_t*)(&TEMP))[1];
		Datastore[4]=Pos[2];
		Datastore[5]=Pos[1];
		Datastore[6]=Pos[4];
		Datastore[7]=Pos[3];
		Datastore[8]=Pos[6];
		Datastore[9]=Pos[5];
	    Datastore[10]=Pos[8];
	    Datastore[11]=Pos[7];
	    Datastore[12]=Pos[9];
		
	}
	else if(Pos[0]==0xbd)
	{
		TEMP=ReadRambyte;
        Datastore[0]=0;
        Datastore[1]=1;
        Datastore[2]=((uint8_t*)(&TEMP))[0];
        Datastore[3]=((uint8_t*)(&TEMP))[1];
        Datastore[4]=((uint8_t *)&(VariableManager_t[Pos[1]].VariableAdd))[0];
        Datastore[5]=((uint8_t *)&(VariableManager_t[Pos[1]].VariableAdd))[1];
        Datastore[6]=VariableManager_t[Pos[1]].VariableSize;
        Datastore[12]=VariableManager_t[Pos[1]].VariableSize;
	}
	if(data=='!')
	{
	  argp1=(argp *)(((uint16_t*)(Pos+11))[0]);
	  PushEventInterface(201,argp1,Datastore,0);
	}
	else
	{
	  PushEventInterface(52,1,Datastore,0);
	}
	return 0;
}

static uint8_t chartohex(char arg)
{
	if(arg>='0' && arg<='9' )
	{
		return charHex[arg-'0'];
	}
	else if(arg>='A' && arg<='F')
	{
		return charHex[arg-'A'+10];
	}
	return 0;	
}

uint16_t ReadRambyte(void *Ptr)
{
	uint8_t i;
	uint8_t *address;
	address=((uint8_t*)((uint16_t)(((uint8_t*)Ptr)[5]<<8)|((uint8_t*)Ptr)[4]));
	FillUartBufferSiglechar('\n');
	for(i=0;i<((uint8_t*)Ptr)[6];i++)
	{
		FillUartBufferSiglechar(HexChar[((address[0]&0XF0)>>4)]);
		FillUartBufferSiglechar(HexChar[(address[0]&0X0F)]);
		FillUartBufferSiglechar(' ');
		address++;
	}
	
	return 0;
}

uint16_t WriteRambyte(void *Ptr)
{
	uint8_t i;
	uint8_t *address;
	address=((uint8_t*)((uint16_t)(((uint8_t*)Ptr)[5]<<8)|((uint8_t*)Ptr)[4]));
	FillUartBufferSiglechar('\n');
	for(i=0;i<((uint8_t*)Ptr)[12];i++)
	{
		FillUartBufferSiglechar(HexChar[((address[0]&0XF0)>>4)]);
		FillUartBufferSiglechar(HexChar[(address[0]&0X0F)]);
		FillUartBufferSiglechar(' ');
		*address=((uint8_t*)Ptr)[i+6];
		address++;
		Datastore[1]=0;
	}

	PushEventInterface(52,1,Datastore,0);	
	return 0;
}

//FD {ADDRESS}
//2bytes each t last byte is length
//-->EXAMPLE ROUTINE :-FD01ED01EE01EF01F004
//01ED --> one address
//everything is in hex
//04-->length
uint16_t ReadRambytesNonCnt(void *Ptr)
{
    uint8_t i;
	uint8_t *address;
	FillUartBufferSiglechar('\n');
	for(i=0;i<(((uint8_t*)Ptr)[12]*2);i=i+2)
	{
		address=((uint8_t*)((uint16_t)(((uint8_t*)Ptr)[i+1+4]<<8)|((uint8_t*)Ptr)[i+4]));
		FillUartBufferSiglechar(HexChar[((address[0]&0XF0)>>4)]);
		FillUartBufferSiglechar(HexChar[(address[0]&0X0F)]);
		FillUartBufferSiglechar(' ');
	}
	
	return 0;	
}

uint8_t OutPutVariableRegister(uint16_t Outadd,uint8_t Varsize,uint8_t Varid)
{
	VariableManager_t[Varid].VariableAdd=Outadd;
	VariableManager_t[Varid].VariableId=Varid;
	VariableManager_t[Varid].VariableSize=Varsize;
}