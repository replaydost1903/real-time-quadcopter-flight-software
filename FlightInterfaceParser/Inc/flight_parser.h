#ifndef INC_FLIGHT_PARSER_H_
#define INC_FLIGHT_PARSER_H_

#include "main.h"

//array length define function
#define _arraylength(_Array) (sizeof(_Array) / sizeof(_Array[0]))

/*Define Definitions*/
#define BUFFER_SIZE	10					/*!< Number of bytes to be sent to rs485 >!*/
#define POLYNOMIAL_VALUE 0x03FD			/*!< CRC Polynomial Value >!*/

typedef struct
{
	uint8_t PID_COMMAND 	:1;
	uint8_t YAW_COMMAND 	:2;
	uint8_t PITCH_COMMAND 	:3;

}FlightCommandState_t;

typedef enum
{
	INTERFACE_BUSY = 0,
	INTERFACE_OK   = 1,
	INTERFACE_ERROR = 2

}FlightInterfaceState_t;

struct FlightCommandInterface_t
{
	uint8_t ui8index;
	uint8_t ui8buffer[BUFFER_SIZE];
	uint16_t ui16crc;
	uint8_t receive_data;
	FlightInterfaceState_t state;
//	crc_check crc;

};

void FligthInterfaceInit(struct FlightCommandInterface_t*);
void FligthInterfacePacketParser(struct FlightCommandInterface_t*);
void FligthInterfaceCommandParser(struct FlightCommandInterface_t*);

#endif /* INC_FLIGHT_PARSER_H_ */







