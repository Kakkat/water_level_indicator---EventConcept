/*
 * ESP8266.h
 *
 * Created: 10/30/2016 3:32:53 PM
 *  Author: Nikhil
 */ 


#ifndef ESP8266_H_
#define ESP8266_H_
#include "..\MddleLayer\SignalHandler.h"

typedef struct
{
	unsigned char *ustring;
	unsigned char *Response;
	uint8_t state;
	uint8_t MatchCounter;
	uint8_t ResposeLength;
	uint16_t WaitTime;
	
}Esp_Commands;

typedef struct
{
	unsigned char Connection_flag:1;
	unsigned char Disconnect_Flag:1;
	unsigned char Server_flag:1;
	unsigned char Request_Flag:1;
}ESP_flags_t;

typedef struct
{
	unsigned char *strp;
	uint8_t  Purpose;
}ESP_DataRead_t;

typedef enum
{
	Wifi_Command,
	Connection_Wait,
	Mode_Command,
	Mux_Command,
	Server_Command,
	GetIp_Command,
	Wait_Command,
	Send_Command,
	Send_Data,
	CloseChannel_Command,
	Disconnect_Command,
	Uart_command,
	Cmd_EndofList
}ESP_CommandIndex;
typedef enum
{
initiated,
connected,
closed		
}ESP_PortConnection;
typedef enum
{
  ESP_CmdSndOK,
  ESP_CmdSndBusy,
  ESP_CmdSNDFailed,
}ESPRetVal;
unsigned char espdata;
static ESP_flags_t ESP_flags;
uint16_t ESPreadvalue(void *);
ESPRetVal CommandSend(ESP_CommandIndex);
ESPRetVal Connect_ESP();
ESPRetVal RequestWait();
void printBuffer();
void ESP_Init();
ESPRetVal SendData(uint8_t);
ESPRetVal WifiDisconnectCheck();
ESPRetVal ConnectCommand();
volatile uint8_t Sendstatus;
uint16_t EspGlobalCounter(uint8_t state);
uint8_t CheckInput();
uint8_t enable();
volatile uint8_t UartEvents;
void Uart_DebugMode(void);
uint8_t ESPpop(char *Bytex);
void ESPCallBack(void *fillcallback);
#endif /* ESP8266_H_ */