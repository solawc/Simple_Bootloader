#ifndef _hal_h
#define _hal_h

#include "../main.h"
#include "stdbool.h"

#ifndef MCU_FREQ
#define MCU_FREQ        F_CPU
#endif

#ifndef MCU_RAM
#define MCU_RAM         64*1024     // default for STM32F401RC, is 64k RAM 
#endif

#ifndef MCU_FLASH
#define MCU_FLASH       256*1024    // default for STM32F401RC is 256k Flash
#endif
#define MCU_NAME        

typedef struct {
    uint16_t mcu_freq;
    uint16_t mcu_size;
    bool is_has_u_disk;
    bool is_has_sd_disk;
}hal_info_t;
extern hal_info_t hal_info;


void printf_info(void);

#endif
