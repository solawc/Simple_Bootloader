#include "hal_spi.h"

SPI_HandleTypeDef sd_hspi;

#ifdef SD_CARD_SPI

static void sd_spi_pin_init(void) {

    GPIO_InitTypeDef SPI_GPIO_Init;

    _SD_GPIO_CLK_ENABLE();                          // Enable SPI and GPIO Clock

    SPI_GPIO_Init.Alternate = GPIO_AF5_SPI2;
    SPI_GPIO_Init.Mode = GPIO_MODE_AF_PP;
    SPI_GPIO_Init.Pin = SD_SPI_MISO_PIN|
                        SD_SPI_MOSI_PIN|
                        SD_SPI_SCK_PIN;
    SPI_GPIO_Init.Pull = GPIO_NOPULL;
    SPI_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_SPI_SCK_PORT, &SPI_GPIO_Init);

    SPI_GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    SPI_GPIO_Init.Pin = SD_SPI_CS_PIN;
    SPI_GPIO_Init.Pull = GPIO_PULLUP;
    SPI_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_SPI_CS_PORT, &SPI_GPIO_Init);

    SPI_GPIO_Init.Mode = GPIO_MODE_INPUT;
    SPI_GPIO_Init.Pin = SD_DET_PIN;
    SPI_GPIO_Init.Pull = GPIO_NOPULL;
    SPI_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_DET_PORT, &SPI_GPIO_Init);
}

static void sd_spi_init(void) {

    sd_hspi.Instance = SD_CARD_SPI;
    sd_hspi.Init.BaudRatePrescaler = SD_SPI_SPEED;
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
    if (HAL_SPI_Init(&sd_hspi) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(&sd_hspi);
}

void hal_sd_enable(void) {
    HAL_GPIO_WritePin(SD_SPI_CS_PORT, SD_SPI_CS_PIN, GPIO_PIN_RESET);
}

void hal_sd_disable(void) {
    HAL_GPIO_WritePin(SD_SPI_CS_PORT, SD_SPI_CS_PIN, GPIO_PIN_SET);
}

uint8_t hal_sd_read_write_byte(uint8_t data) {
    uint8_t rxdata = 0;
    HAL_SPI_TransmitReceive(&sd_hspi, &data, &rxdata, 1, 1000);
    return rxdata;
}

void hal_sd_init(void) {
    sd_spi_pin_init();      // set gpio init
    sd_spi_init();          // set spi init
}




#endif
