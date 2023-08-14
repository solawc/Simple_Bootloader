/*
 stm32_f4_system.c

 Copyright (c) 2021-2023 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#include "stm32_f4_system.h"

#ifdef STM32F4xx

uint32_t PLLN_USE = 84;    // Set STM32F4xx CPU Freq, default set low freq at 84MHz
uint32_t PLLM_USE = 4;
uint32_t PLLQ_USE = 4;
uint32_t PLLR_USE = 2;
FLASH_EraseInitTypeDef bl_flash;

void HAL_STM32_F4_SYS_Init(void) {

    #if defined(STM32F407xx) || defined(STM32F405xx)
      PLLN_USE = 168;   // 168M
    #elif defined(STM32F427xx) || defined(STM32F437xx) || \
          defined(STM32F429xx) || defined(STM32F439xx) || \
          defined(STM32F469xx) || defined(STM32F479xx)
      PLLN_USE = 180;
    #elif defined(STM32F446xx)
      PLLM_USE = 15;
      PLLN_USE = 216;
      PLLQ_USE = 2;
      PLLR_USE = 2;
    #else 
      PLLN_USE = 84;
    #endif

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = PLLM_USE;
    RCC_OscInitStruct.PLL.PLLN = PLLN_USE; 
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = PLLQ_USE;
    RCC_OscInitStruct.PLL.PLLR = PLLR_USE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
      Error_Handler();
    }
}

uint8_t HAL_STM32_F4_GET_SECTOR(uint32_t offset) {
    
    uint8_t sector = 0;

    if(offset <= 64) {
      sector = (ceil((float)offset / 16)) + 1;   // erase next sector.
    }else {
      sector = 5 + 1;
      // bootloader can not more than 128K.
    }
    return sector;
}

uint8_t HAL_STM32_F4_GET_N_SECTOR() {

  uint8_t nSector = 0;

  nSector = ((MCU_FLASH / 1024) - 128) / 128;   // 计算出有多少128K的页面
  
  if(BL_OFFSET <= 64) {
      nSector += (4 - (ceil(BL_OFFSET / 16)));
  }

  return nSector;
}

void HAL_STM32_F4_ERASE_CHIP(void) {

    uint32_t SectorError=0;
    
    HAL_FLASH_Unlock();

    memset(&bl_flash, 0, sizeof(bl_flash));
    bl_flash.TypeErase = FLASH_TYPEERASE_SECTORS;
    bl_flash.Sector = HAL_STM32_F4_GET_SECTOR(BL_OFFSET);
    bl_flash.NbSectors = HAL_STM32_F4_GET_N_SECTOR();
    bl_flash.VoltageRange = FLASH_VOLTAGE_RANGE_3;      // set at 2.7V to 3.6V

    if(HAL_FLASHEx_Erase(&bl_flash, &SectorError)!=HAL_OK) {
      hal_flag.bit_erase = 0;
    }else {
      hal_flag.bit_wait_finsh = 0;
    }

    HAL_FLASH_Lock();
}

void HAL_STM32_F4_PROGRAM_FLASH(uint32_t addr ,uint32_t *buff, uint32_t num) {
    HAL_StatusTypeDef FlashStatus=HAL_OK;
    uint32_t addrx=0;
    uint32_t endaddr=0;	
    HAL_StatusTypeDef status;
    if( addr <STM32_FLASH_BASE || addr % 4 ) return;	//非法地址

    HAL_FLASH_Unlock();               //解锁	

    addrx = addr;				              //写入的起始地址
    endaddr = addr + num * 2;	        //写入的结束地

    if(FlashStatus==HAL_OK)
    {
      while(addrx < endaddr)//写数据
      {
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addrx, *buff); /* 写入数据 */
        if(status != HAL_OK) {  break;	}   /* 写入异常 */
        addrx += 4;//2;
        buff++;
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