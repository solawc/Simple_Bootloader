/*
 stm32_f407_hal_system.h

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef __stm32f407_hal_system_h
#define __stm32f407_hal_system_h

#include "../../main.h"

#ifdef STM32F407xx

#ifndef STM32F4_DEBUG

/* Must settings */
#define MCU_RAM                         KB(128)
#define MCU_FLASH                       KB(512)
#define BL_SIZE                         KB(48) 
#define BL_OFFSET                       ((uint32_t)0XC000)
#define BL_END_ADDR                     ((uint32_t)0x800Bfff) 
#define APP_STAR_ADDR                   ((uint32_t)(0x8000000 + BL_OFFSET))

#define ADDR_FLASH_SECTOR_0             ((uint32_t)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1             ((uint32_t)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2             ((uint32_t)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3             ((uint32_t)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4             ((uint32_t)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5             ((uint32_t)0x08030000) 	//扇区4起始地址, 64 Kbytes  

#define SYSTEM_INIT()                   hal_stm32f407_system_init()
#define COMMON_FLASH_ERASE()            hal_flash_erase()
#define COMMON_FLASH_WRITE(A,B,C)       hal_flash_write(A,B,C)

void hal_stm32f407_system_init(void);
void Error_Handler(void);
void systick_init(void);
uint8_t hal_flash_erase(void);
void hal_flash_write(uint32_t addr ,uint32_t *buff, uint32_t num);
uint8_t hal_get_flash_sector(uint32_t addr);
#endif

#endif

#endif
