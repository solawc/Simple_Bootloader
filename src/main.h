#ifndef __main_h
#define __main_h

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#ifdef STM32F4xx
#include "stm32f4xx_hal.h"
    #ifdef STM32F401xC
        #include "mcu/stm32_f401rc_hal_system.h"
    #endif
#endif

#include "bl_config.h"


#include "hal/hal.h"
#include "hal/hal_uart.h"


#endif /* main.h */ 
