#ifndef __bootloader_h
#define __bootloader_h

#include "main.h"

/* Get from stm32f4 ST lib */
#define NVIC_VectTab_RAM                ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH              ((uint32_t)0x08000000)
#define IS_NVIC_VECTTAB(VECTTAB)        (((VECTTAB) == NVIC_VectTab_RAM) || \
                                        ((VECTTAB) == NVIC_VectTab_FLASH))

#define IS_NVIC_OFFSET(OFFSET)          ((OFFSET) < 0x000FFFFF)

#define FW_NAME_SIZE                     30
#define READ_FILE_PAGE_SIZE             ((uint16_t)0x400)  


typedef struct {
   
   char fw_name_buf[FW_NAME_SIZE];
   char fw_old_name_buf[FW_NAME_SIZE];

   uint8_t (*hal_erase_flash)(void);
   uint8_t (*hal_write_flash_bin)(void);       // 写入.bin的固件
   uint8_t (*hal_read_data)(uint32_t );        // 读取某个地址的数据
   uint8_t (*hal_jump_to_app)(void);
}hal_bootloader_t;

void bl_jump_to_app(uint32_t sect,uint32_t Msp,uint32_t reset);
void nvic_set_vector_table(uint32_t NVIC_VectTab, uint32_t Offset);
void update_check(void);
#ifdef BOOT_LED_PORT
   void bsp_led_init(void);
   void bsp_led_on(void);
   void bsp_led_off(void);
   void bsp_led_toggle(void);
#endif

#endif /* __bootload_h */ 
