/*
 * EepromStructure.c
 *
 * Created: 12/9/2017 12:28:21 PM
 *  Author: Nikhil
 */ 
#include "EepromStructure.h"
void Nvm_TableInit()
{
	Nvm_Table_t[0].Id=0;
	Nvm_Table_t[0].Nvm_Size=sizeof(Nvm_T_Ping);
	Nvm_Table_t[1].Id=1;
	Nvm_Table_t[1].Nvm_Size=sizeof(Nvm_T_OH);
	Nvm_Table_t[2].Id=5;
	Nvm_Table_t[2].Nvm_Size=sizeof(Nvm_T_TankOverflow);
	Nvm_Table_t[3].Id=6;
	Nvm_Table_t[3].Nvm_Size=sizeof(Nvm_T_TankOverflowLevel);
	Nvm_Table_t[4].Id=7;
	Nvm_Table_t[4].Nvm_Size=sizeof(Nvm_T_TankHeight);
}