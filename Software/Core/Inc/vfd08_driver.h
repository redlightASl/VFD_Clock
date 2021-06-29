/* VFD08-软件SPI驱动头文件 */
/* Written by RedlightASl */
#ifndef __VFD08_H
#define __VFD08_H
#include <stdint.h>
#define OUTPUT 1

/* 引脚分配 */
static uint8_t din   = 11; // DA
static uint8_t clk   = 13; // CK
static uint8_t cs    = 10; // CS
static uint8_t Reset = 1; // RS
static uint8_t en    = 0; // EN

/* 底层适配函数 */
static void VFD_delay_seconds(unsigned char time);
static void VFD_delay_microseconds(unsigned char time);
static void VFD_set_pin_mode(unsigned char pin,unsigned char direction);
static void VFD_digital_write(unsigned char pin,unsigned char pin_voltage);

static void spi_write_data(unsigned char w_data);
static void VFD_cmd(unsigned char command);
static void VFD_show(void);
static void VFD_init(void);
static void VFD_write_char(unsigned char x, unsigned char chr);
static void VFD_write_string(unsigned char x, char *str);
static void VFD_test(void);
#endif