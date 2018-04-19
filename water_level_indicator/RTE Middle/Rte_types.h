/*
 * Rte_types.h
 *
 * Created: 3/31/2017 8:24:39 PM
 *  Author: Nikhil
 */ 


#ifndef RTE_TYPES_H_
#define RTE_TYPES_H_
#include <avr/io.h>
typedef struct  
{
	const unsigned char *Ustring;
	uint8_t pos;
}UartBuffer;

typedef struct
{
	const unsigned char *Ustring;
	uint8_t State;
}UartOutBuffer;

typedef enum
{
	AL_CmdOk,
	Al_CmdWriting,
	AL_CmdNotOk
	
}Cmd_State;

#endif /* RTE_TYPES_H_ */