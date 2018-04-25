#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#define I2C_READ 0x01
#define I2C_WRITE 0x00
#include <avr/pgmspace.h>
void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_writeRegInit(uint8_t devaddr, uint8_t regaddr, uint16_t length);
void i2c_stop(void);
uint8_t ssd1036_Init();
uint8_t ssd1036_chumma();
void ssd1306_setpos(uint8_t x, uint8_t y);
void ssd1306_char_font6x8(char ch);
void ssd1306_String_font6x8(const unsigned char *SSDstring,uint8_t x, uint8_t y);
void ssd1306_Rectangle(uint8_t x, uint8_t y);
void ssd1306_Fill_Rectangle(uint8_t x, uint8_t y,uint8_t data);
uint8_t EOTi2c();
uint8_t SSDGetByte(char SSDch,uint8_t SSDarrIndex);
void ssd1306_String_font6x8_test(const unsigned char *SSDstring,uint8_t x, uint8_t y);
#endif // I2C_MASTER_H