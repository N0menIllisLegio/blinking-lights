/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
	extern "C" {
#endif

#include "stm32f1xx_hal.h"

void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/
#define LEDs_Pin GPIO_PIN_0
#define LEDs_GPIO_Port GPIOB
#define LEDsB1_Pin GPIO_PIN_1
#define LEDsB1_GPIO_Port GPIOB
#define LEDsB2_Pin GPIO_PIN_2
#define LEDsB2_GPIO_Port GPIOB
#define LEDsB3_Pin GPIO_PIN_3
#define LEDsB3_GPIO_Port GPIOB
#define LEDsB4_Pin GPIO_PIN_4
#define LEDsB4_GPIO_Port GPIOB
#define LEDsB5_Pin GPIO_PIN_5
#define LEDsB5_GPIO_Port GPIOB
#define LEDsB6_Pin GPIO_PIN_6
#define LEDsB6_GPIO_Port GPIOB
#define LEDsB7_Pin GPIO_PIN_7
#define LEDsB7_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
