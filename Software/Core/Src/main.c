/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include "vfd08_driver.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//设置模式进入标志位
volatile unsigned char SETTING_FLAG;
//当前模式标志位
volatile unsigned char MODE_FLAG;
//确认按钮按下标志位
volatile unsigned char ENTER_FLAG;
//已获取时间标志位
volatile unsigned char TIME_GET_FLAG;
//按钮按下标志
volatile unsigned char KEY1_PRESSED;
volatile unsigned char KEY2_PRESSED;
//要求检测按钮按下标志
volatile unsigned char CHECK_KEY1;
volatile unsigned char CHECK_KEY2;
//设置时间切换标志
volatile unsigned char SWITCH_SET_TIME;

//定时器多次开启计数器
volatile unsigned char KEY1_TIM_TURN_COUNTER;
volatile unsigned char KEY2_TIM_TURN_COUNTER;

//RTC设置时间：小时
char SET_TIME_HOUR_NUM;
//RTC设置时间：分钟
char SET_TIME_MINUTE_NUM;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	/*
	MODE_FLAG = 0;
	SETTING_FLAG = 0;
	ENTER_FLAG = 0;
	KEY1_PRESSED = 0;
	KEY2_PRESSED = 0;
	SWITCH_SET_TIME = 0;
	SET_TIME_HOUR_NUM = 0;
	SET_TIME_MINUTE_NUM = 0;
	*/
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	//HAL_TIM_Base_Stop_IT(&htim1);
	//HAL_TIM_Base_Stop(&htim1);
	//__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);
	//HAL_TIM_Base_Stop_IT(&htim2);
	//HAL_TIM_Base_Stop(&htim2);
	//__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
	/* 
		KEY1 MODE
		KEY2 ENTER
		KEY2 在显示模式长按：切换世界线变动模式
	*/
	
	/* 在定时器内完成长短按判断 */
	if(htim == &htim1) //处理KEY1
	{
		if(CHECK_KEY1 == 1)
		{
			CHECK_KEY1 = 0;
			if(KEY1_TIM_TURN_COUNTER == 5)
		{
			HAL_TIM_Base_Stop_IT(&htim1);
			HAL_TIM_Base_Stop(&htim1);
			__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);
			__HAL_RCC_TIM1_CLK_DISABLE();
			HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);
			
			if(HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == 0) //KEY1保持按下，长按
			{
				KEY1_PRESSED = 0;
				//KEY1_LONG_PRESS = 1; //判断为KEY1长按
				if(MODE_FLAG == 1) //设置模式
				{
					MODE_FLAG = 0;//切换模式
					ENTER_FLAG = 1;
				}
				else //显示模式或世界线变动模式
				{
					MODE_FLAG = 1;//切换模式
				}
			}
			else //KEY1停止按下，短按
			{
				KEY1_PRESSED = 0;
				//KEY1_SHORT_PRESS = 1;  //判断为KEY1短按
				if(MODE_FLAG == 1) //设置模式
				{
					//时间增加
					if(SWITCH_SET_TIME == 0) //设置小时
					{
						SET_TIME_HOUR_NUM++;
						if(SET_TIME_HOUR_NUM > 23)
						{
							SET_TIME_HOUR_NUM = 0;
						}
					}
					else if(SWITCH_SET_TIME == 1) //设置分钟
					{
						SET_TIME_MINUTE_NUM++;
						if(SET_TIME_MINUTE_NUM > 59)
						{
							SET_TIME_MINUTE_NUM = 0;
						}
					}
					else
					{
						SWITCH_SET_TIME = 0; //防止溢出
						SET_TIME_HOUR_NUM++;
						if(SET_TIME_HOUR_NUM > 23)
						{
							SET_TIME_HOUR_NUM = 0;
						}
					}
				}
				else //显示模式或世界线变动模式
				{
					//无效果
				}
			}
			
		}
		else
		{
			KEY1_TIM_TURN_COUNTER++;
		}
		}
		
	}
	else if(htim == &htim2) //处理KEY2
	{
		if(CHECK_KEY2 == 1)
		{
			CHECK_KEY2 = 0;
			if(KEY2_TIM_TURN_COUNTER == 5)
		{
			HAL_TIM_Base_Stop_IT(&htim2);
			HAL_TIM_Base_Stop(&htim2);
			__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
			__HAL_RCC_TIM2_CLK_DISABLE();
			HAL_NVIC_DisableIRQ(TIM2_IRQn);
			
			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == 0) //KEY2保持按下，长按
			{
				KEY2_PRESSED = 0;
				//KEY2_LONG_PRESS = 1;  //判断为KEY2长按
				if(MODE_FLAG == 1) //设置模式
				{
					SWITCH_SET_TIME++;//切换要设置的时间位
					if(SWITCH_SET_TIME > 1)
					{
						SWITCH_SET_TIME = 0; //防止溢出
					}
				}
				else if(MODE_FLAG == 0) //显示模式
				{
					MODE_FLAG = 2; //进入世界线变动模式
				}
				else //世界线变动模式
				{
					MODE_FLAG = 0; //退出世界线变动模式
				}
			}
			else //KEY2停止按下，短按
			{
				KEY2_PRESSED = 0;
				//KEY2_SHORT_PRESS = 1; //判断为KEY2短按
				
				if(MODE_FLAG == 1) //设置模式
				{
					//时间减少
					if(SWITCH_SET_TIME == 0) //设置小时
					{
						SET_TIME_HOUR_NUM--;
						if(SET_TIME_HOUR_NUM < 0)
						{
							SET_TIME_HOUR_NUM = 23;
						}
					}
					else if(SWITCH_SET_TIME == 1) //设置分钟
					{
						SET_TIME_MINUTE_NUM--;
						if(SET_TIME_MINUTE_NUM < 0)
						{
							SET_TIME_MINUTE_NUM = 59;
						}
					}
					else
					{
						SWITCH_SET_TIME = 0; //防止溢出
						SET_TIME_HOUR_NUM--;
						if(SET_TIME_HOUR_NUM < 0)
						{
							SET_TIME_HOUR_NUM = 23;
						}
					}
				}
				else //显示模式或世界线变动模式
				{
					//无效果
				}
			}
			KEY2_PRESSED = 0;
		}
		else
		{
			KEY2_TIM_TURN_COUNTER++;
		}
		}
		
	}
	
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
