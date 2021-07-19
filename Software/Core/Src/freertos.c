/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "vfd08_driver.h"
#include "rtc.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"
#include "adc.h"

#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/**
KEY1 MODE
KEY2 ENTER

KEY1 ����������ʱ������
KEY2 ����������ʱ�����
KEY1 �������л�����ģʽ����ʾģʽ
KEY2 �������л�Ҫ���õ�ʱ��λ
KEY2 ����ʾģʽ�������л������߱䶯ģʽ
*/
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

RTC_TimeTypeDef NowTime;
RTC_TimeTypeDef SetTime;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId VFDHandle;
osThreadId RTCHandle;
osThreadId ButtonHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void StartDefaultTask(void const * argument);
void VFD_Show(void const * argument);
void RTC_Control(void const * argument);
void Button_Control(void const * argument);

void VFD_OP(void);
void VFD_random_num(void);

int fputc(int ch,FILE *f)
{
 uint8_t temp[1]={ch};
 HAL_UART_Transmit(&huart1,temp,1,2);
 return ch;
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void VFD_Show(void const * argument);
void RTC_Control(void const * argument);
void Button_Control(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of VFD */
  osThreadDef(VFD, VFD_Show, osPriorityHigh, 0, 128);
  VFDHandle = osThreadCreate(osThread(VFD), NULL);

  /* definition and creation of RTC */
  osThreadDef(RTC, RTC_Control, osPriorityHigh, 0, 128);
  RTCHandle = osThreadCreate(osThread(RTC), NULL);

  /* definition and creation of Button */
  osThreadDef(Button, Button_Control, osPriorityHigh, 0, 128);
  ButtonHandle = osThreadCreate(osThread(Button), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	
  /* Infinite loop */
  for(;;)
  {
		//printf("hello");
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_VFD_Show */
/**
* @brief Function implementing the VFD thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_VFD_Show */
void VFD_Show(void const * argument)
{
  /* USER CODE BEGIN VFD_Show */
	//uint8_t txbuffer[10] = "test";
	
	/*
	NowTime.Hours = 0;
	NowTime.Minutes = 0;
	NowTime.Seconds = 0;
	*/
	
	VFD_OP();
	VFD_random_num(); //��ʾ����仯������
	//osDelay(100);
	
	//osEvent ret;
  /* Infinite loop */
  for(;;)
  {
		//HAL_UART_Transmit(&huart1, txbuffer, sizeof(txbuffer), 0);
		if(MODE_FLAG == 0) //��ʾģʽ
		{
			if(TIME_GET_FLAG == 1)
			{
				//printf("%d:%d:%d",NowTime.Hours,NowTime.Minutes,NowTime.Seconds);
				VFD_write_char(0, (NowTime.Hours / 10) + '0');
				VFD_write_char(1, (NowTime.Hours % 10) + '0');
				VFD_write_char(2,':');
				VFD_write_char(3, (NowTime.Minutes / 10) + '0');
				VFD_write_char(4, (NowTime.Minutes % 10) + '0');
				VFD_write_char(5,':');
				VFD_write_char(6, (NowTime.Seconds / 10) + '0');
				VFD_write_char(7, (NowTime.Seconds % 10) + '0');
				TIME_GET_FLAG = 0;
			}
			else
			{
				osDelay(1);
			}
		}
		else if(MODE_FLAG == 1) //����ģʽ
		{
			if(TIME_GET_FLAG == 1)
			{
				VFD_write_char(0, (SetTime.Hours / 10) + '0');
				VFD_write_char(1, (SetTime.Hours % 10) + '0');
				VFD_write_char(2,':');
				VFD_write_char(3, (SetTime.Minutes / 10) + '0');
				VFD_write_char(4, (SetTime.Minutes % 10) + '0');
				VFD_write_char(5,':');
				VFD_write_char(6, (SetTime.Seconds / 10) + '0');
				VFD_write_char(7, (SetTime.Seconds % 10) + '0');
				TIME_GET_FLAG = 0;
			}
			else
			{
				osDelay(1);
			}
		}
		else if(MODE_FLAG == 2) //�����߱䶯ģʽ
		{
			/* ����Ч�������� */
			int adc_seed;
			//uint8_t num;
	
			//ADC�Ѿ���adc.h�п���
			HAL_ADC_PollForConversion(&hadc1, 10);
			if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
			{
				adc_seed = HAL_ADC_GetValue(&hadc1);
			}
			srand(adc_seed);
	
			VFD_write_char(0, '1');
			VFD_write_char(1, '.');
			for(int count = 0; count < 8; count++)
			{
				for(int i = 2; i < 8; i++)
				{
					uint8_t num = rand()%10;
					VFD_write_char(i, (num + '0'));
				}
				osDelay(1000);
				osDelay(1000);
			}
		}
		else
		{
			VFD_write_string(0,(uint8_t*)"ERROR!!!");
		}
		
    osDelay(100);
		
  }
  /* USER CODE END VFD_Show */
}

/* USER CODE BEGIN Header_RTC_Control */
/**
* @brief Function implementing the RTC thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RTC_Control */
void RTC_Control(void const * argument)
{
  /* USER CODE BEGIN RTC_Control */
	RTC_TimeTypeDef EnterSetTime;
  /* Infinite loop */
  for(;;)
  {
		if(MODE_FLAG == 0) //��ʾģʽ
		{
			if(TIME_GET_FLAG == 0)
			{
				HAL_RTC_GetTime(&hrtc, &NowTime, RTC_FORMAT_BIN); //��ȡ��ǰʱ��
				TIME_GET_FLAG = 1;
			}
			else
			{
				osDelay(1);
			}
		}
		else if(MODE_FLAG == 1) //����ģʽ
		{
			while(SETTING_FLAG)
			{
				osDelay(1); //�ȴ���ť����
			}
			SETTING_FLAG = 0; //���ñ�־λ
			
			SetTime.Hours = SET_TIME_HOUR_NUM; //��ȫ�ֱ������Сʱ�ͷ���ʱ��
			SetTime.Minutes = SET_TIME_MINUTE_NUM;
			SetTime.Seconds = 0;
			
			if(ENTER_FLAG) //�ȴ�ȷ����ִ��
			{
				ENTER_FLAG = 0; //���ñ�־λ
				EnterSetTime.Hours = SetTime.Hours;
				EnterSetTime.Minutes = SetTime.Minutes;
				EnterSetTime.Seconds = 0; //Ĭ�Ͻ�������Ϊ0
				HAL_RTC_SetTime(&hrtc, &EnterSetTime, RTC_FORMAT_BIN);
				TIME_GET_FLAG = 1;
			}
		}
		else //�����߱䶯ģʽ�����
		{
			osDelay(1); //ʲôҲ����
		}
  }
  /* USER CODE END RTC_Control */
}

/* USER CODE BEGIN Header_Button_Control */
/**
* @brief Function implementing the Button thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Button_Control */
void Button_Control(void const * argument)
{
  /* USER CODE BEGIN Button_Control */
	
  /* Infinite loop */
  for(;;)
  {
		//��ѯ��ȡ��ť״̬
		if((HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_RESET) || 
			(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET)) //�а�ť����
		{
			osDelay(5); //����
			
			if((HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_RESET) && 
				(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_SET)) //KEY1
			{
				if(!KEY1_PRESSED) //���KEY1��һ�ΰ���
				{
					KEY1_PRESSED = 1;
					CHECK_KEY1 = 1;
					__HAL_RCC_TIM1_CLK_ENABLE();
					HAL_TIM_Base_Start(&htim1); //�ж�KEY1���̰�
					HAL_TIM_Base_Start_IT(&htim1); 
					HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
				}
				else //���KEY1���ǵ�һ�ΰ���
				{
					osDelay(1); //�ȴ���ʱ����ɳ��̰��ж�
				}
			}
			else if((HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_SET) && 
				(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET)) //KEY2
			{
				if(!KEY2_PRESSED) //���KEY2��һ�ΰ���
				{
					KEY2_PRESSED = 1;
					CHECK_KEY2 = 1;
					__HAL_RCC_TIM2_CLK_ENABLE();
					HAL_TIM_Base_Start(&htim2); //�ж�KEY2���̰�
					HAL_TIM_Base_Start_IT(&htim2);
					HAL_NVIC_EnableIRQ(TIM2_IRQn);
				}
				else //���KEY2���ǵ�һ�ΰ���
				{
					osDelay(1); //�ȴ���ʱ����ɳ��̰��ж�
				}
			}
		}
    osDelay(1);
  }
  /* USER CODE END Button_Control */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* �ſ����������1 */
void VFD_OP(void)
{
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET);
	VFD_init();

	VFD_write_char(0,'I');
	VFD_write_char(1,'n');
	VFD_write_char(2,'i');
	VFD_write_char(3,'t');
	VFD_write_char(4,'O');
	VFD_write_char(5,'v');
	VFD_write_char(6,'O');
	VFD_write_char(7,'!');
	for(int i = 1;i < 255; i++)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		VFD_SPI_Transmit(0xe4);
		VFD_delay_us(1);
		VFD_SPI_Transmit(i); //���255
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		VFD_delay_us(1);
		//osDelay(10);
		osDelay(1);
	}
}

/* �ſ����������2 */
void VFD_random_num(void)
{
	int adc_seed;
	uint8_t num;
	
	//ADC�Ѿ���adc.h�п���
	HAL_ADC_PollForConversion(&hadc1, 10);
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	{
		adc_seed = HAL_ADC_GetValue(&hadc1);
	}
	srand(adc_seed);
	
	for(int count = 0; count < 8; count++)
	{
		for(int i = 0; i < 8; i++)
		{
			uint8_t num = rand()%10;
			VFD_write_char(i, (num + '0'));
		}
		osDelay(60);
	}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
