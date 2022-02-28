#ifndef __stm32f407_hal_system_h
#define __stm32f407_hal_system_h

#include "../main.h"

#ifdef STM32F407xx

/* Must settings */
#define MCU_RAM         (128     *1024)
#define MCU_FLASH       (512    *1024)
#define BL_SIZE         (48     *1024)
#define BL_END_ADDR     ((uint32_t)0x800Bfff) 
#define APP_STAR_ADDR   ((uint32_t)0x800C000) 
#define BL_OFFSET       ((uint32_t)0XC000)

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) 	//扇区5起始地址, 128 Kbytes   
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) 	//扇区6起始地址, 128 Kbytes 



#define SYSTEM_INIT()           hal_stm32f407_system_init()

void hal_stm32f407_system_init(void);
void Error_Handler(void);
void systick_init(void);
uint8_t hal_get_flash_sector(uint32_t addr);

#endif

#endif
