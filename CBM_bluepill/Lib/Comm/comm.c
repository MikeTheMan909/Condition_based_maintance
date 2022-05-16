/*
	Communication protocol
	byte 0 - Sensor id;
	byte 1 - 0 Command; see enum commands
			 1 Datapkt;
	byte 2 - send flag; see enum send_flag
	byte 3 - temperature;
	byte 4 - temperature;
	byte 5 - temperature;
	byte 6 - temperature;
	byte 7 - x value;
	byte 8 - x value;
	byte 9 - y value;
	byte 10 - y value;
	byte 11 - z value;
	byte 12 - z value;
*/


#include "comm.h"

const char *commmod = "comm";
#define comm_print_debug(str) print_debug(commmod, str)

#ifdef ENABLE_DEBUG
#define COMM_DEBUG 1
#endif

uint8_t gateway_received = 0;
uint8_t message_send = 0;

void comm_builddata(uint8_t *temp, float *value, uint8_t placement){
	union convert f;
	f.t = *value;
	printf("%f",*value);
	int i = 0;
	for(i=0; i<4; i++){
		printf("%02x ",f.b[i]);
		temp[placement + i] = f.b[i];
	}
}

uint8_t comm_request(uint8_t *temp, struct sensor_values sensor_value){
	//make sensor data ready for send
	int i;
	VECTOR *ptr_data = 0;
	ptr_data = &sensor_value.acc.x;

	memset(temp,0,200);
	temp[0] = sensor_id;
	temp[1] = DATAPKT;

	memcpy(&temp[2], &c.send_flag, 1);
	comm_builddata(temp,&sensor_value.temperature, 3);

	for(i=0; i<4;i++){
		comm_builddata(temp,&ptr_data->rms, 7+(12*i));
		comm_builddata(temp,&ptr_data->peak, 11+(12*i));
		comm_builddata(temp,&ptr_data->crest, 15+(12*i));
		ptr_data++;
	}
	ptr_data = &sensor_value.velo.x;
	for(i=0; i<4;i++){
		comm_builddata(temp,&ptr_data->rms, 55+(12*i));
		comm_builddata(temp,&ptr_data->peak, 59+(12*i));
		comm_builddata(temp,&ptr_data->crest, 63+(12*i));
		ptr_data++;
	}
	ptr_data = &sensor_value.disp.x;
	for(i=0; i<4;i++){
		comm_builddata(temp,&ptr_data->rms, 67+(8*i));
		comm_builddata(temp,&ptr_data->peak, 71+(8*i));
		ptr_data++;
	}
	message_send = 1;
	return 13;
}

void comm_command(uint8_t cmd, uint8_t address){
	uint8_t data[20];
	uint8_t enc_data[16];
	int i = 3;
	if(cmd == GATEWAY_CHECK){
		SpiritPktBasicSetDestinationAddress(GATEWAY_ADDRESS);
		data[0] = sensor_id;
		data[1] = COMMAND;
		if(cmd == GATEWAY_CHECK){
			data[2] = GATEWAY_CHECK;
		}
		if(cmd == SENSORS_CHECK){
			SpiritPktBasicSetDestinationAddress(BROADCAST_ADDRESS);
			data[2] = SENSORS_CHECK;
			data[3] = nodes.gateway_connected;
			i++;
		}
		if(cmd == CONV_TO_CONPOINT){
			SpiritPktBasicSetDestinationAddress(address);
			data[2] = CONV_TO_CONPOINT;
		}
		comm_encrypt(data, i ,enc_data);
		comm_send(enc_data);
	}
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
	uint8_t dataframe[20];
	uint8_t enc_data[20];

	if(data[1] == DATAPKT){
#ifdef COMM_DEBUG
		memset(&tmp, 0, 50);

		sprintf(tmp, "Device id: %d \n\r", data[0]);
		comm_print_debug(tmp);
		sprintf(tmp, "send flag: %d \n\r", data[2]);
		comm_print_debug(tmp);

		memcpy(&f.b, &data[3], 4);
		sprintf(tmp, "temperature: %f\n\r", f.t);
		comm_print_debug(tmp);

		memcpy(&tempvalue, &data[7],2);
		sprintf(tmp, "x value: %d\n\r", tempvalue);
		comm_print_debug(tmp);

		memcpy(&tempvalue, &data[9],2);
		sprintf(tmp, "y value: %d\n\r", tempvalue);
		comm_print_debug(tmp);

		memcpy(&tempvalue, &data[11],2);
		sprintf(tmp, "z value: %d\n\r", tempvalue);
		comm_print_debug(tmp);
#endif
		message_send = 1;
		comm_encrypt(data, 13 ,enc_data);
		comm_send(enc_data);

	}else if(data[1] == COMMAND){
		if(data[2] == SENSORS_CHECK){
			comm_print_debug("a sensor is checking whos in range");
			nodes.node_in_range++;
			nodes.node[nodes.node_in_range].node_id = data[0];
			nodes.node[nodes.node_in_range].node_gw_connected = data[3];
			dataframe[0] = MY_ADDRESS_CFG;
			dataframe[1] = COMMAND;
			dataframe[2] = ACK;
			dataframe[3] = nodes.gateway_connected;
			comm_encrypt(dataframe, 4 ,enc_data);
			comm_send(enc_data);
			if(nodes.gateway_connected == 0 && nodes.node[nodes.node_in_range].node_gw_connected == 1){

			}
		}
		if(data[2] == CONV_TO_CONPOINT){
			dataframe[0] = MY_ADDRESS_CFG;
			dataframe[1] = COMMAND;
			dataframe[2] = ACK;
			comm_encrypt(dataframe, 3 ,enc_data);
			comm_send(enc_data);
			comm_print_debug("Sensor asked me to send their messages to the gateway");
		}
		if(data[2] == ACK){
			gateway_received = 1;
			comm_print_debug("got ack from gateway");
		}
		if(message_send == 1 && gateway_received == 0){
			message_send = 0;
			HAL_Delay(1000);
			comm_print_debug("message didn't arrive");
			comm_send(last_message);
		}
	}else{
		//ERR
	}
}

void comm_send(uint8_t * data){
	SpiritPktBasicSetDestinationAddress(nodes.destination_node);
	SPSGRF_StartTx(data,16);
	memcpy(last_message, data , 16);
}

void comm_encrypt(uint8_t *data, uint8_t len ,uint8_t *enc_data){
	char temp[50];
	char str[50];
#ifdef DEBUG_ENCRYPTION
	memset(temp,0, 50);
	strcpy(temp, "data:");
	for(int i = 0; i<len; i++){
	sprintf(str,"%X", data[i]);
	strcat(temp,str);
	}
	comm_print_debug(temp);
#endif

	SpiritAesWriteDataIn(data , len);
	SpiritAesExecuteEncryption();
	while(!irqStatus.IRQ_AES_END);
	SpiritAesReadDataOut(enc_data , 16);

#ifdef DEBUG_ENCRYPTION
	memset(temp,0, 50);
	strcpy(temp, "data:");
	for(int i = 0; i<16; i++){
	  sprintf(str,"%X", enc_data[i]);
	  strcat(temp,str);
	}
	comm_print_debug(temp);
#endif
}

void comm_decrypt(uint8_t *data){
	uint8_t rxdata[20];
	SPSGRF_GetRxData(rxdata);
	char temp[50];
	char str[50];

	SpiritAesWriteDataIn(rxdata, 16);
	SpiritAesDeriveDecKeyExecuteDec();
	while(!irqStatus.IRQ_AES_END);

	SpiritAesReadDataOut(data , 13);
	#ifdef DEBUG_ENCRYPTION
	memset(temp,0, 50);
	strcpy(temp, "data:");
	for(int i = 0; i<12; i++){
		sprintf(str,"%X", data[i]);
		strcat(temp,str);
	}
	comm_print_debug(temp);
	#endif
}

void comm_start(){
	SPSGRF_Init();
	SpiritAesWriteKey(c.key);
	//mesh_init();
}
