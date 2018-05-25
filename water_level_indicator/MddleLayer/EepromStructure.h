/*
 * EepromStructure.h
 *
 * Created: 12/2/2017 12:47:51 PM
 *  Author: Nikhil
 */ 


#ifndef EEPROMSTRUCTURE_H_
#define EEPROMSTRUCTURE_H_
#include <avr/io.h>
void Nvm_TableInit();
typedef struct
{
	uint8_t LargestValue;
}Nvm_T_Ping;

typedef struct
{
	uint32_t OperatingHours;
}Nvm_T_OH;

typedef struct
{
	uint8_t Tank;
}Nvm_T_TankOverflow;

typedef struct
{
	uint8_t Threshold;
}Nvm_T_TankOverflowLevel;

typedef struct
{
	uint8_t TankHeight;
}Nvm_T_TankHeight;

typedef enum
{
	Nvm_Ping,
	Nvm_OH,
	Nvm_TankOverflow,
	Nvm_TankOverflowLevel,
	Nvm_TankHeight,
	Nvm_EndOflist
}Nvm_Id;

typedef struct
{
	Nvm_Id Id;
	uint8_t	Nvm_Size;
}Nvm_Table;

Nvm_Table Nvm_Table_t[Nvm_EndOflist];
#endif /* EEPROMSTRUCTURE_H_ */