#include "config.h"

struct config c;

uint8_t config(){
	uint8_t flag = 0;
	set_flag(flag,SEND_TEMP_FLAG);
	set_flag(flag,SEND_CO2_FLAG);
	set_flag(flag,SEND_VIBRATION_FLAG);
	return flag;
}
