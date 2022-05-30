/*
 * data_structs.h
 *
 *  Created on: 18 mei 2022
 *      Author: ii26
 */

#ifndef APPLICATION_USER_IOT_CBM_DATA_STRUCTS_H_
#define APPLICATION_USER_IOT_CBM_DATA_STRUCTS_H_

#include "main.h"
#include "arm_math.h"
#include "data_structs.h"

// Data structs
struct L0_1 {
	float min;
	float max;
	float new;
};

struct L0_2 {
	uint16_t min;
	uint16_t max;
	uint16_t new;
};

struct L1_1 {
	float32_t samples[VIBRATION_SAMPLE_SIZE];
	struct L0_1 rms;
	struct L0_1 peak;
	struct L0_1 crest;
};

struct L1_2 {
	float32_t samples[VIBRATION_SAMPLE_SIZE];
	struct L0_1 rms;
	struct L0_1 peak;
};

struct L2 {
	struct L1_1 acceleration;
	struct L1_1 velocity;
	struct L1_2 displacement;
};

struct L3 {
	struct L2 x;
	struct L2 y;
	struct L2 z;
};

extern struct L3 vibration;
extern struct L0_2 co2;
extern struct L0_1 temperature;

#endif /* APPLICATION_USER_IOT_CBM_DATA_STRUCTS_H_ */
