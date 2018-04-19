/*
 * GccApplication1.c
 *
 * Created: 8/6/2016 5:55:55 PM
 *  Author: neethu
 */ 

#define F_CPU 16000000UL
#define value={{task1},{task2},{task3},}
#include "OSRR.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include "..\OS\Taskadd.h"
#include "..\RTE ASW\Rte_ASW.h"
#include "..\BaseLayer\ADC.h"
#include "..\BaseLayer\I2C.h"
static uint32_t clock_freq=12000000;
uint16_t ADC_Array[10];
#include "..\BaseLayer\NVM.h"
#include "Events.h"
volatile struct Events_t *testev=0;
volatile struct Events_t *lasttestev=0;
static void loopthrough();
	static unsigned char str[] = "I am working.";
	static unsigned char str1[] = "Nik";
	static void adddummyevent(uint8_t *pt);
struct EventQ e;
void delayms( uint16_t millis )  {

	while( millis )  {

		_delay_ms( 1 );
		millis--;

	}

}


//ISR(TIMER0_COMP_vect) {
static volatile uint8_t pin_timeout=1;
static volatile uint8_t TimeCount;
ISR(TIMER0_OVF_vect){
	static uint32_t counter5ms=0;
	if(counter5ms==1)
	{   
		TimeCount++;
		counter5ms=0;
		

	}
	//TCNT0=70;
	TCNT0=0;
	counter5ms++;
}
void set_timer(uint16_t enable)
{
	//PORTB|=x;
	if(enable==1)
	{
		TIMSK0|=(1<<TOIE0);

		//PORTB=0xFF;
	}

}
int main() {
   // event=0;
	uint16_t tmp;
	uint16_t Limitflag=0;
	//
    
	ExtIntInit();
	//
	//
	DDRC=0x00;
	//PinOutConfig(PIN_OUT1);
	DDRD=0b11111011;					// set pd2 as input for int
	PORTD|=(1<<PIND2);	
	PORTD|=(1<<PIND3);				// Port C lower nibble initialization as high (Pull-up mode)
	//uart_string("I am working.");
	sei();
	// enable timer overflow interrupt for Timer0
	TIMSK0|=(1<<TOIE0);
	// set timer0 counter initial value to 0
	TCNT0=70;//255-(clock_freq/1000000);
	// start timer0 with / prescaler 78 Hz
	TCCR0B = (1<<CS01)|(1<<CS00);

uart_init();
	adc_init();				//initialization of UART
	create();
    uart_string("working");
	// enable interrupts
	//sei();
	//pin
	set_timer(1);
    //EECR |= (1<<EERIE);
    //adddummyevent(str);
	//adddummyevent(str1);
	//adddummyevent(str);
    //loopthrough();
	
	//uart_string(testev1->ptr);
	//uart_string(testev2->ptr);
	//AddEvent((uint8_t *)str,0);
	//AddEvent((uint8_t *)str,1);
	//AddEvent((uint8_t *)str1,2);
	//PrintEvents();
								e.EventId=1;
								e.EventFunction=tasks;
	while(1)
	{
		if(TimeCount==1)
		{
			static uint8_t odd=1;
			odd++;
		   PushEventInterface(1,tasks,0,0);
		   PushEventInterface(2,NonPeriodicTaskFuncCall,0,0);
           TimeCount=0;
		}
	//	enq(e);
	   if(PopEventInterface(&e)==eBuffOk)
	   {
		   if(e.EventFunction!=0)
		   {		   
		   if(e.EventId>=125 && e.EventId<200)
		   {
			   if(e.EventId<175)
			   {
			   callbackgetFunction(e.EventId-125)(e.EventFunction);		
			   }
			   else
			   {
				 callbackSetFunction(e.EventId-173,e.EventFunction);  
			   }
		   }
		   else
		   {
			   if(e.EventId>=200)
			   {
				  e.EventFunction(e.ptr); 
			   }
			   else if(e.EventId>=50 && e.EventId<125)
			   {
				  //uart_num(e.EventId);
				  callbackgetFunction(e.EventId-49)((&e.State));
				  if(e.EventId==52)
				  {
					 callbackgetFunction(e.EventId-49)((e.ptr)); 
				  }
				  //callbackSetFunction(e.EventId-48,e.EventFunction);
			   }
			   else
			   {
				  e.EventFunction(0); 
			   }
			   
		   }
		   }
	   }
		  if(countSize()>1)
		  {
			  
			//OSRR_Events();  
		 }
	if(event ==1 || event ==0)
	{
		ApplicationHookUP(&event);
		//event=0;
	}	

	
	}
}

static void loopthrough()
{
		struct Events_t *loop;
		loop=testev;
		uart_string("hello");
		while(loop!=0)
		{
			uart_string(loop->ptr);
			loop=loop->next;
		}
}

static void adddummyevent(uint8_t *pt)
{
	if(testev=0)
	{
		testev=(struct Events_t *)malloc(sizeof(struct Events_t ));
	    testev->ptr=pt;
		testev->next=0;
		lasttestev=testev;
		//uart_string(testev->ptr);
	}
	else
	{
		struct Events_t *testev1=(struct Events_t *)malloc(sizeof(struct Events_t ));
		testev1->ptr=pt;
		testev1->next=0;
		lasttestev->next=testev1;
		lasttestev=testev1;
		//uart_string(testev1->ptr);
	}
}