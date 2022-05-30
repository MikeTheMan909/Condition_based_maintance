/*
 * sensor.h
 *
 *  Created on: 23 mei 2022
 *      Author: user
 */

#ifndef SENSOR_SENSOR_H_
#define SENSOR_SENSOR_H_

#include "Comm/comm.h"

#define TEMPERATURE_I2C_ADDRESS					0x48
#define ACCELEROMETER_I2C_ADDRESS				0x1e

#define TEMP_CONVERTION							0.0078125

#define ACE
#define ACCELEROMETER_SAMPLE_RATE 	3200.0
#define VIBRATION_SAMPLE_SIZE 		1024
#define G_TO_MMS2 					9806.65
#define ACCELEROMETER_G_RANGE		8.0


typedef struct sensor_values *SENSOR_s;

uint8_t sensor_setup();
void sensor_readAcceleroRegister(uint8_t reg);
float sensor_readTemperature();
uint8_t accelerometer_sample();
void sensor_fillStruct(SENSOR_s sensor);

#endif /* SENSOR_SENSOR_H_ */
