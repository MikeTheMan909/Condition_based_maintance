#include "config.h"
#include "stdio.h"
#include <string.h>

uint8_t sensor_id = 0xAA;

struct config config(){

	struct config t;
	uint8_t flag = 0;
	set_flag(flag,SEND_TEMP_FLAG);
	//set_flag(flag,SEND_CO2_FLAG);
	set_flag(flag,SEND_VIBRATION_FLAG);

	t.send_flag = flag;
	memcpy(t.key,"HALLO_adwFegadwa", 16);

	return t;
}
