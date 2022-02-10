#ifndef __stm32f407_hal_system_h
#define __stm32f407_hal_system_h

#include "../main.h"

#ifdef STM32F407xx

#define SYSTEM_INIT()           hal_stm32f407_system_init()




void hal_stm32f407_system_init(void);
void Error_Handler(void);
void systick_init(void);
uint8_t hal_get_flash_sector(uint32_t addr);

#endif

#endif
