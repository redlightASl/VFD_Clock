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
//����ģʽ�����־λ
volatile unsigned char SETTING_FLAG;
//��ǰģʽ��־λ
volatile unsigned char MODE_FLAG;
//ȷ�ϰ�ť���±�־λ
volatile unsigned char ENTER_FLAG;
//�ѻ�ȡʱ���־λ
volatile unsigned char TIME_GET_FLAG;
//��ť���±�־
volatile unsigned char KEY1_PRESSED;
volatile unsigned char KEY2_PRESSED;
//Ҫ���ⰴť���±�־
volatile unsigned char CHECK_KEY1;
volatile unsigned char CHECK_KEY2;
//����ʱ���л���־
volatile unsigned char SWITCH_SET_TIME;

//��ʱ����ο���������
volatile unsigned char KEY1_TIM_TURN_COUNTER;
volatile unsigned char KEY2_TIM_TURN_COUNTER;

//RTC����ʱ�䣺Сʱ
char SET_TIME_HOUR_NUM;
//RTC����ʱ�䣺����
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
		KEY2 ����ʾģʽ�������л������߱䶯ģʽ
	*/
	
	/* �ڶ�ʱ������ɳ��̰��ж� */
	if(htim == &htim1) //����KEY1
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
			
			if(HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == 0) //KEY1���ְ��£�����
			{
				KEY1_PRESSED = 0;
				//KEY1_LONG_PRESS = 1; //�ж�ΪKEY1����
				if(MODE_FLAG == 1) //����ģʽ
				{
					MODE_FLAG = 0;//�л�ģʽ
					ENTER_FLAG = 1;
				}
				else //��ʾģʽ�������߱䶯ģʽ
				{
					MODE_FLAG = 1;//�л�ģʽ
				}
			}
			else //KEY1ֹͣ���£��̰�
			{
				KEY1_PRESSED = 0;
				//KEY1_SHORT_PRESS = 1;  //�ж�ΪKEY1�̰�
				if(MODE_FLAG == 1) //����ģʽ
				{
					//ʱ������
					if(SWITCH_SET_TIME == 0) //����Сʱ
					{
						SET_TIME_HOUR_NUM++;
						if(SET_TIME_HOUR_NUM > 23)
						{
							SET_TIME_HOUR_NUM = 0;
						}
					}
					else if(SWITCH_SET_TIME == 1) //���÷���
					{
						SET_TIME_MINUTE_NUM++;
						if(SET_TIME_MINUTE_NUM > 59)
						{
							SET_TIME_MINUTE_NUM = 0;
						}
					}
					else
					{
						SWITCH_SET_TIME = 0; //��ֹ���
						SET_TIME_HOUR_NUM++;
						if(SET_TIME_HOUR_NUM > 23)
						{
							SET_TIME_HOUR_NUM = 0;
						}
					}
				}
				else //��ʾģʽ�������߱䶯ģʽ
				{
					//��Ч��
				}
			}
			
		}
		else
		{
			KEY1_TIM_TURN_COUNTER++;
		}
		}
		
	}
	else if(htim == &htim2) //����KEY2
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
			
			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == 0) //KEY2���ְ��£�����
			{
				KEY2_PRESSED = 0;
				//KEY2_LONG_PRESS = 1;  //�ж�ΪKEY2����
				if(MODE_FLAG == 1) //����ģʽ
				{
					SWITCH_SET_TIME++;//�л�Ҫ���õ�ʱ��λ
					if(SWITCH_SET_TIME > 1)
					{
						SWITCH_SET_TIME = 0; //��ֹ���
					}
				}
				else if(MODE_FLAG == 0) //��ʾģʽ
				{
					MODE_FLAG = 2; //���������߱䶯ģʽ
				}
				else //�����߱䶯ģʽ
				{
					MODE_FLAG = 0; //�˳������߱䶯ģʽ
				}
			}
			else //KEY2ֹͣ���£��̰�
			{
				KEY2_PRESSED = 0;
				//KEY2_SHORT_PRESS = 1; //�ж�ΪKEY2�̰�
				
				if(MODE_FLAG == 1) //����ģʽ
				{
					//ʱ�����
					if(SWITCH_SET_TIME == 0) //����Сʱ
					{
						SET_TIME_HOUR_NUM--;
						if(SET_TIME_HOUR_NUM < 0)
						{
							SET_TIME_HOUR_NUM = 23;
						}
					}
					else if(SWITCH_SET_TIME == 1) //���÷���
					{
						SET_TIME_MINUTE_NUM--;
						if(SET_TIME_MINUTE_NUM < 0)
						{
							SET_TIME_MINUTE_NUM = 59;
						}
					}
					else
					{
						SWITCH_SET_TIME = 0; //��ֹ���
						SET_TIME_HOUR_NUM--;
						if(SET_TIME_HOUR_NUM < 0)
						{
							SET_TIME_HOUR_NUM = 23;
						}
					}
				}
				else //��ʾģʽ�������߱䶯ģʽ
				{
					//��Ч��
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
