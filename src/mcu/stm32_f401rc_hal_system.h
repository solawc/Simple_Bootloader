#ifndef _hal_system_h
#define _hal_system_h

#include "../main.h"

#define SYSTEM_INIT()           hal_stm32f401_system_init()


void hal_stm32f401_system_init(void);
void Error_Handler(void);
void systick_init(void);

#endif
