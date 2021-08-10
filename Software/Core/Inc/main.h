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
//设置模式进入标志位
extern volatile unsigned char SETTING_FLAG;
//当前模式标志位
extern volatile unsigned char MODE_FLAG;
//确认按钮按下标志位
extern volatile unsigned char ENTER_FLAG;
//已获取时间标志位
extern volatile unsigned char TIME_GET_FLAG;
//设置时间切换标志
extern volatile unsigned char SWITCH_SET_TIME;
//界面闪烁等待按钮复位标志
extern volatile unsigned char WAIT_FOR_BUTTON;

//按钮按下标志
extern volatile unsigned char KEY1_PRESSED;
extern volatile unsigned char KEY2_PRESSED;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
enum FSM_KEYSTATE_U
{
	KEY_PRESS = 0, //按钮按下状态
	KEY_JUDGE, //按钮等待判断状态
	KEY_EX_KEY1LONG, //按钮操作状态
	KEY_EX_KEY1SHORT,
	KEY_EX_KEY2LONG,
	KEY_EX_KEY2SHORT,
	KEY_READY, //按钮等待复位状态
	KEY_DEFAULT, //初始化默认状态
};
typedef enum FSM_KEYSTATE_U KeyState;

//RTC设置时间：小时
extern char SET_TIME_HOUR_NUM;
//RTC设置时间：分钟
extern char SET_TIME_MINUTE_NUM;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* 世界线数值 */
void Alpha(void);//α世界线
void Beta(void);//β世界线
void AlphaT(void);//α变动世界线
void BetaT(void);//β变动世界线
void TrueEnding(void);//1.048596%结局世界线
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
