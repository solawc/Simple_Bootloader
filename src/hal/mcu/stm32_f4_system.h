#ifndef __stm32_f4_system_h
#define __stm32_f4_system_h

#include "../../main.h"

#ifdef STM32F4_DEBUG

#define MCU_RAM                         KB(128)
#define MCU_FLASH                       KB(512)
#define BL_SIZE                         KB(48) 
#define BL_OFFSET                       ((uint32_t)0XC000)
#define BL_END_ADDR                     ((uint32_t)0x800Bfff) 
#define APP_STAR_ADDR                   ((uint32_t)(0x8000000 + BL_OFFSET))


void HAL_STM32_F4_SYS_Init(void);


#define SYSTEM_INIT()                   HAL_STM32_F4_SYS_Init()
#define COMMON_FLASH_ERASE()            hal_flash_erase()
#define COMMON_FLASH_WRITE(A,B,C)       hal_flash_write(A,B,C)



#endif /* STM32F4_DEBUG */


#endif
