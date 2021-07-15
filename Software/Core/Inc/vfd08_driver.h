/* VFD08-软件SPI驱动头文件 */
/* Written by RedlightASl */
#ifndef __VFD08_H
#define __VFD08_H
#include <stdint.h>
#define OUTPUT 1

static uint8_t VFD_SHOW=0xe8;
static uint8_t VFD_BITS=0x07;
static uint8_t VFD_LIGHTNESS=0xff;

/* 引脚分配 */
/**SPI1 GPIO Configuration
    PA4     ------> SPI1_NSS
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI
*/

/* 底层适配函数 */
void VFD_delay_microseconds(uint8_t time);
void VFD_show(void);
void VFD_init(void);
void VFD_write_char(uint8_t x, uint8_t chr);
void VFD_write_string(uint8_t x, uint8_t *str);
#endif


