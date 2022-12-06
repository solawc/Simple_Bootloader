/*
 arm_support.h

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef __arm_support_h
#define __arm_support_h

#include "../main.h"

/* For ARM SCB base address. */
#define NVIC_VectTab_RAM                ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH              ((uint32_t)0x08000000)
#define IS_NVIC_VECTTAB(VECTTAB)        (((VECTTAB) == NVIC_VectTab_RAM) || \
                                        ((VECTTAB) == NVIC_VectTab_FLASH))
#define IS_NVIC_OFFSET(OFFSET)          ((OFFSET) < 0x000FFFFF)



void armSystickInit(void);
void armSystickDeinit(void);
__WEAK void systickCallBack(void);
void NvicSetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
#endif
