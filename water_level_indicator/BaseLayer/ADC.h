/*
 * ADC.h
 *
 * Created: 8/6/2016 8:44:49 PM
 *  Author: neethu
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef ADC_H_
#define ADC_H_
void adc_init(void);
#include <avr/sfr_defs.h>
void adc_read(unsigned char ch);
uint16_t ADCValue();
uint8_t ADC_State();

#endif /* ADC_H_ */