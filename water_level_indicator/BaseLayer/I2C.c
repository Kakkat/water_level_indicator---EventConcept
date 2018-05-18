#ifndef  F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/twi.h>
#include <avr/pgmspace.h>
#include "I2C.h"
#include <avr/pgmspace.h>
#define F_SCL 400000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)
uint8_t chumma[5]={0x00,0x00,0x00,0x00,0x00};

const uint8_t ssd1306xled_font6x8 []  PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // sp
	0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, // !
	0x00, 0x00, 0x07, 0x00, 0x07, 0x00, // "
	0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14, // #
	0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
	0x00, 0x62, 0x64, 0x08, 0x13, 0x23, // %
	0x00, 0x36, 0x49, 0x55, 0x22, 0x50, // &
	0x00, 0x00, 0x05, 0x03, 0x00, 0x00, // '
	0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, // (
	0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, // )
	0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, // *
	0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, // +
	0x00, 0x00, 0x00, 0xA0, 0x60, 0x00, // ,
	0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // -
	0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // .
	0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // /
	0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
	0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
	0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
	0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
	0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
	0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
	0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
	0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
	0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
	0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
	0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // :
	0x00, 0x00, 0x56, 0x36, 0x00, 0x00, // ;
	0x00, 0x08, 0x14, 0x22, 0x41, 0x00, // <
	0x00, 0x14, 0x14, 0x14, 0x14, 0x14, // =
	0x00, 0x00, 0x41, 0x22, 0x14, 0x08, // >
	0x00, 0x02, 0x01, 0x51, 0x09, 0x06, // ?
	0x00, 0x32, 0x49, 0x59, 0x51, 0x3E, // @
	0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // A
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, // B
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // C
	0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, // D
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // E
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // F
	0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A, // G
	0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, // H
	0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
	0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, // J
	0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, // K
	0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // L
	0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
	0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, // N
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, // O
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, // P
	0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
	0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // R
	0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // S
	0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // T
	0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, // U
	0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, // V
	0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, // W
	0x00, 0x63, 0x14, 0x08, 0x14, 0x63, // X
	0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // Y
	0x00, 0x61, 0x51, 0x49, 0x45, 0x43, // Z
	0x00, 0x00, 0x7F, 0x41, 0x41, 0x00, // [
	0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55, // 55
	0x00, 0x00, 0x41, 0x41, 0x7F, 0x00, // ]
	0x00, 0x04, 0x02, 0x01, 0x02, 0x04, // ^
	0x00, 0x40, 0x40, 0x40, 0x40, 0x40, // _
	0x00, 0x00, 0x01, 0x02, 0x04, 0x00, // '
	0x00, 0x20, 0x54, 0x54, 0x54, 0x78, // a
	0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, // b
	0x00, 0x38, 0x44, 0x44, 0x44, 0x20, // c
	0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, // d
	0x00, 0x38, 0x54, 0x54, 0x54, 0x18, // e
	0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, // f
	0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g
	0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, // h
	0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, // i
	0x00, 0x40, 0x80, 0x84, 0x7D, 0x00, // j
	0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // k
	0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, // l
	0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, // m
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, // n
	0x00, 0x38, 0x44, 0x44, 0x44, 0x38, // o
	0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, // p
	0x00, 0x18, 0x24, 0x24, 0x18, 0xFC, // q
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, // r
	0x00, 0x48, 0x54, 0x54, 0x54, 0x20, // s
	0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, // t
	0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, // u
	0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, // v
	0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, // w
	0x00, 0x44, 0x28, 0x10, 0x28, 0x44, // x
	0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y
	0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, // z
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, // horiz lines
};

const uint8_t ssd1306_init_sequence []   PROGMEM= {	// Initialization Sequence
	0xAE,			// Display OFF (sleep mode)
	0x20, 0b00,		// Set Memory Addressing Mode
	// 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
	// 10=Page Addressing Mode (RESET); 11=Invalid
	0xB0,			// Set Page Start Address for Page Addressing Mode, 0-7
	0xC8,			// Set COM Output Scan Direction
	0x00,			// ---set low column address
	0x10,			// ---set high column address
	0x40,			// --set start line address
	0x81, 0x3F,		// Set contrast control register
	0xA1,			// Set Segment Re-map. A0=address mapped; A1=address 127 mapped.
	0xA6,			// Set display mode. A6=Normal; A7=Inverse
	0xA8, 0x3F,		// Set multiplex ratio(1 to 64)
	0xA4,			// Output RAM to Display
	// 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
	0xD3, 0x00,		// Set display offset. 00 = no offset
	0xD5,			// --set display clock divide ratio/oscillator frequency
	0xF0,			// --set divide ratio
	0xD9, 0x22,		// Set pre-charge period
	0xDA, 0x12,		// Set com pins hardware configuration
	0xDB,			// --set vcomh
	0x20,			// 0x20,0.77xVcc
	0x8D, 0x14,		// Set DC-DC enable
	0xAF			// Display ON in normal mode
	
};
void i2c_init(void)
{
	
	TWBR = (uint8_t)TWBR_val;
	uart_num(TWBR);
}
uint8_t EOTi2c()
{

	while( !(TWCR & (1<<TWINT)) )
	{
	}

	return 1;
}


uint8_t i2c_start(uint8_t address)
{
	// reset TWI control register
	TWCR = 0;
	// transmit START condition 
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) )
	{
		
	}
	//uart_num(!(TWCR & (1<<TWINT)));
	// check if the start condition was successfully transmitted
	if((TWSR & 0xF8) != TW_START){ return 1; }
	//uart_string("hrrr");
	// load slave address into data register
	TWDR = address;
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the device has acknowledged the READ / WRITE mode
	uint8_t twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
	
	return 0;
}

uint8_t i2c_write(uint8_t data)
{
	// load data into data register
	TWDR = data;
	// start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	if( (TWSR & 0xF8) != TW_MT_DATA_ACK ){ return 1; }

	return 0;
}

uint8_t i2c_read_ack(void)
{
	
	// start TWI module and acknowledge data after reception
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); 
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	// return received data from TWDR
	return TWDR;
}

uint8_t i2c_read_nack(void)
{
	
	// start receiving without acknowledging reception
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	// return received data from TWDR
	return TWDR;
}

uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length)
{
	if (i2c_start(address | I2C_WRITE)) return 1;
	
	for (uint16_t i = 0; i < length; i++)
	{
		if (i2c_write(data[i])) return 1;
	}
	
	i2c_stop();
	
	return 0;
}

uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length)
{
	if (i2c_start(address | I2C_READ)) return 1;
	
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();
	
	i2c_stop();
	
	return 0;
}

uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{

	for (uint16_t i = 0; i < length; i++)
	{
		if (i2c_start(devaddr | 0x00)) return 1;
        i2c_write(regaddr);
		if (i2c_write(data[i])) return 1;
		i2c_stop();
	}

	

	return 0;
}
uint8_t i2c_writeRegInit(uint8_t devaddr, uint8_t regaddr, uint16_t length)
{

	for (uint16_t i = 0; i < length; i++)
	{
		if (i2c_start(devaddr | 0x00)) return 1;
		i2c_write(regaddr);
		if (i2c_write(pgm_read_byte(&ssd1306_init_sequence[i]))) return 1;
		i2c_stop();
	}

	

	return 0;
}
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	if (i2c_start(devaddr)) return 1;

	i2c_write(regaddr);

	if (i2c_start(devaddr | 0x01)) return 1;

	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();

	i2c_stop();

	return 0;
}

void i2c_stop(void)
{
	// transmit STOP condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

uint8_t ssd1036_Init()
{
	return i2c_writeRegInit(0x78,0x00,28);
}

uint8_t ssd1036_chumma()
{
	//for(uint8_t i=0;i<5;i++)
	//{
		//chumma[i]=0x00;
	//}
	// i2c_writeReg(0x78,0x40,chumma,255);
	 //i2c_writeReg(0x78,0x40,chumma,255);
	 //i2c_writeReg(0x78,0x40,chumma,255);
	 return i2c_writeReg(0x78,0x40,chumma,5);
} 

void ssd1306_char_font6x8(char ch) {
	uint8_t c = ch - 32;
	if (i2c_start(0x78 | 0x00)) return 1;
	i2c_write(0x40);
	for (uint8_t i = 0; i < 6; i++)
	{
		if (i2c_write(pgm_read_byte(&ssd1306xled_font6x8[c * 6 + i]))) return 1;//ssd1306_send_byte(pgm_read_byte(&ssd1306xled_font6x8[c * 6 + i]));
	}
	i2c_stop();
}
void ssd1306_String_font6x8(const unsigned char *SSDstring,uint8_t x, uint8_t y)
{
	ssd1306_setpos(x,y);
	while ( *SSDstring)
	{
     ssd1306_char_font6x8(*SSDstring++);
	 x=x+6;
	}
}
void ssd1306_setpos(uint8_t x, uint8_t y)
{
	if (i2c_start(0x78 | 0x00)) return 1;
	i2c_write(0x00);
	i2c_write(0xb0 + y);
	i2c_write((x & 0x0f));
	i2c_write(((x & 0xf0) >> 4) | 0x10); // | 0x10
	/* TODO: Verify correctness */	 // | 0x01
	i2c_stop();
}

void ssd1306_Rectangle(uint8_t x, uint8_t y)
{
	ssd1306_setpos(x,y);
	if (i2c_start(0x78 | 0x00)) return 1;
	i2c_write(0x40);
	for(uint16_t i=0;i<256;i++)
	{
		i2c_write(0x01);
	}
	i2c_stop();
}
void ssd1306_Fill_Rectangle(uint8_t x, uint8_t y,uint8_t data)
{
		ssd1306_setpos(x,y);
		if (i2c_start(0x78 | 0x00)) return 1;
		i2c_write(0x40);
		for(uint8_t i=0;i<data;i++)
		{
			i2c_write(0xff);
		}
		for(uint8_t i=data;i<127;i++)
		{
		  i2c_write(0x01);
		}
		i2c_stop();
}

uint8_t SSDGetByte(char SSDch,uint8_t SSDarrIndex)
{
	uint8_t c = SSDch - 32;
	return (pgm_read_byte(&ssd1306xled_font6x8[c * 6 + SSDarrIndex]));
}

void ssd1306_String_font6x8_test(const unsigned char *SSDstring,uint8_t x, uint8_t y)
{
	//ssd1306_setpos(x,y);
	
	while ( *SSDstring)
	{
		ssd1306_char_font6x8(*SSDstring++);
		x=x+6;
	}
}

ISR(TWI_vect)
{
	uart_string("INT");
	TWCR = (1<<TWINT);
}