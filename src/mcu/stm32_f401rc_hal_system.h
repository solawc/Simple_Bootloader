#ifndef _hal_system_h
#define _hal_system_h

#ifdef STM32F401xC

#include "../main.h"
#include "core_cm4.h"

/* Must settings */
#define MCU_RAM         (64     *1024)
#define MCU_FLASH       (256    *1024)
#define BL_SIZE         (32     *1024)
#define BL_END_ADDR     ((uint32_t)0x8007fff) 
#define APP_STAR_ADDR   ((uint32_t)0x8008000) 
#define BL_OFFSET       ((uint32_t)0X8000)

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) 	//扇区5起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) 	//扇区6起始地址, 128 Kbytes 

/**************************************************************************************/

#define SYSTEM_INIT()               hal_stm32f401_system_init()
#define COMMON_FLASH_ERASE()        hal_flash_erase()
#define COMMON_FLASH_WRITE(A,B,C)   hal_flash_write(A,B,C)

void hal_stm32f401_system_init(void);
void Error_Handler(void);
void systick_init(void);
uint8_t hal_flash_erase(void);
void hal_flash_write(uint32_t addr ,uint16_t *buff, uint32_t num);
uint8_t hal_get_flash_sector(uint32_t addr);

#endif
#endif
