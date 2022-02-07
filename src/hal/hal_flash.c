#include "hal_flash.h"

FLASH_EraseInitTypeDef bl_flash;


uint8_t hal_flash_erase(void) {

    uint32_t SectorError=0;
    HAL_StatusTypeDef FlashStatus=HAL_OK;

    HAL_FLASH_Unlock();             //解锁

    bl_flash.TypeErase = FLASH_TYPEERASE_SECTORS;
    bl_flash.Sector = hal_get_flash_sector(ADDR_FLASH_SECTOR_2);   //要擦除的扇区
	bl_flash.NbSectors = 4;                             //一次只擦除一个扇区
	bl_flash.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    if(HAL_FLASHEx_Erase(&bl_flash, &SectorError)!=HAL_OK) 
    {
        DEBUG_PRINT("erase flase error");
    }else {
        DEBUG_PRINT("erase flase Succeed");
    }

    FlashStatus = FLASH_WaitForLastOperation(FLASH_WAITETIME);

    if(FlashStatus == HAL_OK) {
        DEBUG_PRINT("wait finsh succeed");
    }else {
        DEBUG_PRINT("wait fail, error code:%d", FlashStatus);
    }

    HAL_FLASH_Lock();

    return 0;
}


void hal_flash_write(uint32_t addr ,uint16_t *buff, uint32_t num) {
    
    FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus=HAL_OK;
    uint32_t SectorError=0;
	uint32_t addrx=0;
	uint32_t endaddr=0;	
    HAL_StatusTypeDef status;
    
    if( addr <STM32_FLASH_BASE || addr % 4 ) return;	//非法地址

    HAL_FLASH_Unlock();             //解锁	

    addrx=addr;				//写入的起始地址

	endaddr = addr+num*2;	//写入的结束地

	if(FlashStatus==HAL_OK)
	{
		 while(addr < endaddr)//写数据
		 {
            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr, *buff);

			if(status != HAL_OK)//写入数据
			{ 
				break;	//写入异常
			}
			addr+=2;
			buff++;
		}  
	}
	HAL_FLASH_Lock();           //上锁
}



