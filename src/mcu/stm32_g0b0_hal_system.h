#ifndef __stm32_g0b0_hal_system_h
#define __stm32_g0b0_hal_system_h



#include "../main.h"
#include "core_cm0plus.h"

#define SYSTEM_INIT()                               hal_stm32g0b0_system_init()

#define COMMON_FLASH_ERASE()                        hal_flash_erase()
#define COMMON_FLASH_WRITE(A,B,C)                   hal_flash_write(A,B,C)

void Error_Handler(void);
void hal_stm32g0b0_system_init(void);
void hal_flash_erase();
void hal_flash_write(uint32_t addr ,uint16_t *buff, uint32_t num);

#endif