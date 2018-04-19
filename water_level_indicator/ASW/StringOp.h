/*
 * StringOp.h
 *
 * Created: 10/23/2016 10:43:03 AM
 *  Author: Nikhil
 */ 

#include <avr/io.h>

#ifndef STRINGOP_H_
#define STRINGOP_H_

uint8_t Stringlength(const unsigned char *ustring,unsigned char End );
void AddSubString( unsigned char *ustring,unsigned char *Sub,uint16_t pos );
void ReplaceSpace(unsigned char *ustring,unsigned char *Sub,uint8_t pos);


#endif /* STRINGOP_H_ */