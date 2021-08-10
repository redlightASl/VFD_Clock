/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define DEBUG_PRINTF

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
//����ģʽ�����־λ
extern volatile unsigned char SETTING_FLAG;
//��ǰģʽ��־λ
extern volatile unsigned char MODE_FLAG;
//ȷ�ϰ�ť���±�־λ
extern volatile unsigned char ENTER_FLAG;
//�ѻ�ȡʱ���־λ
extern volatile unsigned char TIME_GET_FLAG;
//����ʱ���л���־
extern volatile unsigned char SWITCH_SET_TIME;
//������˸�ȴ���ť��λ��־
extern volatile unsigned char WAIT_FOR_BUTTON;

//��ť���±�־
extern volatile unsigned char KEY1_PRESSED;
extern volatile unsigned char KEY2_PRESSED;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
enum FSM_KEYSTATE_U
{
	KEY_PRESS = 0, //��ť����״̬
	KEY_JUDGE, //��ť�ȴ��ж�״̬
	KEY_EX_KEY1LONG, //��ť����״̬
	KEY_EX_KEY1SHORT,
	KEY_EX_KEY2LONG,
	KEY_EX_KEY2SHORT,
	KEY_READY, //��ť�ȴ���λ״̬
	KEY_DEFAULT, //��ʼ��Ĭ��״̬
};
typedef enum FSM_KEYSTATE_U KeyState;

//RTC����ʱ�䣺Сʱ
extern char SET_TIME_HOUR_NUM;
//RTC����ʱ�䣺����
extern char SET_TIME_MINUTE_NUM;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* ��������ֵ */
void Alpha(void);//��������
void Beta(void);//��������
void AlphaT(void);//���䶯������
void BetaT(void);//�±䶯������
void TrueEnding(void);//1.048596%���������
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MODE_Pin GPIO_PIN_1
#define MODE_GPIO_Port GPIOA
#define ENTER_Pin GPIO_PIN_2
#define ENTER_GPIO_Port GPIOA
#define NCS_Pin GPIO_PIN_4
#define NCS_GPIO_Port GPIOA
#define SCLK_Pin GPIO_PIN_5
#define SCLK_GPIO_Port GPIOA
#define DIN_Pin GPIO_PIN_7
#define DIN_GPIO_Port GPIOA
#define EN_Pin GPIO_PIN_15
#define EN_GPIO_Port GPIOB
#define RESET_Pin GPIO_PIN_8
#define RESET_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
