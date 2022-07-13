#include "hal_sdio.h"

SD_HandleTypeDef sd_hsdio;

#ifdef SD_CARD_SDIO

static void WIFI_PDN_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOG_CLK_ENABLE();															   
	GPIO_InitStruct.Pin = GPIO_PIN_9;	
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;      
	GPIO_InitStruct.Pull  = GPIO_PULLUP;  
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST; 
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);	
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_9,GPIO_PIN_RESET);  
}

static void sd_sdio_pin_init(void) {

    GPIO_InitTypeDef SDIO_GPIO_Init;

    _SD_GPIO_CLK_ENABLE();                          // Enable SDIO and GPIO Clock

    WIFI_PDN_INIT();

    SDIO_GPIO_Init.Alternate = GPIO_AF12_SDIO;
    SDIO_GPIO_Init.Mode = GPIO_MODE_AF_PP;
    SDIO_GPIO_Init.Pin = SD_SDIO_CLK_PIN|
                         SD_SDIO_D0_PIN|
                         SD_SDIO_D1_PIN|
                         SD_SDIO_D2_PIN|
                         SD_SDIO_D3_PIN;
    SDIO_GPIO_Init.Pull = GPIO_NOPULL;
    SDIO_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_SDIO_CLK_PORT, &SDIO_GPIO_Init);

    SDIO_GPIO_Init.Alternate = GPIO_AF12_SDIO;
    SDIO_GPIO_Init.Mode = GPIO_MODE_AF_PP;
    SDIO_GPIO_Init.Pin = SD_SDIO_CMD_PIN;
    SDIO_GPIO_Init.Pull = GPIO_NOPULL;
    SDIO_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_SDIO_CMD_PORT, &SDIO_GPIO_Init);

}

static void sd_sdio_init(void){

    sd_hsdio.Instance = SD_CARD_SDIO;
    sd_hsdio.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    sd_hsdio.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    sd_hsdio.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    sd_hsdio.Init.BusWide = SDIO_BUS_WIDE_1B;
    sd_hsdio.Init.ClockDiv = SDIO_TRANSFER_CLK_DIV;
    sd_hsdio.Init.HardwareFlowControl =SDIO_HARDWARE_FLOW_CONTROL_DISABLE;

    if(HAL_SD_Init(&sd_hsdio) != HAL_OK)
    {
        Error_Handler();
    }

    if(HAL_SD_ConfigWideBusOperation(&sd_hsdio,SDIO_BUS_WIDE_4B) != HAL_OK)//Configure SD bus width for data transmission
    {
        Error_Handler();
    }
    

}


void hal_sd_init(void) {
    sd_sdio_pin_init();      // set gpio init
    sd_sdio_init();          // set sdio init
}


void hal_sd_read_block(uint32_t *pData, uint32_t ReadAddr,uint32_t NumberOfBlocks) {
    
    if(HAL_SD_ReadBlocks(&sd_hsdio,(uint8_t *)pData,ReadAddr,NumberOfBlocks,1000) != HAL_OK)
    {
        Error_Handler();
    }
    
}

void hal_sd_write_block(uint32_t *pData, uint32_t WriteAddr,uint32_t NumberOfBlocks) {
    
    if(HAL_SD_WriteBlocks(&sd_hsdio,(uint8_t *)pData,WriteAddr,NumberOfBlocks,1000) != HAL_OK)
    {
        Error_Handler();
    }
    
}

uint8_t hal_sd_get_cardstate(void){
    
    return((HAL_SD_GetCardState(&sd_hsdio) == HAL_SD_CARD_TRANSFER ) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);

}

uint8_t hal_sd_erase(uint32_t StartAddr, uint32_t EndAddr){
    if(HAL_SD_Erase(&sd_hsdio, StartAddr, EndAddr) != HAL_OK)
    {
        Error_Handler();
    }

}

void hal_sd_get_cardinfo(HAL_SD_CardInfoTypeDef *CardInfo){

  HAL_SD_GetCardInfo(&sd_hsdio, CardInfo);

}

void hal_sd_get_cardcsd(HAL_SD_CardCSDTypeDef *pCSD){

  HAL_SD_GetCardCSD(&sd_hsdio, pCSD);

}


void hal_sd_deinit(void) {

    _SD_GPIO_CLK_DISABLE();
    HAL_SD_DeInit(&sd_hsdio);
}



void hal_sd_register(void) {    

    hal_sd.sd_init = hal_sd_init;
    hal_sd.sd_trans_data = hal_sd_write_block;
    hal_sd.sd_receive_data = hal_sd_read_block;
    hal_sd.sd_get_status = hal_sd_get_cardstate;
    hal_sd.sd_get_cardinfo = hal_sd_get_cardinfo;
    hal_sd.sd_erase = hal_sd_erase;
    hal_sd.sd_get_cardcsd = hal_sd_get_cardcsd;

    hal_sd.sd_init();

}



#endif


