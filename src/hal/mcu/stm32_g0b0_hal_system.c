/*
 stm32_g0b0_hal_system.c

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#include "stm32_g0b0_hal_system.h"

#ifdef STM32G0xx

FLASH_EraseInitTypeDef bl_flash;

void hal_stm32g0b0_system_init(void) {

  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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


uint8_t hal_flash_erase() {

    uint32_t PageError=0;
    HAL_StatusTypeDef FlashStatus=HAL_OK;

    HAL_FLASH_Unlock();             //解锁

    bl_flash.Banks = FLASH_BANK_1;
    bl_flash.TypeErase = FLASH_TYPEERASE_PAGES;   //按页擦除
    bl_flash.Page = 16;
    bl_flash.NbPages = 35;

    if(HAL_FLASHEx_Erase(&bl_flash, &PageError)!=HAL_OK) 
    {
        hal_flag.bit_erase = 0;
    }else {
        hal_flag.bit_erase = 1;
    }

    FlashStatus = FLASH_WaitForLastOperation(FLASH_WAITETIME);

    if(FlashStatus == HAL_OK) {
        hal_flag.bit_wait_finsh = 1;
    }else {
        hal_flag.bit_wait_finsh = 0;
    }

    HAL_FLASH_Lock();

    return 0;

}


void hal_flash_write(uint32_t addr ,uint64_t *buff, uint32_t num) {

  HAL_StatusTypeDef FlashStatus=HAL_OK;
	uint32_t addrx=0;
	uint32_t endaddr=0;	
    HAL_StatusTypeDef status;
    
    if( addr <STM32_FLASH_BASE || addr % 4 ) return;	//非法地址

    HAL_FLASH_Unlock();                 //解锁	
    addrx = addr;				                //写入的起始地址
	  endaddr = addr + num * 4;	          //写入的结束地

	if(FlashStatus==HAL_OK)
	{
		 while(addrx < endaddr)//写数据
		 {
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addrx, *buff);

        if(status != HAL_OK)//写入数据
        { 
          break;	//写入异常
        }
        addrx += 8;
        buff++;
		}  
	}
	HAL_FLASH_Lock();           //上锁
}


#endif





