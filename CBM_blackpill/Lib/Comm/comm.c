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
#define comm_printf_debug(format,...) \
	printf_debug(commmod, format, ##__VA_ARGS__)
#ifdef ENABLE_DEBUG
#define COMM_DEBUG 1
#endif

uint8_t gateway_received = 0;
uint8_t message_send = 0;

void comm_builddata(uint8_t *temp, float *value, uint8_t placement, uint8_t type)
{
//	comm_printf_debug("Value: %f", *value);
	uint16_t int_conv = 0;
	if(type == 1){
		int_conv = *value/ ACC_CONVERTION;

	}
	if(type == 2){
		int_conv = *value/ VELO_CONVERTION;
	}
	if(type == 3){
		int_conv = *value/ DISP_CONVERTION;
	}
//	comm_printf_debug("Value converted: %d", int_conv);
	memset(&temp[placement],(int_conv >>(8)),1);
	memset(&temp[placement+1],(int_conv >>(8*0)),1);
}

uint8_t comm_request(uint8_t *temp, struct sensor_values sensor_value)
{
	//make sensor data ready for send
	int i;
	char tmp[150];
	char chr[300];
	union convert f;
	VECTOR *ptr_data = 0;
	ptr_data = &sensor_value.acc.x;
	f.t = sensor_value.temperature;
	memset(temp,0,200);
	temp[0] = sensor_id;
	temp[1] = DATAPKT;

	for(i= 2; i< 7; i++){
		temp[i] = f.b[i-2];
	}

	for(i=0; i<3;i++){
		comm_builddata(temp,&ptr_data->rms, 7+(6*i),1);
		comm_builddata(temp,&ptr_data->peak, 9+(6*i),1);
		comm_builddata(temp,&ptr_data->crest, 11+(6*i),1);
		ptr_data++;
	}
	ptr_data = &sensor_value.velo.x;
	for(i=0; i<3;i++){
		comm_builddata(temp,&ptr_data->rms, 25+(6*i),2);
		comm_builddata(temp,&ptr_data->peak, 27+(6*i),2);
		comm_builddata(temp,&ptr_data->crest,29+(6*i),2);
		ptr_data++;
	}
	ptr_data = &sensor_value.disp.x;
	for(i=0; i<3;i++){
		comm_builddata(temp,&ptr_data->rms, 43+(4*i),3);
		comm_builddata(temp,&ptr_data->peak, 45+(4*i),3);
		ptr_data++;
	}
	for(i=0; i<55;i++){
		sprintf(tmp,"%02x",temp[i]);
		strcat(chr, tmp);
	}
	comm_printf_debug(chr);
	message_send = 1;
	return 55;
}

void comm_command(uint8_t cmd, uint8_t address)
{
	uint8_t data[20];
	uint8_t enc_data[16];
	int i = 3;
	if(cmd == GATEWAY_CHECK)
	{
		SpiritPktBasicSetDestinationAddress(GATEWAY_ADDRESS);
		data[0] = sensor_id;
		data[1] = COMMAND;
		if(cmd == GATEWAY_CHECK)
		{
			data[2] = GATEWAY_CHECK;
		}
		if(cmd == SENSORS_CHECK)
		{
			SpiritPktBasicSetDestinationAddress(BROADCAST_ADDRESS);
			data[2] = SENSORS_CHECK;
			data[3] = nodes.gateway_connected;
			i++;
		}
		if(cmd == CONV_TO_CONPOINT)
		{
			SpiritPktBasicSetDestinationAddress(address);
			data[2] = CONV_TO_CONPOINT;
		}
		comm_encrypt(data, i ,enc_data);
		comm_send(enc_data,i,GATEWAY_ADDRESS);
	}
}


void comm_request_big(uint16_t X[10], uint16_t Y[10], uint16_t Z[10], uint16_t size){
	uint8_t temp[MAX_BUFFER_LEN];
	int i = 0;
	int k = 0;
	if((size*3) > MAX_BUFFER_LEN)
	{
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
		if(half)
		{

		}

	}else
	{
	 for(i = 0; i<MAX_BUFFER_LEN/3; i++){
		 memcpy(&temp[0*i], &X[i],2);
		 memcpy(&temp[2*i], &Y[i],2);
		 memcpy(&temp[4*i], &Z[i],2);
	 }
	 SPSGRF_StartTx((uint8_t *)temp,(size*3));
	}
}


void comm_received(uint8_t *data, struct sensor_values *sensordata)
{
//	char tmp[50];
	union convert f;
	uint16_t tempvalue;
//	uint8_t dataframe[20];
//	uint8_t enc_data[20];
	VECTOR *ptr_xyz = 0;
	ptr_xyz = &sensordata->acc.x;
	for(int i= 2; i< 7; i++)
	{
		f.b[i-2]= data[i];
	}
	sensordata->temperature = f.t;
	if(data[1] == DATAPKT){
		for(int i=0; i<3; i++)
		{
			tempvalue = data[7 + (6*i)] << 8 | data[8 + (6*i)] << 0;
			ptr_xyz->rms = tempvalue * ACC_CONVERTION;
			tempvalue = data[9 + (6*i)] << 8 | data[10 + (6*i)] << 0;
			ptr_xyz->peak = tempvalue * ACC_CONVERTION;
			tempvalue = data[11 + (6*i)] << 8 | data[12 + (6*i)] << 0;
			ptr_xyz->crest = tempvalue * ACC_CONVERTION;

			ptr_xyz++;

		}
		ptr_xyz = &sensordata->velo.x;
		for(int i=0; i<3; i++)
		{
			tempvalue = data[25 + (6*i)] << 8 | data[26 + (6*i)] << 0;
			ptr_xyz->rms = tempvalue * VELO_CONVERTION;
			tempvalue = data[27 + (6*i)] << 8 | data[28 + (6*i)] << 0;
			ptr_xyz->peak = tempvalue * VELO_CONVERTION;
			tempvalue = data[29 + (6*i)] << 8 | data[30 + (6*i)] << 0;
			ptr_xyz->crest = tempvalue * VELO_CONVERTION;

			ptr_xyz++;

		}
		ptr_xyz = &sensordata->disp.x;
		for(int i=0; i<3; i++)
		{
			tempvalue = data[43 + (4*i)] << 8 | data[44 + (4*i)] << 0;
			ptr_xyz->rms = tempvalue * DISP_CONVERTION;
			tempvalue = data[45 + (4*i)] << 8 | data[46 + (4*i)] << 0;
			ptr_xyz->peak = tempvalue * DISP_CONVERTION;
			ptr_xyz++;
		}
	}
	comm_printf_debug("value temperature = %f", sensordata->temperature);
	comm_printf_debug("value x acc rms = %f", sensordata->acc.x.rms);
	comm_printf_debug("value x acc peak= %f", sensordata->acc.x.peak);
	comm_printf_debug("value x acc crest = %f", sensordata->acc.x.crest);
	comm_printf_debug("value y acc rms = %f", sensordata->acc.y.rms);
	comm_printf_debug("value y acc peak= %f", sensordata->acc.y.peak);
	comm_printf_debug("value y acc crest= %f", sensordata->acc.y.crest);
	comm_printf_debug("value z acc rms= %f", sensordata->acc.z.rms);
	comm_printf_debug("value z acc peak= %f", sensordata->acc.z.peak);
	comm_printf_debug("value z acc crest = %f", sensordata->acc.z.crest);

	comm_printf_debug("value x velo rms= %f", sensordata->velo.x.rms);
	comm_printf_debug("value x velo peak= %f", sensordata->velo.x.peak);
	comm_printf_debug("value x velo crest= %f", sensordata->velo.x.crest);
	comm_printf_debug("value y velo rms= %f", sensordata->velo.y.rms);
	comm_printf_debug("value y velo peak= %f", sensordata->velo.y.peak);
	comm_printf_debug("value y velo crest= %f", sensordata->velo.y.crest);
	comm_printf_debug("value z velo rms= %f", sensordata->velo.z.rms);
	comm_printf_debug("value z velo peak= %f", sensordata->velo.z.peak);
	comm_printf_debug("value z velo crest= %f", sensordata->velo.z.crest);

	comm_printf_debug("value x disp rms= %f", sensordata->disp.x.rms);
	comm_printf_debug("value x disp peak= %f", sensordata->disp.x.peak);
	comm_printf_debug("value y disp rms= %f", sensordata->disp.y.rms);
	comm_printf_debug("value y disp peak= %f", sensordata->disp.y.peak);
	comm_printf_debug("value z disp rms= %f", sensordata->disp.z.rms);
	comm_printf_debug("value z disp peak= %f", sensordata->disp.z.peak);
//		message_send = 1;
//		comm_encrypt(data, 13 ,enc_data);
//		comm_send(enc_data,13);
//
//	}else if(data[1] == COMMAND){
//		if(data[2] == SENSORS_CHECK){
//			comm_print_debug("a sensor is checking whos in range");
//			nodes.node_in_range++;
//			nodes.node[nodes.node_in_range].node_id = data[0];
//			nodes.node[nodes.node_in_range].node_gw_connected = data[3];
//			dataframe[0] = MY_ADDRESS_CFG;
//			dataframe[1] = COMMAND;
//			dataframe[2] = ACK;
//			dataframe[3] = nodes.gateway_connected;
//			comm_encrypt(dataframe, 4 ,enc_data);
//			comm_send(enc_data,4);
//			if(nodes.gateway_connected == 0 && nodes.node[nodes.node_in_range].node_gw_connected == 1){
//
//			}
//		}
//		if(data[2] == CONV_TO_CONPOINT){
//			dataframe[0] = MY_ADDRESS_CFG;
//			dataframe[1] = COMMAND;
//			dataframe[2] = ACK;
//			comm_encrypt(dataframe, 3 ,enc_data);
//			comm_send(enc_data,3);
//			comm_print_debug("Sensor asked me to send their messages to the gateway");
//		}
//		if(data[2] == ACK){
//			gateway_received = 1;
//			comm_print_debug("got ack from gateway");
//		}
//		if(message_send == 1 && gateway_received == 0){
//			message_send = 0;
//			HAL_Delay(1000);
//			comm_print_debug("message didn't arrive");
////			comm_send(last_message);
//		}
//	}else{
//		//ERR
//	}
}

void comm_send(uint8_t * data,uint8_t len,uint8_t destination)
{
	SpiritPktBasicSetDestinationAddress(destination);
	SPSGRF_StartTx(data,len);
	memcpy(last_message, data , len);
}

uint8_t comm_encrypt(uint8_t *data, uint8_t len ,uint8_t *enc_data)
{
	char temp[100];
	char str[100];
	uint8_t i = 0;
	uint8_t blocks = 0;
	uint8_t cur_block =0;
	uint8_t rest = 0;
	if(len > 16)
	{
		blocks = len/16;
		while(1)
		{
			SpiritAesWriteDataIn(data , 16);
			SpiritAesExecuteEncryption();
			while(!irqStatus.IRQ_AES_END);
			irqStatus.IRQ_AES_END = 0;
			SpiritAesReadDataOut(enc_data , 16);
			irqStatus.IRQ_AES_END = 0;
			strcpy(temp, "data enc:");
			for(int i = 0; i<16; i++)
			{
				sprintf(str,"%02X", enc_data[i]);
				strcat(temp,str);
			}
			comm_print_debug(temp);
			data = data +16;
			enc_data = enc_data + 16;
			i = i+ 16;
			cur_block++;
			if(cur_block >= blocks)
			{
				rest = len % 16;
				if(rest)
				{
					SpiritAesWriteDataIn(data , rest);
					SpiritAesExecuteEncryption();
					while(!irqStatus.IRQ_AES_END);
					irqStatus.IRQ_AES_END = 0;
					SpiritAesReadDataOut(enc_data , 16);
					irqStatus.IRQ_AES_END = 0;
					strcpy(temp, "data enc:");
					for(int i = 0; i<16; i++){
						sprintf(str,"%02X", enc_data[i]);
						strcat(temp,str);
					}
					comm_print_debug(temp);
					//enc_data = enc_data +16;
					blocks++;
					i = i+ 16;
				}
				break;
			}

		}
	}else
	{
		SpiritAesWriteDataIn(data , len);
		SpiritAesExecuteEncryption();
		while(!irqStatus.IRQ_AES_END);
		irqStatus.IRQ_AES_END = 0;
		SpiritAesReadDataOut(enc_data , 16);
		irqStatus.IRQ_AES_END = 0;
		comm_printf_debug("test %d",len);
		strcpy(temp, "data enc:");
		for(int i = 0; i<16; i++)
		{
			sprintf(str,"%X", enc_data[i]);
			strcat(temp,str);
		}
		i = i+ 16;
		comm_print_debug(temp);
	}
	return i;
}

void comm_decrypt(uint8_t *data,uint8_t *_data)
{
	uint8_t len;
	uint8_t rxdata[96];
	uint8_t blocks = 0;
	uint8_t cur_block =0;
	uint8_t rest = 0;
	uint8_t *enc_data = &rxdata[0];
	len=SpiritLinearFifoReadNumElementsRxFifo();
	SPSGRF_GetRxData(rxdata);

	int i =0;
	char temp[150];
	char str[150];
//	len = 64;
	if(len>16)
	{
		blocks = len/16;
		while(1)
		{
			SpiritAesWriteDataIn(enc_data , 16);
			SpiritAesDeriveDecKeyExecuteDec();
			while(!irqStatus.IRQ_AES_END);
			irqStatus.IRQ_AES_END = 0;
			SpiritAesReadDataOut(data , 16);
			irqStatus.IRQ_AES_END = 0;
			memset(temp,0, 100);
			strcpy(temp, "data decr:");
			for(i = 0; i<16; i++)
			{
				sprintf(str,"%02x", data[i]);
				strcat(temp,str);
			}
			comm_print_debug(temp);
			data = data + 16;
			enc_data = enc_data + 16;
			cur_block++;
			if(cur_block >= blocks)
			{
				rest = len%16;
				if(rest)
				{
					SpiritAesWriteDataIn(enc_data , rest);
					SpiritAesDeriveDecKeyExecuteDec();
					while(!irqStatus.IRQ_AES_END);
					irqStatus.IRQ_AES_END = 0;
					SpiritAesReadDataOut(data , 16);
					irqStatus.IRQ_AES_END = 0;
					blocks++;
				}
				break;
			}
		}
	}else
	{
		SpiritAesWriteDataIn(enc_data, 16);
		SpiritAesDeriveDecKeyExecuteDec();
		while(!irqStatus.IRQ_AES_END);
		irqStatus.IRQ_AES_END = 0;
		SpiritAesReadDataOut(data , 16);
		irqStatus.IRQ_AES_END = 0;
		memset(temp,0, 50);
		strcpy(temp, "data decr:");
		for(i = 0; i<16; i++)
		{
			sprintf(str,"%02x", data[i]);
			strcat(temp,str);
		}
		comm_print_debug(temp);
	}
	#ifdef DEBUG_ENCRYPTION

	#endif
}

void comm_start(){
	SPSGRF_Init();
	SpiritAesWriteKey(c.key);
	//mesh_init();
}
