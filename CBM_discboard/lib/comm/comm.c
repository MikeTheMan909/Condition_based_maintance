#include "comm.h"
#include "config.h"
const char *commmod = "comm";
#define comm_print_debug(str) print_debug(commmod, str)

#ifdef ENABLE_DEBUG
#define COMM_DEBUG 1
#endif

void comm_request(float temperature, uint16_t X,uint16_t Y,uint16_t Z){
	//make sensor data ready for send
	union convert f;
	uint8_t temp[50];
	f.t = temperature;
	temp[0] = SENSOR_ID;
	memcpy(&temp[1], &c.send_flag, 1);
	memcpy(&temp[2], &f.b, 4);
	memcpy(&temp[6], &X, 2);
	memcpy(&temp[8], &Y, 2);
	memcpy(&temp[10], &Z, 2);

#ifdef COMM_DEBUG
	comm_print_debug("data ready");
	comm_print_debug("data:");
	comm_print_debug(temp);
#endif
	SPSGRF_StartTx((uint8_t *)temp,12);
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
