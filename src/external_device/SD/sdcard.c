#include "sdcard.h"

void set_sd_spi_speed(uint8_t SPI_BaudRatePrescaler) {

    sd_hspi.Init.BaudRatePrescaler = SD_SPI_LOW_SPEED;
    HAL_SPI_Init(&sd_hspi);
    __HAL_SPI_ENABLE(&sd_hspi);
}



