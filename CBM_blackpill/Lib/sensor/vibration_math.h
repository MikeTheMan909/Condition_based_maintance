/*
 * vibration_math.h
 *
 *  Created on: 18 mei 2022
 *      Author: ii26
 */

#ifndef APPLICATION_USER_MATH_VIBRATION_MATH_H_
#define APPLICATION_USER_MATH_VIBRATION_MATH_H_

#include "main.h"
#include "arm_math.h"
#include "data_structs.h"

// Function prototypes
void convert_to_velocity();
void convert_to_displacement();
void vibration_statistics();
void subtract_mean(float32_t *inputVector, uint16_t vectorSize);
void numerical_integrate(float32_t *inputVector, float32_t *integratedVector, float32_t sampleRate, uint32_t vectorSize);

#endif /* APPLICATION_USER_MATH_VIBRATION_MATH_H_ */
