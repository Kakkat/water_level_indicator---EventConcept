/*
 * StringOp.c
 *
 * Created: 10/23/2016 10:42:26 AM
 *  Author: Nikhil
 */ 
#include "StringOp.h"

uint8_t Stringlength(const unsigned char *ustring,unsigned char End )
{
	uint8_t count=0;
	//unsigned char value;
	while(ustring[count]!='\n')
	{
		count++;
	}
	return (count);
}

void AddSubString(unsigned char *ustring,unsigned char *Sub,uint16_t pos )
{
	ustring[pos]='"';
	uint16_t count =0;
	while (Sub[count]!='\n')
	{
		pos++;
		ustring[pos]=Sub[count];
		count++;		
	}
	ustring[pos]=Sub[count];
}

void ReplaceSpace(unsigned char *ustring,unsigned char *Sub,uint8_t pos)
{
	 uint16_t count =0;
	 
	 while (ustring[count]!='\n')
	 {
		 if(ustring[count]==' ')
		 {
			 ustring[count]=Sub[pos+1];
		 }
		 count++;
	 }
}