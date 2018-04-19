/*
 * ADC.c
 *
 * Created: 8/6/2016 8:44:30 PM
 *  Author: neethu
 */ 
#include "ADC.h"
#include "..\BaseLayer\UART.h"
void adc_init(void){

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHzjkh

	ADMUX |= (1 << REFS0)|(1 << REFS1); // Set ADC reference to 2.56 internal
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	// No MUX values needed to be changed to use ADC0

	//ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode
	ADCSRA |= (1 << ADIE);	
	//ADCSRA |= (1 << ADEN);  // Enable ADC
    //ADCSRA |= (1 << ADSC);  // Start A2D Conversions
	
}

void adc_read(unsigned char ch){
    ADCSRA |= (1 << ADEN);
	ADMUX &= 0xF8; // clear bottom 3 bits
	ADMUX |= ch; // then set bottom 3 bits to channel n

	//uart_num(ch);
	ADCSRA |= (1 << ADSC);//|(1<<ADEN);  // Start A2D Conversions
	
}

uint8_t ADC_State()
{	
	return bit_is_set(ADCSRA,ADSC);
}
uint16_t ADCValue()
{
		uint8_t thelow=ADCL;
		uint16_t tenbit=ADCH<<2|thelow>>6;
		//PORTD=tenbit;
		//uart_num(thelow);
		//uart_num(ADMUX&0x07);
		return(tenbit);

}

ISR(ADC_vect)
{
	uint8_t thelow=ADCL;
	uint16_t tenbit=ADCH<<2|thelow>>6;
	//PORTD=tenbit;
	
	
}