/*
 stm32_g4_system.h

 Copyright (c) 2021-2023 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef __stm32_g4_system_h
#define __stm32_g4_system_h

#include "../../../main.h"

#ifdef STM32G4xx

#include "stm32g4xx_hal.h"

#define ST_G4_FLASH_BASE        0x08000000

#define SYSTEM_INIT()                   HAL_STM32_G4_SYS_Init()
#define COMMON_FLASH_ERASE()            HAL_STM32_G4_ERASE_CHIP()
#define COMMON_FLASH_WRITE(A,B,C)       HAL_STM32_G4_PROGRAM_FLASH(A,B,C)


void Error_Handler(void);

#endif

#endif
