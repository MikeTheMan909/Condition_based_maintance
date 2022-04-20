/*
 * comm.h
 *
 *  Created on: Mar 15, 2022
 *      Author: user
 */

#ifndef COMM_COMM_H_
#define COMM_COMM_H_

#include "spsgrf.h"
#include "debug.h"
#include "string.h"
#include "stdio.h"
#include "main.h"

union convert {
	float t;
	uint8_t b[4];
};
void comm_request(float temperature, uint16_t X,uint16_t Y,uint16_t Z);
#endif /* COMM_COMM_H_ */
