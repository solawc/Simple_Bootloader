/*
 bootloader.h

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef __bootloader_h
#define __bootloader_h

#include "main.h"


#define FW_NAME_SIZE                     30
#define READ_FILE_PAGE_SIZE             ((uint16_t)0x400)  

typedef uint32_t MSP_TYPE;
typedef uint32_t RST_TYPE;

extern MSP_TYPE msp;
extern RST_TYPE reset;

typedef struct {
   char *fw_name_buf;
   char *fw_old_name_buf;
}hal_bootloader_t;

void bl_jump_to_app(uint32_t sect,uint32_t Msp,uint32_t reset);
void NvicSetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void UpdateCheck(void);
#ifdef BOOT_LED_PORT
   void bsp_led_init(void);
   void bsp_led_on(void);
   void bsp_led_off(void);
   void bsp_led_toggle(void);
#endif

#endif /* __bootload_h */ 
