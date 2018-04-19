
#include "pinout.h"
#include <avr/pgmspace.h>
#define portOutRegister(P) ( (volatile uint8_t *)( pgm_read_word( Port + (P))) )
#define portModeRegister(P) ( (volatile uint8_t *)( pgm_read_word( DDR + (P))) )
#define portInputRegister(P) ( (volatile uint8_t *)( pgm_read_word( PIN + (P))) )
#define Bit_Is_Set(p,pos) ((pos>>p)&0x01)
const uint16_t Port[] PROGMEM={&PORTB,&PORTC,&PORTD };
const uint16_t DDR[] PROGMEM={&DDRB,&DDRC,&DDRD };
const uint16_t PIN[] PROGMEM={&PINB,&PINC,&PIND };
//static Port PORTB_OUT;

void PinOutConfig(uint8_t State,Pin Pin_s,Ports Port_s)
{
   volatile uint8_t *Reg;
   Reg=portModeRegister(Port_s);
  if(State==1)
  {
	  
	  *Reg|=1<<Pin_s;
  }
  else 
  {
	  *Reg&=~(1<<Pin_s);
  } 
}
void PinOutput(uint8_t Out,Pin Pin_s,Ports Port_s )
{
    volatile uint8_t *out;
	out=portOutRegister(Port_s);
	    if(Out==ON)
		{
			*out=*out|(1<<Pin_s);
		}
		else
		{
			*out&=~(1<<Pin_s);
		}
	    
}


void PinValue(uint8_t *Value,Pin Pin_s,Ports Port_s)
{
	    volatile uint8_t *out;
	    out=portInputRegister(Port_s);
		
		//*Value=bit_is_clear(*out,Pin_s);
		*Value=bit_is_set(*out,Pin_s);
	
}