/*
 * ADCread.h
 *
 * Created: 8/6/2016 8:54:41 PM
 *  Author: neethu
 */ 



#ifndef ADCREAD_H_
#define ADCREAD_H_
#include <avr/io.h>

typedef struct
{
	uint8_t channel;
	uint8_t State;
	uint8_t filled;
	
}ChannelBuffer;

uint16_t ReadEveryValueADC(void);
uint16_t GetADC_Value(uint16_t ADC_ChannelAndValue);

#endif /* ADCREAD_H_ */