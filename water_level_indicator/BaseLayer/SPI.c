/*
 * SPI.c
 *
 * Created: 8/8/2016 11:26:18 PM
 *  Author: neethu
 */ 
#include "SPI.h"
uint8_t ClockSpeed1[Endoflist]={0,1,2,3,0,1,2,3};
	
void spi_init_master (void)
{
	// Set MOSI, SCK as Output
	DDRB = DDRB|(1<<5)|(1<<3)|(1<<2);
	// Enable SPI, Set as Master
	//Prescaler: Fosc/16, Enable Interrupts
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void spi_dataorder(uint8_t data )
{
	
	SPCR |=(data<<DORD);//1 lsb first
}

void spi_clockspeed(SPI_CLK_Divider clock)
{
	
	if(clock==2||clock==8||clock==32||clock==64)
	{
		
		SPCR =SPCR|1<<ClockSpeed1[clock];//ClockSpeed1[clock];//1 for fosc/4,rest till 4
		SPSR=SPSR|0x01;
	}
	else if(clock==4||clock==16||clock==64||clock==128)
	{
		
		SPCR =SPCR|clock;	
	}
	
	
}

void spi_clockphase(uint8_t data)
{
	
	
	SPCR|=1<<CPOL;//1 to 4
	
}
unsigned char spi_tranceiver (unsigned char data)
{
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF) ));
	
	// Return received data
	return(SPDR);
}