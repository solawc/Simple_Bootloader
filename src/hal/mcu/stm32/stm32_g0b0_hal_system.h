/*
 stm32_g0b0_hal_system.h

 Copyright (c) 2021-2023 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef __stm32_g0b0_hal_system_h
#define __stm32_g0b0_hal_system_h

#ifdef STM32G0xx

#include "../../main.h"
#include "core_cm0plus.h"

/* Must settings */
#define MCU_RAM                                     (144     *1024)
#define MCU_FLASH                                   (512     *1024)
#define BL_SIZE                                     (32      *1024)
#define BL_END_ADDR                                 ((uint32_t)0x8007fff) 
#define BL_OFFSET                                   ((uint32_t)0X8000)
#define APP_STAR_ADDR                               ((uint32_t)0x8000000 + BL_OFFSET) 

#define SYSTEM_INIT()                               hal_stm32g0b0_system_init()
#define COMMON_FLASH_ERASE()                        hal_flash_erase()
#define COMMON_FLASH_WRITE(A,B,C)                   hal_flash_write(A,B,C)

void Error_Handler(void);
void hal_stm32g0b0_system_init(void);
uint8_t hal_flash_erase();
void hal_flash_write(uint32_t addr ,uint64_t *buff, uint32_t num);
#endif

#endif