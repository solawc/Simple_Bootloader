/*
 stm32_f401rc_hal_system.h

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef _hal_system_h
#define _hal_system_h

#ifdef STM32F401xC

#include "../../main.h"
#include "core_cm4.h"

/* Must settings */
#define MCU_RAM                 KB(64)
#define MCU_FLASH               KB(256)
#define BL_SIZE                 KB(32)
#define BL_END_ADDR             ((uint32_t)0x8007fff) 
#define BL_OFFSET               ((uint32_t)0X8000)
#define APP_STAR_ADDR           ((uint32_t)0x8000000 + BL_OFFSET) 

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) 	//Setor 0 begin, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) 	//Setor 1 begin, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) 	//Setor 2 begin, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) 	//Setor 3 begin, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) 	//Setor 4 begin, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) 	//Setor 5 begin, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) 	//Setor 6 begin, 128 Kbytes 

/**************************************************************************************/

#define SYSTEM_INIT()                   hal_stm32f401_system_init()             
#define COMMON_FLASH_ERASE()            hal_flash_erase()
#define COMMON_FLASH_WRITE(A,B,C)       hal_flash_write(A,B,C)

void hal_stm32f401_system_init(void);
void Error_Handler(void);
void systick_init(void);
uint8_t hal_flash_erase(void);
void hal_flash_write(uint32_t addr ,uint32_t *buff, uint32_t num);
uint8_t hal_get_flash_sector(uint32_t addr);

#endif
#endif