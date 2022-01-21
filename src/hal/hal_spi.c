#include "hal_spi.h"


#ifdef SD_CARD_SPI

static void sd_spi_pin_init() {

    GPIO_InitTypeDef SPI_GPIO_Init;

    // __HAL_RCC_GPIOB_CLK_ENABLE();
    // __HAL_RCC_GPIOC_CLK_ENABLE();

    // __HAL_RCC_SPI_CLK_ENABLE();

    _SD_GPIO_CLK_ENABLE();

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




#endif
