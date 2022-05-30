/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SPSGRF/SPSGRF.h"
#include "string.h"
#include "stdio.h"
#include <stdbool.h>
#include "Debug/debug.h"
#include "Comm/comm.h"
#include "Cbm/config.h"
#include "Mesh/mesh.h"
#include "sensor/sensor.h"
#include "sensor/vibration_math.h"
#include "sensor/data_structs.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim5;
extern SpiritIrqs irqStatus;
extern struct sensor_values sensor_value;
extern uint8_t interrupt_flag;
extern bool trigger;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI_Cs_Pin GPIO_PIN_4
#define SPI_Cs_GPIO_Port GPIOA
#define SPIRIT1_GPIO0_Pin GPIO_PIN_0
#define SPIRIT1_GPIO0_GPIO_Port GPIOB
#define SPIRIT1_GPIO0_EXTI_IRQn EXTI0_IRQn
#define SPIRIT_SHUTDOWN_Pin GPIO_PIN_1
#define SPIRIT_SHUTDOWN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
enum states {
	ENCRYPT,
	DECRYPT,
	PREP_DATA,
	SEND,
	RECEIVE,
	IDLE
};
extern enum states state;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
