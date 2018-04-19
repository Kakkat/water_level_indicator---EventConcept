/*
 * UART.h
 *
 * Created: 8/13/2016 2:46:17 PM
 *  Author: neethu
 */ 

#include<avr/io.h>
#include "CircularQueue.h"
#include "../RTE Base/Rte_Uart.h"
#define TRUE 1
#define FALSE 0
#define CHAR_NEWLINE '\n'
#define CHAR_RETURN '\r'
#define RETURN_NEWLINE "\r\n"
#define BUFFER_SIZE 5
#define Baud 115200
#define Clock_Speed 12000000
#define MYbbr  Clock_Speed/16/Baud-1
volatile uint8_t command_ready;
volatile uint8_t Data_Count;
volatile unsigned char data_in[BUFFER_SIZE];
uint16_t  (*callbackFunction)(void);
void uart_init();
 uint16_t Callhandler(void *);
void uart_char(unsigned char uchar);
void uart_string(const unsigned char *ustring);
void uart_string1(const unsigned char *ustring);
uint8_t CheckESP_Response(const unsigned char *Data);
void uart_num(unsigned char num);
unsigned char uart_read();
void uart_delay(unsigned int delaytime);
void uart_16Uint(uint16_t num);
volatile unsigned char r;
uint8_t PopInterface(unsigned char *);
volatile uint8_t event;
uint8_t CheckUartReadyToSend();
void SendByte(unsigned char dat);
void ConfigureCallBack(uint16_t  (*callbackarg)(void));
CbuffState_t BufferEmpty();
//static void(*PrintOut)(const unsigned char*)=uart_string;

