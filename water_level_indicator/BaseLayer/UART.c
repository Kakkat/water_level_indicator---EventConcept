/*
 * UART.c
 *
 * Created: 8/13/2016 2:46:44 PM
 *  Author: neethu
 */ 
//program read a charactor from UART and again send back, basically called charactor echo, generally use to test UART


#define F_CPU 12000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <string.h>
#include "..\RTE Middle\Rte_types.h"
#include "..\MddleLayer\DebugHandler.h"
#include "..\OS\EventQ.h"
#include "..\OS\OSRR.h"
#define EspRead 0x01
#define  circularbuff(x,y) \
volatile unsigned char  ESPUartData[y];   \
volatile Cbuff_t x={                \
	ESPUartData,           \
	0,                     \
	0,                     \
	y                      \
};                          \


void uart_init()
{   Data_Count=0;
	/*UCSR0A=0x02;//for esp baud 0x02 
	UCSR0B=0x98;
	UCSR0C=0x86;
	UBRR0H=0x00;
	UBRR0L=0x0C;//0x0C;//--> FOR BAUD esp;0x9b-->for 9800
	Data_Count=0;	
	//UCSRB|=(1<7);
	//uart_delay(100);*/
		//UCSR0A=0x02;//for esp baud 0x02
		UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);//UCSR0B=0x98;
		UCSR0C = (1<<USBS0)|(3<<UCSZ00);//UCSR0C=0x86;
		UBRR0H=0x00;
		UBRR0L=0x08;//--> FOR BAUD esp;0x9b-->for 9800//0x69
		//UDR0='B';
		//Data_Count=0;
		callbackFunction=0;
		callbackSetFunction(0,ConfigureCallBack);
}

void uart_char(unsigned char uchar)
{
	UDR0=uchar;
	while((UCSR0A&0x40)==0x00);
	uart_delay(1000);
}
void uart_string1(const unsigned char *ustring)
{
	while ( *ustring )
	{
		uart_char(*ustring++);
		//UDR=*ustring++;
		//while((UCSRA&0x40)==0x00);
		//uart_delay(1000);
	}	
}
void uart_string(const unsigned char *ustring)
{

	while ( *ustring)
	{
		UDR0=*ustring++;
		while((UCSR0A&0x40)==0x00);
		uart_delay(1000);
	}
}

void uart_num(unsigned char num)
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));

	uart_char(H+48);
	uart_char(T+48);
	uart_char(O+48);
}
void uart_16Uint(uint16_t num)
{
	if(num>255)
	{
		num=255;
	}
	else
	{
		uart_num((uint8_t) num);
		num=1;
	}
	uint16_t n,i=0,index;
	unsigned char a[6];
	n=num;
	while(n)
	{
		a[i]=n%10;
		n=n/10;
		i++;
	}
	i--;
	while(i)
	{
		uart_char(a[i]+48);
		i--;
	}
	uart_char(a[i]+48);
}
unsigned char uart_read()
{
	while((UCSR0A&0x80)==0x00);
	return UDR0;
}

void uart_delay(unsigned int delaytime)
{
	unsigned int dc;
	for(dc=0;dc<=delaytime;dc++)
	{
		asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
		asm("nop");asm("nop");asm("nop");asm("nop");
		asm("nop");asm("nop");asm("nop");asm("nop");
	}
	
}
circularbuff(CircularBuffer,100);
ISR(USART_RX_vect)
{
    
    static uint8_t flag=0;
	static UartBuffer BufferData;
	r=UDR0;
	uint8_t i;
	char data;
	//cli();
	PushIntoCircularBuffer(&CircularBuffer,r);
	//sei();
	if(r=='d')
	{
		Data_Count=0;
		
	}
	data_in[Data_Count]=r;
	Data_Count++;
	if(Data_Count==5)
	{
		if(data_in[0]=='d'&&data_in[1]=='e'&&data_in[2]=='b'&&data_in[3]=='u'&&data_in[4]=='g')
		{
			

			while(PopFromCircularBuffer(&CircularBuffer,&data)==0)
			{
				uart_char(data);
			}
			flag=1;
		}
		Data_Count=0;
	}
	if(callbackFunction!=0&&flag==0)
	{
		PushEventInterface(200,callbackFunction,PopInterface,0);
	}
	else if(flag==2)
	{
		if(HeadTailDiff(&CircularBuffer,20)>=20)
		{
			PushEventInterface(200,Callhandler,PopInterface,0);
		}
	}
	else if(flag==1)
	{
		flag=2;
		PopFromCircularBuffer(&CircularBuffer,&data);
	}
	
}

uint8_t PopInterface(unsigned char *dataval)
{
	unsigned char data;
	
	if(PopFromCircularBuffer(&CircularBuffer,&data)==BuffOk)
	{
		*dataval=data;
		return 0;
	}
	return 1;
}
uint8_t PushInterface(unsigned char *dataval)
{
	PushIntoCircularBuffer(&CircularBuffer,dataval);
}
uint8_t CheckUartReadyToSend()
{ 
	return (!(UCSR0A&(1<<UDRE0)));
}

void SendByte(unsigned char dat)
{
	UDR0=dat;
}

void ConfigureCallBack(uint16_t  (*callbackarg)(void))
{
	callbackFunction= callbackarg;
}
CbuffState_t BufferEmpty()
{
	return IsBuffempty(&CircularBuffer);
}

//updated code
 uint16_t Callhandler(void *fptr)
{
	PushEventInterface(200,DebugHandlerFunc,PopInterface,0);
}