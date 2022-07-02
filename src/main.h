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
    #endif

    #ifdef STM32F407xx
        #include "mcu/stm32_f407_hal_system.h"
    #endif

    #ifdef STM32F429xx
        #include "mcu/stm32_f429_hal_system.h"
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




FRESULT open_append();

void IO_test(void);

#endif /* main.h */ 
