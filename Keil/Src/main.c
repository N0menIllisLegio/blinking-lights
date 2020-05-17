/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void LightLEDs(uint16_t *LEDs);

void variant1(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction);
void variant2(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction);
void variant3(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction);
void variant4(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction);
void variant5(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction);

uint8_t MASK = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
char Initializtion = 1;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
	
	uint16_t LEDs = GPIO_PIN_0, unmovingLEDs = 0, movingLED = 0;
	char ActiveLEDs = 0, Direction = 1;
	void (*variant) (uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction);
	variant = variant1;
	
  while (1)
  {
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET)
		{
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
			{
				LEDs = GPIO_PIN_0;
				variant = variant1;
			}
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET)
			{
				LEDs = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
				variant = variant2;
			}
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET)
			{
				LEDs = 0;
				unmovingLEDs = 0;
				movingLED = 0;
				variant = variant3;
			}
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_SET)
			{
				LEDs = 0; 
				char ActiveLEDs = 0;
				Direction = 1;
				variant = variant4;
			}
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET)
			{
				LEDs = GPIO_PIN_0 | GPIO_PIN_1;
				variant = variant5;
			}
		}
		
		LightLEDs(&LEDs);
		variant(&LEDs, &unmovingLEDs, &movingLED, &ActiveLEDs, &Direction);
  }
}

void variant5(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction)
{
	if (*Direction == 1)
	{
		*LEDs = *LEDs << 1;
	}
	else
	{
		*LEDs = *LEDs >> 1;
	}
	
	if ((*LEDs << 1) > GPIO_PIN_8)
	{
		*Direction = -1;
	}
	
	if ((*LEDs >> 1) == GPIO_PIN_0)
	{
		*Direction = 1;
	}
}

void variant4(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction)
{
	*LEDs = 0;
	uint16_t temp = 0;
	
	for(int i = 0; i < *ActiveLEDs; i++)
	{
		*LEDs = *LEDs << 1;
		*LEDs = *LEDs | GPIO_PIN_0;
		temp = temp >> 1;
		temp = temp | GPIO_PIN_7;
	}
	
	*LEDs = *LEDs | temp;
	
	if (*ActiveLEDs == 4)
	{
		*Direction = -1;
	}
	
	if (*ActiveLEDs == 0)
	{
		*Direction = 1;
	}
	
	*ActiveLEDs = *ActiveLEDs + *Direction;
}


void variant3(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction)
{	
	if (*LEDs == MASK)
	{
		*unmovingLEDs = 0;
		*movingLED = 0;
	}
	
	if (*movingLED == 0)
	{
		*movingLED = GPIO_PIN_0;
	}
	else
	{
		*movingLED = *movingLED << 1;
		
		if ((((*movingLED << 1) + *unmovingLEDs) >= GPIO_PIN_8) || ((*movingLED << 1) >= GPIO_PIN_8))
		{
			*unmovingLEDs = *unmovingLEDs | *movingLED;
			*movingLED = 0;
		}
	}
	
	*LEDs = *movingLED + *unmovingLEDs;
}

void variant2(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction)
{
	*LEDs = *LEDs << 1;
	
	if (*LEDs > GPIO_PIN_8)
	{
		*LEDs = (*LEDs & MASK) | GPIO_PIN_0;
	}
}

void variant1(uint16_t *LEDs, uint16_t *unmovingLEDs, uint16_t *movingLED, char *ActiveLEDs, char *Direction)
{
	*LEDs = *LEDs << 1;
	
	if (*LEDs > GPIO_PIN_7)
	{
		*LEDs = GPIO_PIN_0;
	}
}

void LightLEDs(uint16_t *LEDs)
{
	HAL_GPIO_TogglePin(GPIOB, *LEDs);
	for(int i = 0; i < 1000; i++);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_All, GPIO_PIN_RESET);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LEDs_Pin|LEDsB1_Pin|LEDsB2_Pin|LEDsB3_Pin 
                          |LEDsB4_Pin|LEDsB5_Pin|LEDsB6_Pin|LEDsB7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4 
                           PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LEDs_Pin LEDsB1_Pin LEDsB2_Pin LEDsB3_Pin 
                           LEDsB4_Pin LEDsB5_Pin LEDsB6_Pin LEDsB7_Pin */
  GPIO_InitStruct.Pin = LEDs_Pin|LEDsB1_Pin|LEDsB2_Pin|LEDsB3_Pin 
                          |LEDsB4_Pin|LEDsB5_Pin|LEDsB6_Pin|LEDsB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // GPIO_SPEED_FREQ_HIGH
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
	printf("Wrong parameters value: file %s on line %d\r\n", file, line)
}
#endif 
