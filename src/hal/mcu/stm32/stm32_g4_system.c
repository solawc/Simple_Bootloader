#include "stm32_g4_system.h"

#ifdef STM32G4xx

uint8_t ST_G4_GET_PAGE(uint32_t addr) {

  uint32_t page;
  
  page = (((addr - ST_G4_FLASH_BASE) / 1024) / 2) - 1;

  return page;
}

void HAL_STM32_G4_ERASE_CHIP(void) {
  FLASH_EraseInitTypeDef erase_init;
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t error;

  // 初始化擦除结构体
  erase_init.Banks = FLASH_BANK_1;
  erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
  erase_init.Page = 16; // ST_G4_GET_PAGE(APP_STAR_ADDR);
  erase_init.NbPages = 48;

  // 解锁Flash
  HAL_FLASH_Unlock();

  // 配置Flash擦除操作
  status = HAL_FLASHEx_Erase(&erase_init, &error);
  if(status != HAL_OK) {
    DEBUG_PRINT("Flash erase error!Please check mcu is right!");
  }

  erase_init.Banks = FLASH_BANK_2;
  erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
  erase_init.Page = 0; // ST_G4_GET_PAGE(APP_STAR_ADDR);
  erase_init.NbPages = 64;

  status = HAL_FLASHEx_Erase(&erase_init, &error);
  if(status != HAL_OK) {
    DEBUG_PRINT("Flash erase error!Please check mcu is right!");
  }

  // 锁定Flash
  HAL_FLASH_Lock();
}

void HAL_STM32_G4_PROGRAM_FLASH(uint32_t addr ,uint32_t *buff, uint32_t num) {

  HAL_StatusTypeDef FlashStatus=HAL_OK;
  uint32_t addrx=0;
  uint32_t endaddr=0;	
  HAL_StatusTypeDef status;
 
  if( addr < ST_G4_FLASH_BASE || addr % 4 ) return;	//非法地址

  HAL_FLASH_Unlock();               //解锁	
  addrx = addr;				              //写入的起始地址
  endaddr = addr + num * 4;	        //写入的结束地

  if(FlashStatus == HAL_OK)
  {
    while(addrx < endaddr)//写数据
    {
      status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addrx, *(uint64_t *)buff); /* 写入数据 */
      if(status != HAL_OK) {  break;	}   /* 写入异常 */
      addrx += 8;
      buff += 2;
    }  
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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

#endif







