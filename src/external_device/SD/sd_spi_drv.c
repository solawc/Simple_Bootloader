#include "sd_spi_drv.h"

#ifdef SD_CARD_SPI

SPI_HandleTypeDef sd_hspi;

static void BspSdSpiGpioInit(void) {

    GPIO_InitTypeDef SPI_GPIO_Init = {
        .Alternate = BOARD_SD_GPIO_AF,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_NOPULL,
    };

    GPIO_InitTypeDef SPI_CS_GPIO_Init = {
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW,
    };

    _SD_GPIO_CLK_ENABLE();                          // Enable SPI and GPIO Clock


    SPI_GPIO_Init.Pin = SD_SPI_MISO_PIN|
                        SD_SPI_MOSI_PIN|
                        SD_SPI_SCK_PIN;
    HAL_GPIO_Init(SD_SPI_SCK_PORT, &SPI_GPIO_Init);

    SPI_GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    SPI_GPIO_Init.Pull = GPIO_PULLUP;
    SPI_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
    SPI_GPIO_Init.Pin = SD_SPI_CS_PIN;
    HAL_GPIO_Init(SD_SPI_CS_PORT, &SPI_GPIO_Init);

    SPI_CS_GPIO_Init.Pin = SD_DET_PIN;
    HAL_GPIO_Init(SD_DET_PORT, &SPI_CS_GPIO_Init);
}

static void BspSpiInit(void) {

    sd_hspi.Instance = SD_CARD_SPI;
    sd_hspi.Init.BaudRatePrescaler = SD_SPI_LOW_SPEED;
    sd_hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    sd_hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    sd_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    sd_hspi.Init.CRCPolynomial = 7;
    sd_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    sd_hspi.Init.Direction = SPI_DIRECTION_2LINES;
    sd_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    sd_hspi.Init.Mode = SPI_MODE_MASTER;
    sd_hspi.Init.NSS = SPI_NSS_SOFT;
    sd_hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    if (HAL_SPI_Init(&sd_hspi) != HAL_OK) {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(&sd_hspi);
}

void BspSdSetSpeed(uint32_t SPI_BaudRatePrescaler) {
    sd_hspi.Init.BaudRatePrescaler = SPI_BaudRatePrescaler;
    HAL_SPI_Init(&sd_hspi);
    __HAL_SPI_ENABLE(&sd_hspi);
}

void BspSdSpiWait() {
    
    uint32_t t=0;
	do
	{	
		if(hal_sd_read_write_byte(0XFF)==0XFF) return 0;
		t++;		  	
	}while(t<0XFFFFFF);
	return 1;
}

void BspSdBegin() {
    HAL_GPIO_WritePin(SD_SPI_CS_PORT, SD_SPI_CS_PIN, GPIO_PIN_RESET);
}

void BspSdEnd() {
    HAL_GPIO_WritePin(SD_SPI_CS_PORT, SD_SPI_CS_PIN, GPIO_PIN_SET);
}

uint8_t BspSdSpiReadWriteByte(uint8_t data) {
    uint8_t rxdata = 0;
    HAL_SPI_TransmitReceive(&sd_hspi, &data, &rxdata, 1, 1000);
    return rxdata;
}

uint8_t BspDetRead(void) {

    if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(SD_DET_PORT, SD_DET_PIN)) { return 0; }
    else return 1;
}

uint32_t BspSpiAutoSpeed(void) {

    uint16_t get_clk = (HAL_RCC_GetHCLKFreq() / 1000000) / 2; 

    uint8_t sd_spi_min_clk_div = get_clk / 8;       // 8兆需要高分频

    if(sd_spi_min_clk_div <= 2)         return SPI_BAUDRATEPRESCALER_2;
    else if(sd_spi_min_clk_div <= 4)    return SPI_BAUDRATEPRESCALER_4;
    else if(sd_spi_min_clk_div <= 8)    return SPI_BAUDRATEPRESCALER_8;
    else if(sd_spi_min_clk_div <= 16)    return SPI_BAUDRATEPRESCALER_16;
    else if(sd_spi_min_clk_div <= 32)    return SPI_BAUDRATEPRESCALER_32;
    else return SPI_BAUDRATEPRESCALER_256;
}


void SdSpiDrvDeinit(void) {
    _SD_GPIO_CLK_DISABLE();
    HAL_SPI_DeInit(&sd_hspi);
}

void SdSpiDrvInit(void) {
    BspSdSpiGpioInit();         /* Init SD SPI GPIO */
    BspSpiInit();               /* Init SD SPI */
}


#endif
