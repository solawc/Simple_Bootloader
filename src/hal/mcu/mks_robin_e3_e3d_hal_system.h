/*
 mks_robin_e3_e3d_hal_system.h

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifdef STM32F103xE

#include "../../main.h"
#include "core_cm3.h"

#define MCU_RAM                 KB(64)
#define MCU_FLASH               KB(256)
#define BL_SIZE                 KB(32)
#define BL_END_ADDR             ((uint32_t)0x8007fff) 
#define BL_OFFSET               ((uint32_t)0X8000)
#define APP_STAR_ADDR           ((uint32_t)0x8000000 + BL_OFFSET) 


void hal_stm32f103_system_init(void);
void Error_Handler(void);
uint8_t hal_flash_erase(void);
void hal_flash_write(uint32_t addr ,uint32_t *buff, uint32_t num);

#define SYSTEM_INIT()                   hal_stm32f103_system_init()             
#define COMMON_FLASH_ERASE()            hal_flash_erase()
#define COMMON_FLASH_WRITE(A,B,C)       hal_flash_write(A,B,C)



#endif
