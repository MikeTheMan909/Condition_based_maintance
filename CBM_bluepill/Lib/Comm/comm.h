/*
 * comm.h
 *
 *  Created on: Mar 15, 2022
 *      Author: user
 */

#ifndef COMM_COMM_H_
#define COMM_COMM_H_

#include "SPSGRF/spsgrf.h"
#include "Debug/debug.h"
#include "string.h"
#include "Cbm/config.h"
#include "main.h"
#include "Mesh/mesh.h"
#include "stdio.h"

union convert {
	float t;
	uint8_t b[4];
};

typedef struct vector_value {
	float rms;
	float peak;
	float crest;
} VECTOR;

struct sensor_values {
	float temperature;
	struct acceleration {
		VECTOR x;
		VECTOR y;
		VECTOR z;
	} acc;
	struct velocity {
		VECTOR x;
		VECTOR y;
		VECTOR z;
	} velo;
	struct displacement {
		VECTOR x;
		VECTOR y;
		VECTOR z;
	} disp;
};


enum commands {
	COMMAND,
	DATAPKT,
};

extern uint8_t last_message[50];

uint8_t comm_request(uint8_t *temp, struct sensor_values values);
void comm_request_big(uint16_t X[10], uint16_t Y[10], uint16_t Z[10], uint16_t size);
void comm_received(uint8_t *data);
void comm_send(uint8_t * data);
void comm_encrypt(uint8_t *data, uint8_t len ,uint8_t *enc_data);
void comm_decrypt(uint8_t *data);
void comm_command(uint8_t cmd, uint8_t address);
void comm_start();

#define DEBUG_ENCRYPTION 1




#endif /* COMM_COMM_H_ */
