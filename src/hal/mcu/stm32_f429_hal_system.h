/*
 stm32_f429_hal_system.h

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef _hal_system_h
#define _hal_system_h

#ifdef STM32F429xx

#include "../../main.h"

/* Must settings */
#define MCU_RAM         KB(64)  
#define MCU_FLASH       KB(1024)  
#define BL_SIZE         KB(32)  
#define BL_END_ADDR     ((uint32_t)0x8007fff) 
#define BL_OFFSET       ((uint32_t)0X8000)
#define APP_STAR_ADDR   ((uint32_t)0x8008000 + BL_OFFSET) 

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) 	//扇区5起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) 	//扇区6起始地址, 128 Kbytes 
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) 	//扇区7起始地址, 128 Kbytes 
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) 	//扇区8起始地址, 128 Kbytes 
#define ADDR_FLASH_SECTOR_9    ((uint32_t)0x080A0000) 	//扇区9起始地址, 128 Kbytes 
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) 	//扇区10起始地址, 128 Kbytes 
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) 	//扇区11起始地址, 128 Kbytes 


/**************************************************************************************/

#define SYSTEM_INIT()           hal_stm32f429_system_init()

void hal_stm32f429_system_init(void);
void Error_Handler(void);
void systick_init(void);
uint8_t hal_get_flash_sector(uint32_t addr);

#endif
#endif