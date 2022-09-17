#ifndef __main_h
#define __main_h

/* STD Lib */
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* MCU HAL Lib */

#ifdef STM32F4xx
    #include "stm32f4xx_hal.h"
    #ifdef STM32F401xC
        #include "mcu/stm32_f401rc_hal_system.h"
        #ifdef ST_MKS_E3
            #include "mcu/pins_map/pins_robin_e3.h"
        #elif defined(ST_MKS_E3D)
            #include "mcu/pins_map/pins_robin_e3d.h"
        #elif defined(ZNP_ROBIN_DW)
            #include "mcu/pins_map/pins_znp_robin_nano_dw.h"
        #elif defined(MKS_DLC_LG0_V3)
            #include "mcu/pins_map/pins_mks_dlc32_lg0_v3.h"
        #endif
    #endif

    #ifdef STM32F407xx
        #include "mcu/stm32_f407_hal_system.h"
    #endif


    #ifdef STM32F429xx
        #include "mcu/stm32_f429_hal_system.h"
    #endif


#elif defined(STM32G0xx)
  #include "stm32g0xx_hal.h"
   #ifdef DLC_LG0_V2
       #include "mcu/stm32_g0b0_hal_system.h"
       #include "mcu/pins_map/pins_dlc_lg0.h"
   #endif
#endif

/* Common header files */
#include "bl_config.h"
#include "bootloader.h"

/* HAL drivers files */
#include "hal/hal.h"
#include "hal/hal_uart.h"
#include "hal/hal_spi.h"
#include "hal/hal_sdio.h"
#include "hal/hal_flash.h"
#include "external_device/SD/sdcard.h"
#include "external_device//LCD/lcd_dgus.h"
// Fatfs 
#include "ff.h"

extern FIL fil;


FRESULT open_append();

void IO_test(void);

#endif /* main.h */ 
