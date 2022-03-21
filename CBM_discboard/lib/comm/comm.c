#include "comm.h"
#include "string.h"
const char *commmod = "comm";
#define comm_print_debug(str) print_debug(commmod, str)

#ifdef ENABLE_DEBUG
#define COMM_DEBUG 1
#endif
void comm_request(char *data){
	//make sensor data ready for send
#ifdef COMM_DEBUG
	comm_print_debug("data ready");
	comm_print_debug("data:");
	comm_print_debug(data);
#endif
	SPSGRF_StartTx((uint8_t *)data,strlen(data));
}
