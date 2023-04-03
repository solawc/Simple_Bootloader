#include "stm32_f1_system.h"


#ifdef STM32F1

FLASH_EraseInitTypeDef bl_flash;

// STM32 F1 Serial default at 72MHz
void HAL_STM32_F1_SYS_Init(void) {

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_STM32_F1_ERASE_CHIP(void) {

    uint32_t error;

    HAL_FLASH_Unlock();
    
    memset(&bl_flash, 0, sizeof(bl_flash));
    bl_flash.TypeErase = FLASH_TYPEERASE_PAGES;
    bl_flash.PageAddress = APP_STAR_ADDR;
    bl_flash.NbPages = (MCU_FLASH - BL_OFFSET) % FLASH_PAGE_SIZE;
    
    if (HAL_FLASHEx_Erase(&bl_flash, &error) != HAL_OK) {
        hal_flag.bit_erase = 0;
    }else {
        hal_flag.bit_wait_finsh = 0;
    }
    HAL_FLASH_Lock();
}


void HAL_STM32_F1_PROGRAM_FLASH(uint32_t addr ,uint32_t *buff, uint32_t num) {

    HAL_StatusTypeDef FlashStatus=HAL_OK;
    uint32_t addrx=0;
    uint32_t endaddr=0;	
    HAL_StatusTypeDef status;
    if( addr <STM32_FLASH_BASE || addr % 4 ) return;	//非法地址

    HAL_FLASH_Unlock();               //解锁	

    addrx = addr;				              //写入的起始地址
    endaddr = addr + num * 2;	        //写入的结束地

    if(FlashStatus == HAL_OK)
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
