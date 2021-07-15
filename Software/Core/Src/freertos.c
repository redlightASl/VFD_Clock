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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId VFDHandle;
osThreadId RTCHandle;
osThreadId ButtonHandle;
osMessageQId Queue_RTCHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

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

  /* Create the queue(s) */
  /* definition and creation of Queue_RTC */
  osMessageQDef(Queue_RTC, 16, uint16_t);
  Queue_RTCHandle = osMessageCreate(osMessageQ(Queue_RTC), NULL);

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
	RTC_TimeTypeDef NowTime;
	RTC_TimeTypeDef SetTime;
	MODE_FLAG=0;
	
  /* Infinite loop */
  for(;;)
  {
		if(MODE_FLAG == 0) //日常模式
		{
			HAL_RTC_GetTime(&hrtc, &NowTime, RTC_FORMAT_BCD);
			VFD_write_string(0, &NowTime.Hours);
			VFD_write_char(2,':');
			VFD_write_string(3, &NowTime.Minutes);
			VFD_write_char(5,':');
			VFD_write_string(6, &NowTime.Seconds);
		}
		else if(MODE_FLAG == 1) //设置模式
		{
			HAL_RTC_GetTime(&hrtc, &SetTime, RTC_FORMAT_BCD);
			VFD_write_string(0, &SetTime.Hours);
			VFD_write_char(2,':');
			VFD_write_string(3, &SetTime.Minutes);
			VFD_write_char(5,':');
			VFD_write_string(6, &SetTime.Seconds);
			osDelay(100);
		}
		
    osDelay(1);
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
	
	
	
  /* Infinite loop */
  for(;;)
  {
		if(MODE_FLAG == 1) //进入设置模式
		{
		
		}
		
    osDelay(1);
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
		
    osDelay(1);
  }
  /* USER CODE END Button_Control */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
