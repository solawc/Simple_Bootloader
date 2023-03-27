/*
 mks_robin_e3_e3d_hal_system.c

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#include "mks_robin_e3_e3d_hal_system.h"


#ifdef STM32F103xE

FLASH_EraseInitTypeDef bl_flash;

void hal_stm32f103_system_init(void) {



}

void systick_init(void) {
  SysTick_Config(F_CPU / 1000);
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


uint8_t hal_flash_erase(void) {

    return 0;
}


void hal_flash_write(uint32_t addr ,uint32_t *buff, uint32_t num) {



}

#endif