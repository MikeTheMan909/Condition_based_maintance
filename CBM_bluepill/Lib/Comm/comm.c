#include "comm.h"

const char *commmod = "comm";
#define comm_print_debug(str) print_debug(commmod, str)

#ifdef ENABLE_DEBUG
#define COMM_DEBUG 1
#endif

void comm_request(uint8_t *temp, float temperature, uint16_t X,uint16_t Y,uint16_t Z){
	//make sensor data ready for send
	union convert f;

	char tmp[50];
	f.t = temperature;
	temp[0] = SENSOR_ID;
	memcpy(&temp[1], &c.send_flag, 1);
	memcpy(&temp[2], &f.b, 4);
	memcpy(&temp[6], &X, 2);
	memcpy(&temp[8], &Y, 2);
	memcpy(&temp[10], &Z, 2);

#ifdef COMM_DEBUG
	sprintf(tmp, "temperature: %f", temperature);
	comm_print_debug(tmp);
	sprintf(tmp, "x value: %d", X);
	comm_print_debug(tmp);
	sprintf(tmp, "y value: %d", Y);
	comm_print_debug(tmp);
	sprintf(tmp, "z value: %d", Z);
	comm_print_debug(tmp);
	comm_print_debug("data ready");
#endif
}

void comm_request_big(uint16_t X[10], uint16_t Y[10], uint16_t Z[10], uint16_t size){
	uint8_t temp[MAX_BUFFER_LEN];
	int i = 0;
	int k = 0;
	if((size*3) > MAX_BUFFER_LEN){
		int send_amount = (size*3)/MAX_BUFFER_LEN;
		int half;
		half = (size*3) % i;
		for(i = 0; i < send_amount; i++){
			for(k = 0; k < MAX_BUFFER_LEN/3; k++){
				memcpy(&temp[0*k], &X[k + (MAX_BUFFER_LEN/3 *i)],2);
				memcpy(&temp[2*k], &Y[k + (MAX_BUFFER_LEN/3 *i)],2);
				memcpy(&temp[4*k], &Z[k + (MAX_BUFFER_LEN/3 *i)],2);
			}
			SPSGRF_StartTx((uint8_t *)temp,(MAX_BUFFER_LEN));
			HAL_Delay(200);
		}
		if(half){

		}

	}else{
	 for(i = 0; i<MAX_BUFFER_LEN/3; i++){
		 memcpy(&temp[0*i], &X[i],2);
		 memcpy(&temp[2*i], &Y[i],2);
		 memcpy(&temp[4*i], &Z[i],2);
	 }
	 SPSGRF_StartTx((uint8_t *)temp,(size*3));
	}
}

void comm_received(uint8_t *data){
	char tmp[50];
	union convert f;
	uint16_t tempvalue;
	memset(&tmp, 0, 50);

	sprintf(tmp, "Device id: %d \n\r", data[0]);
	comm_print_debug(tmp);
	sprintf(tmp, "send flag: %d \n\r", data[1]);
	comm_print_debug(tmp);

	memcpy(&f.b, &data[2], 4);
	sprintf(tmp, "temperature: %f\n\r", f.t);
	comm_print_debug(tmp);

	memcpy(&tempvalue, &data[6],2);
	sprintf(tmp, "x value: %d\n\r", tempvalue);
	comm_print_debug(tmp);

	memcpy(&tempvalue, &data[8],2);
	sprintf(tmp, "y value: %d\n\r", tempvalue);
	comm_print_debug(tmp);

	memcpy(&tempvalue, &data[10],2);
	sprintf(tmp, "z value: %d\n\r", tempvalue);
	comm_print_debug(tmp);
}

void comm_send(uint8_t * data){
	SPSGRF_StartTx((uint8_t *)&data,12);
}
