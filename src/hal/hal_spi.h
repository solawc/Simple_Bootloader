#ifndef __hal_spi_h
#define __hal_spi_h

#include "../main.h"


extern SPI_HandleTypeDef sd_hspi;

#define W25QXX_SPI              

#ifdef SD_USE_SPI
    #define SD_CARD_SPI         SPI2
#ifdef SD_CARD_SPI
    #define SD_SPI_MISO_PORT    GPIOB
    #define SD_SPI_MISO_PIN     GPIO_PIN_14
    #define SD_SPI_MOSI_PORT    GPIOB
    #define SD_SPI_MOSI_PIN     GPIO_PIN_15
    #define SD_SPI_SCK_PORT     GPIOB
    #define SD_SPI_SCK_PIN      GPIO_PIN_13
    #define SD_SPI_CS_PORT      GPIOB
    #define SD_SPI_CS_PIN       GPIO_PIN_12
    #define SD_DET_PORT         GPIOC
    #define SD_DET_PIN          GPIO_PIN_13

    #define _SD_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE();\
                                    __HAL_RCC_GPIOC_CLK_ENABLE();\
                                    __HAL_RCC_SPI2_CLK_ENABLE()

    #define _SD_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE();\
                                    __HAL_RCC_GPIOC_CLK_DISABLE();\
                                    __HAL_RCC_SPI2_CLK_DISABLE()
#endif

#endif





void hal_sd_init();
void hal_sd_deinit(void);
void hal_sd_enable(void);
void hal_sd_disable(void);
uint8_t hal_sd_read_byte(void);
uint8_t hal_sd_read_write_byte(uint8_t data);

#endif
