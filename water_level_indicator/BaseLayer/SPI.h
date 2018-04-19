/*
 * SPI.h
 *
 * Created: 8/8/2016 11:25:53 PM
 *  Author: neethu
 */ 

#include <avr/io.h>
#ifndef SPI_H_
#define SPI_H_
//uint8_t ClockSpeed1[8]={0,1,2,3,0,1,2,3};
typedef enum 
{
Divby0,
Divby2,
Divby4,
Divby8,
Divby16,
Divby32,
Divby64,
Divby128,
Endoflist
} SPI_CLK_Divider;



void spi_init_master (void);
void spi_dataorder(uint8_t data );
void spi_clockspeed(SPI_CLK_Divider clock);
void spi_clockphase(uint8_t data);
unsigned char spi_tranceiver (unsigned char data);

#endif /* SPI_H_ */