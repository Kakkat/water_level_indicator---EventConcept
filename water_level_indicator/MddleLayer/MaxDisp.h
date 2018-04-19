/*
 * MaxDisp.h
 *
 * Created: 9/17/2016 5:16:49 AM
 *  Author: neethu
 */ 

#include <avr/io.h>

#ifndef MAXDISP_H_
#define MAXDISP_H_


#define POWERON 0X0C
#define DECODEMODE 0X09
#define INTENSITY 0X0A
#define SCANLIMIT 0X0B
#define DIGIT7 0X08
#define DIGIT6 0X07
#define DIGIT5 0X06
#define DIGIT4 0X05
#define DIGIT3 0X04
#define DIGIT2 0X03
#define DIGIT1 0X02
#define DIGIT0 0X01

typedef enum
{
  Digit0,
  Digit1,
  Digit2,
  Digit3,
  Digit4,
  Digit5,
  Digit6,
  Digit7,
  Digit8,
  Digit9,
}Digits;
void WriteMax(uint8_t address,uint8_t data);
void InitMax();
void ScanlimitExpand(uint8_t num);
void DispDigits(uint16_t num);
void DispChar(uint16_t num,uint8_t MaxDispPos);
#endif /* MAXDISP_H_ */