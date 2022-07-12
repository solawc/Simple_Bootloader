#include "mcu/stm32_f401rc_hal_system.h"

#ifdef STM32F401xC

FLASH_EraseInitTypeDef bl_flash;

void hal_stm32f401_system_init(void) {

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 84;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if(addr<ADDR_FLASH_SECTOR_1)          return FLASH_SECTOR_0;
  else if(addr<ADDR_FLASH_SECTOR_2)     return FLASH_SECTOR_1;
  else if(addr<ADDR_FLASH_SECTOR_3)     return FLASH_SECTOR_2;
  else if(addr<ADDR_FLASH_SECTOR_4)     return FLASH_SECTOR_3;
  else if(addr<ADDR_FLASH_SECTOR_5)     return FLASH_SECTOR_4;
  else return FLASH_SECTOR_5;
}


uint8_t hal_flash_erase(void) {

    uint32_t SectorError=0;
    HAL_StatusTypeDef FlashStatus=HAL_OK;

    HAL_FLASH_Unlock();             //解锁

    bl_flash.TypeErase = FLASH_TYPEERASE_SECTORS;
    bl_flash.Sector = hal_get_flash_sector(ADDR_FLASH_SECTOR_2);        //要擦除的扇区
	bl_flash.NbSectors = 4;                                             //一次只擦除一个扇区
	bl_flash.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    if(HAL_FLASHEx_Erase(&bl_flash, &SectorError)!=HAL_OK) 
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

void hal_flash_write(uint32_t addr ,uint16_t *buff, uint32_t num) {

	HAL_StatusTypeDef FlashStatus=HAL_OK;
	uint32_t addrx=0;
	uint32_t endaddr=0;	
    HAL_StatusTypeDef status;
    
    if( addr <STM32_FLASH_BASE || addr % 4 ) return;	//非法地址

    HAL_FLASH_Unlock();             //解锁	

    addrx = addr;				//写入的起始地址

	endaddr = addr + num * 2;	//写入的结束地

	if(FlashStatus==HAL_OK)
	{
		 while(addrx < endaddr)//写数据
		 {
            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addrx, *buff);

			if(status != HAL_OK)//写入数据
			{ 
				break;	//写入异常
			}
			addrx += 2;
			buff++;
		}  
	}
	HAL_FLASH_Lock();           //上锁
}

#endif