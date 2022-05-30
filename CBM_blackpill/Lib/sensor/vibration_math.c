/*
 * vibration_math.c
 *
 *  Created on: 18 mei 2022
 *      Author: ii26
 */

#include "vibration_math.h"

void convert_to_velocity()
{
	float32_t x_temp_samples[VIBRATION_SAMPLE_SIZE];
	float32_t y_temp_samples[VIBRATION_SAMPLE_SIZE];
	float32_t z_temp_samples[VIBRATION_SAMPLE_SIZE];

	/* Convert to velocity in mm/s */

	// First convert g to mm/s^2
	arm_scale_f32(vibration.x.acceleration.samples, G_TO_MMS2, x_temp_samples, VIBRATION_SAMPLE_SIZE);
	arm_scale_f32(vibration.y.acceleration.samples, G_TO_MMS2, y_temp_samples, VIBRATION_SAMPLE_SIZE);
	arm_scale_f32(vibration.z.acceleration.samples, G_TO_MMS2, z_temp_samples, VIBRATION_SAMPLE_SIZE);

	// Then calculate the integral (mm/s^2 -> mm/s)
	numerical_integrate(x_temp_samples, vibration.x.velocity.samples, ACCELEROMETER_SAMPLE_RATE, VIBRATION_SAMPLE_SIZE);
	numerical_integrate(y_temp_samples, vibration.y.velocity.samples, ACCELEROMETER_SAMPLE_RATE, VIBRATION_SAMPLE_SIZE);
	numerical_integrate(z_temp_samples, vibration.z.velocity.samples, ACCELEROMETER_SAMPLE_RATE, VIBRATION_SAMPLE_SIZE);

	// Remove DC component
	subtract_mean(vibration.x.velocity.samples, VIBRATION_SAMPLE_SIZE);
	subtract_mean(vibration.y.velocity.samples, VIBRATION_SAMPLE_SIZE);
	subtract_mean(vibration.z.velocity.samples, VIBRATION_SAMPLE_SIZE);
}

void convert_to_displacement()
{
	// Calculate the integral (mm/s -> mm)
	numerical_integrate(vibration.x.velocity.samples, vibration.x.displacement.samples, ACCELEROMETER_SAMPLE_RATE, VIBRATION_SAMPLE_SIZE);
	numerical_integrate(vibration.y.velocity.samples, vibration.y.displacement.samples, ACCELEROMETER_SAMPLE_RATE, VIBRATION_SAMPLE_SIZE);
	numerical_integrate(vibration.z.velocity.samples, vibration.z.displacement.samples, ACCELEROMETER_SAMPLE_RATE, VIBRATION_SAMPLE_SIZE);

	// Remove DC component
	subtract_mean(vibration.x.displacement.samples, VIBRATION_SAMPLE_SIZE);
	subtract_mean(vibration.y.displacement.samples, VIBRATION_SAMPLE_SIZE);
	subtract_mean(vibration.z.displacement.samples, VIBRATION_SAMPLE_SIZE);
}

void vibration_statistics()
{
	uint32_t peakIndex; // unused, necessary parameter for arm_max_f32

	// Calculate statistics for acceleration
	// For x axis
	// RMS (Root Mean Square)
	arm_rms_f32(vibration.x.acceleration.samples, VIBRATION_SAMPLE_SIZE, &vibration.x.acceleration.rms.new);

	// Peak (absolute maximum)
	arm_abs_f32(vibration.x.acceleration.samples, vibration.x.acceleration.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.x.acceleration.samples, VIBRATION_SAMPLE_SIZE, &vibration.x.acceleration.peak.new, &peakIndex);

	// Crest (RMS divided by peak)
	vibration.x.acceleration.crest.new = vibration.x.acceleration.peak.new / vibration.x.acceleration.rms.new;

	// For y axis
	arm_rms_f32(vibration.y.acceleration.samples, VIBRATION_SAMPLE_SIZE, &vibration.y.acceleration.rms.new);
	arm_abs_f32(vibration.y.acceleration.samples, vibration.y.acceleration.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.y.acceleration.samples, VIBRATION_SAMPLE_SIZE, &vibration.y.acceleration.peak.new, &peakIndex);
	vibration.y.acceleration.crest.new = vibration.y.acceleration.peak.new / vibration.y.acceleration.rms.new;

	// For z axis
	arm_rms_f32(vibration.z.acceleration.samples, VIBRATION_SAMPLE_SIZE, &vibration.z.acceleration.rms.new);
	arm_abs_f32(vibration.z.acceleration.samples, vibration.z.acceleration.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.z.acceleration.samples, VIBRATION_SAMPLE_SIZE, &vibration.z.acceleration.peak.new, &peakIndex);
	vibration.z.acceleration.crest.new = vibration.z.acceleration.peak.new / vibration.z.acceleration.rms.new;

	// Calculate statistics for velocity
	arm_rms_f32(vibration.x.velocity.samples, VIBRATION_SAMPLE_SIZE, &vibration.x.velocity.rms.new);
	arm_abs_f32(vibration.x.velocity.samples, vibration.x.velocity.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.x.velocity.samples, VIBRATION_SAMPLE_SIZE, &vibration.x.velocity.peak.new, &peakIndex);
	vibration.x.velocity.crest.new = vibration.x.velocity.peak.new / vibration.x.velocity.rms.new;

	arm_rms_f32(vibration.y.velocity.samples, VIBRATION_SAMPLE_SIZE, &vibration.y.velocity.rms.new);
	arm_abs_f32(vibration.y.velocity.samples, vibration.y.velocity.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.y.velocity.samples, VIBRATION_SAMPLE_SIZE, &vibration.y.velocity.peak.new, &peakIndex);
	vibration.y.velocity.crest.new = vibration.y.velocity.peak.new / vibration.y.velocity.rms.new;

	arm_rms_f32(vibration.z.velocity.samples, VIBRATION_SAMPLE_SIZE, &vibration.z.velocity.rms.new);
	arm_abs_f32(vibration.z.velocity.samples, vibration.z.velocity.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.z.velocity.samples, VIBRATION_SAMPLE_SIZE, &vibration.z.velocity.peak.new, &peakIndex);
	vibration.z.velocity.crest.new = vibration.z.velocity.peak.new / vibration.z.velocity.rms.new;

	// Calculate statistics for displacement
	arm_rms_f32(vibration.x.displacement.samples, VIBRATION_SAMPLE_SIZE, &vibration.x.displacement.rms.new);
	arm_abs_f32(vibration.x.displacement.samples, vibration.x.displacement.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.x.displacement.samples, VIBRATION_SAMPLE_SIZE, &vibration.x.displacement.peak.new, &peakIndex);

	arm_rms_f32(vibration.y.displacement.samples, VIBRATION_SAMPLE_SIZE, &vibration.y.displacement.rms.new);
	arm_abs_f32(vibration.y.displacement.samples, vibration.y.displacement.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.y.displacement.samples, VIBRATION_SAMPLE_SIZE, &vibration.y.displacement.peak.new, &peakIndex);

	arm_rms_f32(vibration.z.displacement.samples, VIBRATION_SAMPLE_SIZE, &vibration.z.displacement.rms.new);
	arm_abs_f32(vibration.z.displacement.samples, vibration.z.displacement.samples, VIBRATION_SAMPLE_SIZE);
	arm_max_f32(vibration.z.displacement.samples, VIBRATION_SAMPLE_SIZE, &vibration.z.displacement.peak.new, &peakIndex);
}

void subtract_mean(float32_t *inputVector, uint16_t vectorSize)
{
	float32_t Mean;

	arm_mean_f32(inputVector, vectorSize, &Mean);
	Mean *= -1.0;
	arm_offset_f32(inputVector, Mean, inputVector, vectorSize);
}

void numerical_integrate(float32_t *inputVector, float32_t *integratedVector, float32_t sampleRate, uint32_t vectorSize)
{
	// Start at 0
	integratedVector[0] = 0;

	for (uint16_t i = 0; i < vectorSize-1; i++)
	{
		integratedVector[i+1] = integratedVector[i] + (inputVector[i] / sampleRate);
	}
}
