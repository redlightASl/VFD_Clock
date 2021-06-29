#include "vfd08_driver.h"

/* 移植时需要修改的函数 */
//秒延时
static void VFD_delay_seconds(unsigned char time)
{

}

//微秒延时
static void VFD_delay_microseconds(unsigned char time)
{

}

//配置引脚输入输出模式
static void VFD_set_pin_mode(unsigned char pin,unsigned char direction)
{

}

//配置引脚输出电平
static void VFD_digital_write(unsigned char pin,unsigned char pin_voltage)
{

}
/* 移植时需要修改的函数 */

//软件SPI传输一字节数据
static void spi_write_data(unsigned char w_data)
{
    unsigned char i;
  	for (i = 0; i < 8; i++)
  	{
    	VFD_digital_write(clk, 0);
    	if ((w_data & 0x01) == 0x01)
    	{
      		VFD_digital_write(din, 1);
    	}
    	else
    	{
    	  	VFD_digital_write(din, 1);
    	}
    	w_data >>= 1;
    	VFD_digital_write(clk, 1);
  	}
}

//向设备写入控制代码
static void VFD_cmd(unsigned char command)
{
  	VFD_digital_write(cs, 0);
  	spi_write_data(command);
  	VFD_digital_write(cs, 1);
  	VFD_delay_microseconds(5);
}

//向设备寄存器写入数据控制显示
static void VFD_show(void)
{
  	VFD_digital_write(cs, 0); //开始传输
  	spi_write_data(0xe8); //地址寄存器起始位置
  	VFD_digital_write(cs, 1); //停止传输
}

static void VFD_init(void)
{
  	/* 设置显示数据位 */
  	VFD_digital_write(cs, 0);
  	spi_write_data(0xe0);
  	VFD_delay_microseconds(5);
  	spi_write_data(0x07); //8位数据
  	VFD_digital_write(cs, 1);
  	VFD_delay_microseconds(5);

  	/* 设置亮度 */
  	VFD_digital_write(cs, 0);
  	spi_write_data(0xe4);
  	VFD_delay_microseconds(5);
  	spi_write_data(0xff); //最高255
  	VFD_digital_write(cs, 1);
  	VFD_delay_microseconds(5);
}

/* 
 * 在指定位置打印一个字符
 * 用户自定义,从所有CG-ROM中选取
 * 显示位置x:0-11(模组最多有11位)
 * 要显示的字符编码chr 
 */
static void VFD_write_char(unsigned char x, unsigned char chr)
{
  	VFD_digital_write(cs, 0); //开始传输
  	spi_write_data(0x20 + x); //地址寄存器起始位置
  	spi_write_data(chr + 0x30);
  	VFD_digital_write(cs, 1); //停止传输
  	VFD_show();
}

/*
 * 在指定位置打印字符串
 * (仅适用于英文,标点,数字)
 * 显示位置x:0-11(模组最多有11位)
 * 要显示的字符串str
 */
static void VFD_write_string(unsigned char x, char *str)
{
  	VFD_digital_write(cs, 0); //开始传输
  	spi_write_data(0x20 + x); //地址寄存器起始位置
  	while (*str)
  	{
    	spi_write_data(*str); //ascii与对应字符表转换
    	str++;
  	}
  	VFD_digital_write(cs, 1); //停止传输
  	VFD_show();
}

/* VFD测试程序 */
static void VFD_test(void)
{
  	VFD_set_pin_mode(en, OUTPUT);
  	VFD_set_pin_mode(clk, OUTPUT);
  	VFD_set_pin_mode(din, OUTPUT);
  	VFD_set_pin_mode(cs, OUTPUT);
  	VFD_set_pin_mode(Reset, OUTPUT);
  	VFD_digital_write(en, 1);
  	VFD_digital_write(Reset, 0);
  	VFD_delay_microseconds(5);
  	VFD_digital_write(Reset, 1);
  	VFD_init();

	while(1)
	{
		VFD_cmd(0xE9);// 全亮
  		VFD_delay_seconds(1000);
  		VFD_write_char(0, 0);
  		VFD_write_char(1, 1);
  		VFD_write_char(2, 2);
  		VFD_write_char(3, 3);
  		VFD_write_char(4, 4);
  		VFD_write_char(5, 5);
  		VFD_write_char(6, 6);
  		VFD_write_char(7, 7);
  		VFD_delay_seconds(1000);
  		VFD_write_string(0, "ABCDEFGH");
  		VFD_delay_seconds(1000);
	}
}