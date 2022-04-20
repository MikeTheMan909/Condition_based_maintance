

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "stdint.h"

#define set_flag(r,f) (r |= f)
// reset flag function: r - register to change, f - flag position
#define reset_flag(r,f) (r &= ~f)

enum send_flag {
	SEND_TEMP_FLAG		= 1 << 0,
	SEND_CO2_FLAG		= 1 << 1,
	SEND_VIBRATION_FLAG	= 1 << 2
};

struct config {
	uint8_t send_flag;
	uint8_t key[16];
};
extern struct config c;
uint8_t config();

#define MY_ADDRESS_CFG		0xAA
#define GATEWAY_ADDRESS	0xAA
#define SENSOR_ID 1
#endif /* INC_CONFIG_H_ */
