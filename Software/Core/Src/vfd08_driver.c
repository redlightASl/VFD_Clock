#include "vfd08_driver.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "spi.h"

/* 移植时需要修改的函数 */

//微秒延时
void VFD_delay_microseconds(unsigned char time)
{
	HAL_Delay(1);
}

/* 移植时需要修改的函数 */

//向设备寄存器写入数据控制显示
void VFD_show(void)
{
	HAL_SPI_Transmit(&hspi1,&VFD_SHOW,sizeof(VFD_SHOW),5);
}

void VFD_init(void)
{
	uint8_t VFD_BITS_Adress=0xe0;
	uint8_t VFD_LIGHTNESS_Adress=0xe4;
	
  /* 设置显示数据位 */
	HAL_SPI_Transmit(&hspi1,&VFD_BITS_Adress,sizeof(VFD_BITS_Adress),5);
	VFD_delay_microseconds(5);
	HAL_SPI_Transmit(&hspi1,&VFD_BITS,sizeof(VFD_BITS),5); //8位数据
  VFD_delay_microseconds(5);

  /* 设置亮度 */
	HAL_SPI_Transmit(&hspi1,&VFD_LIGHTNESS_Adress,sizeof(VFD_LIGHTNESS_Adress),5);
  VFD_delay_microseconds(5);
	HAL_SPI_Transmit(&hspi1,&VFD_LIGHTNESS,sizeof(VFD_LIGHTNESS),5); //最高255
  VFD_delay_microseconds(5);
}

/* 
 * 在指定位置打印一个字符
 * 用户自定义,从所有CG-ROM中选取
 * 显示位置x:0-11(模组最多有11位)
 * 要显示的字符编码chr 
 */
void VFD_write_char(unsigned char x, unsigned char chr)
{
	uint8_t Init_Adress=0x20 + x; //地址寄存器起始位置
	uint8_t Print_Num=chr + 0x30;
	HAL_SPI_Transmit(&hspi1,&Init_Adress,sizeof(Init_Adress),5);
  HAL_SPI_Transmit(&hspi1,&Print_Num,sizeof(Print_Num),5);
  VFD_show();
}

/*
 * 在指定位置打印字符串
 * (仅适用于英文,标点,数字)
 * 显示位置x:0-11(模组最多有11位)
 * 要显示的字符串str
 */
void VFD_write_string(unsigned char x, unsigned char *str)
{
	uint8_t Init_Adress=0x20 + x;//地址寄存器起始位置
	HAL_SPI_Transmit(&hspi1,&Init_Adress,sizeof(Init_Adress),5); 
  while (*str)
  {
		HAL_SPI_Transmit(&hspi1,str,sizeof(str),5); 
    str++;
  }
  VFD_show();
}
