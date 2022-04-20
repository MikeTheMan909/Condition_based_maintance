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
union convert {
	float t;
	uint8_t b[4];
};

void comm_request(uint8_t *temp, float temperature, uint16_t X,uint16_t Y,uint16_t Z);
void comm_request_big(uint16_t X[10], uint16_t Y[10], uint16_t Z[10], uint16_t size);
void comm_received(uint8_t *data);
void comm_send(uint8_t * data);

#endif /* COMM_COMM_H_ */
