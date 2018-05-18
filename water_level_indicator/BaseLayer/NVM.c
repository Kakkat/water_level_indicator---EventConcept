/*
 * NVM.c
 *
 * Created: 10/18/2017 6:16:29 PM
 *  Author: Nikhil
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
//EEPROM address initial 0
volatile uint16_t eepromaddress;
volatile uint16_t eepromaddressCopy;
//string array index initial 0
volatile uint8_t WriteorRead;
//message to be written to EEPROM
volatile uint8_t NVMState=2;
volatile uint8_t IndexNvmCount;
uint8_t *message;
//EEPROM writing ISR
volatile uint8_t WriteSize;
static void SwitchNvmOff();
ISR(EE_READY_vect)
{
	/*check if not end of string and address
	didn't reach end of EEPROM*/
	static uint8_t deom;
	if(WriteorRead==0)
	{
		//uart_num(eepromaddress);
		//uart_string("\n");
	if (WriteSize!=0)
	{
		//loads address and increments for next load
		NVMState=1;
		EEAR=eepromaddress++;
		//loads current byte and increments index for next load
		WriteSize--;
		uart_string("write\n");
		EEDR=message[WriteSize];
		uart_num(message[WriteSize]);
		//master write enable
		EECR|=(1<<EEMPE);
		//strobe eeprom write
		EECR|=(1<<EEPE);
	}
	else
	{
		//disable eeprom ready interrupt
		//uart_string("switch off");
		SwitchNvmOff();
    }
	}
	else
	{
	
	if(eepromaddress<=(eepromaddressCopy))
	{
		NVMState=1;
		uart_string("read\n");
		EEAR=eepromaddress++;
		EECR|=(1<<EERE);
		message[IndexNvmCount]=EEDR;
		uart_num(message[IndexNvmCount]);
		IndexNvmCount--;
	}
		else
		{
			//disable eeprom ready interrupt
			uart_string("switch read");
			SwitchNvmOff();
			IndexNvmCount=0;
			eepromaddressCopy=0;
			
		}
	}
}

void NvmPopulateWriteSize(uint8_t size,uint8_t startadd,uint8_t WriteorRead1,uint8_t *ptr)
{
	WriteSize=size;
	eepromaddress=0;//startadd;
	WriteorRead=WriteorRead1;
	message=ptr;
	eepromaddressCopy=(eepromaddress+WriteSize)-1;
	IndexNvmCount=WriteSize-1;
	//uart_num(WriteSize);
}

void SwitchNvmOn()
{
	EECR |= (1<<EERIE);
	NVMState=0;
}

static void SwitchNvmOff()
{
	EECR &= ~(1<<EERIE);
	NVMState=2;
	//uart_num(NVMState);
}

uint8_t GetNVMState()
{	
	return NVMState;
}