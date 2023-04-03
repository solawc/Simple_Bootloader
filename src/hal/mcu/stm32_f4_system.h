#ifndef __stm32_f4_system_h
#define __stm32_f4_system_h

#include "../../main.h"

#ifdef STM32F4_DEBUG

#define MCU_RAM                         KB(64)
#define MCU_FLASH                       KB(256)
#define BL_SIZE                         KB(32)
#define BL_END_ADDR                     ((uint32_t)0x8007fff) 
#define BL_OFFSET                       ((uint32_t)0X8000)
#define APP_STAR_ADDR                   ((uint32_t)0x8000000 + BL_OFFSET) 

void HAL_STM32_F4_SYS_Init(void);
void HAL_STM32_F4_ERASE_CHIP(void);
void HAL_STM32_F4_PROGRAM_FLASH(uint32_t addr ,uint32_t *buff, uint32_t num);
void Error_Handler(void);

#define SYSTEM_INIT()                   HAL_STM32_F4_SYS_Init()
#define COMMON_FLASH_ERASE()           HAL_STM32_F4_ERASE_CHIP()
#define COMMON_FLASH_WRITE(A,B,C)       HAL_STM32_F4_PROGRAM_FLASH(A,B,C)



#endif /* STM32F4_DEBUG */


#endif
