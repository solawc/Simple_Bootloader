#ifndef __stm32_g0b0_hal_system_h
#define __stm32_g0b0_hal_system_h



#include "../main.h"
#include "core_cm0plus.h"

/* Must settings */
#define MCU_RAM         (144     *1024)
#define MCU_FLASH       (512    *1024)
#define BL_SIZE         (32     *1024)
#define BL_END_ADDR     ((uint32_t)0x8007fff) 
#define APP_STAR_ADDR   ((uint32_t)0x8008000) 
#define BL_OFFSET       ((uint32_t)0X8000)



#define SYSTEM_INIT()                               hal_stm32g0b0_system_init()
#define COMMON_FLASH_ERASE()                        hal_flash_erase()
#define COMMON_FLASH_WRITE(A,B,C)                   hal_flash_write(A,B,C)

void Error_Handler(void);
void hal_stm32g0b0_system_init(void);
void hal_flash_erase();
void hal_flash_write(uint32_t addr ,uint16_t *buff, uint32_t num);

#endif