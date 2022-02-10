#include "mcu/stm32_f407_hal_system.h"


#ifdef STM32F407xx

void hal_stm32f407_system_init(void) {




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

uint8_t hal_get_flash_sector(uint32_t addr) {



    
}

#endif