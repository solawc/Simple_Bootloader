/*
 arm_support.c

 Copyright (c) 2021-2023 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/


#include "arm_support.h"

void armSystickInit(void) {

    SysTick_Config(SystemCoreClock / 1000);         /* Tick for 1ms. */
}


extern uint32_t hidTick;
/**************************************************************
 * Author:sola
 * Fix time:2022-01-20
 * Describe:
 * This is for the tick of the HAL library, 
 * using Systick's interrupt to perform the count
**************************************************************/
void SysTick_Handler(void)
{
    HAL_IncTick();
    hidTick--;
}

/* only support cortex-M */
void armSystickDeinit(void) {
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     /* Disable systick */
}

void armReset(void) {

    NVIC_SystemReset();
}


/* only support cortex-M */
void NvicSetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset) {

    /* Check the parameters */
    assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
    assert_param(IS_NVIC_OFFSET(Offset)); 
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}