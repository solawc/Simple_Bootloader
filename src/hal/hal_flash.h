#ifndef __hal_flash_h
#define __hal_flash_h

#include "../main.h"

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
#define FLASH_WAITETIME  50000          //FLASH等待超时时间


void mcu_flash_erase();

#endif
