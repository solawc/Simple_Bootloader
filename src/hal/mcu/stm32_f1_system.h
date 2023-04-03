#ifndef __stm32_f1_system_h
#define __stm32_f1_system_h

#include "../../main.h"

#ifdef STM32F1


void HAL_STM32_F1_SYS_Init(void);
void HAL_STM32_F1_ERASE_CHIP(void);
void HAL_STM32_F1_PROGRAM_FLASH(uint32_t addr ,uint32_t *buff, uint32_t num);
void Error_Handler(void);

#define SYSTEM_INIT()                       HAL_STM32_F1_SYS_Init()
#define COMMON_FLASH_ERASE()                HAL_STM32_F1_ERASE_CHIP();
#define COMMON_FLASH_WRITE(A,B,C)           HAL_STM32_F1_PROGRAM_FLASH(A,B,C);

#endif /* STM32F1 */

#endif

