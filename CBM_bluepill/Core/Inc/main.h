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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SPSGRF/SPSGRF.h"
#include "string.h"
#include "stdio.h"
#include "Debug/debug.h"
#include "Comm/comm.h"
#include "Cbm/config.h"
#include "Mesh/mesh.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern SpiritIrqs irqStatus;
extern TIM_HandleTypeDef htim2;
extern struct sensor_values sensor_value;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define SPIRIT1_CS_Pin GPIO_PIN_4
#define SPIRIT1_CS_GPIO_Port GPIOA
#define SPIRIT1_SDN_Pin GPIO_PIN_0
#define SPIRIT1_SDN_GPIO_Port GPIOB
#define SPIRIT1_GPIO3_Pin GPIO_PIN_1
#define SPIRIT1_GPIO3_GPIO_Port GPIOB
#define SPIRIT1_GPIO3_EXTI_IRQn EXTI1_IRQn
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
extern UART_HandleTypeDef huart1;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
