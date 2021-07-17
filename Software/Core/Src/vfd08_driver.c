#include "vfd08_driver.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"

uint8_t VFD_SHOW = 0xe8;
uint8_t VFD_BITS = 0x07;
uint8_t VFD_LIGHTNESS = 0xff;
uint8_t VFD_BITS_Adress = 0xe0;
uint8_t VFD_LIGHTNESS_Adress = 0xe4;
uint8_t VFD_TEST = 0xe9;

/* 移植时需要修改的函数 */

//微秒延时
void VFD_delay_us(uint32_t us)
{
  uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
  while (delay--) {;}
}

//毫秒延时
void VFD_delay_microseconds(uint8_t time)
{
	HAL_Delay(time);
}

/* 移植时需要修改的函数 */

//软SPI
void VFD_SPI_Transmit(uint8_t data)
{
	uint8_t i;
  for(i = 0; i < 8; i++)   
  {
		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		if((data & 0x01) == 0x01)       
		{
			HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, GPIO_PIN_SET);
		}
		else       
		{
			HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, GPIO_PIN_RESET);
		}
		data>>=1;      
		
    VFD_delay_us(1);
		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
    VFD_delay_us(1);
	}
}

//向设备寄存器写入数据控制显示
void VFD_show(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	VFD_delay_us(1);
	VFD_SPI_Transmit(VFD_SHOW);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void VFD_init(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	VFD_SPI_Transmit(VFD_TEST);
	VFD_delay_us(1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	VFD_delay_microseconds(100);
	
  /* 设置显示数据位 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	VFD_SPI_Transmit(VFD_BITS_Adress);
	VFD_delay_us(1);
	VFD_SPI_Transmit(VFD_BITS); //8位数据
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	
  VFD_delay_us(1);

  /* 设置亮度 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	VFD_SPI_Transmit(VFD_LIGHTNESS_Adress);
  VFD_delay_us(1);
	VFD_SPI_Transmit(VFD_LIGHTNESS); //最高255
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  VFD_delay_us(1);
}

/**
 * 在指定位置打印一个字符
 * 用户自定义,从所有CG-ROM中选取
 * 显示位置x:0-11(模组最多有11位)
 * 要显示的字符编码chr 
 */
void VFD_write_char(uint8_t x, uint8_t chr)
{
	uint8_t Init_Adress = 0x20 + x; //地址寄存器起始位置
	uint8_t Print_Num = chr;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	VFD_delay_us(1);
	VFD_SPI_Transmit(Init_Adress);
	VFD_delay_us(1);
  VFD_SPI_Transmit(Print_Num);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  VFD_show();
}

/**
 * 在指定位置打印字符串
 * (仅适用于英文,标点,数字)
 * 显示位置x:0-11(模组最多有11位)
 * 要显示的字符串str
 */
void VFD_write_string(uint8_t x, uint8_t *str)
{
	uint8_t Init_Adress=0x20 + x;//地址寄存器起始位置
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	VFD_delay_us(1);
	VFD_SPI_Transmit(Init_Adress); 
  while (*str)
  {
		VFD_SPI_Transmit(*str); 
    str++;
  }
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  VFD_show();
}
