#ifndef __hal_spi_h
#define __hal_spi_h

#include "../main.h"


extern SPI_HandleTypeDef sd_hspi;

#define W25QXX_SPI              

#ifdef SD_USE_SPI
    #define SD_CARD_SPI         SPI2

    #ifdef SD_CARD_SPI
    #ifndef BOARD_SD_MISO_PORT
        #define SD_SPI_MISO_PORT    GPIOB
        #define SD_SPI_MISO_PIN     GPIO_PIN_14
    #else 
        #define SD_SPI_MISO_PORT    BOARD_SD_MISO_PORT
        #define SD_SPI_MISO_PIN     BOARD_SD_MISO_PIN
    #endif

    #ifndef BOARD_SD_MOSI_PORT
        #define SD_SPI_MOSI_PORT    GPIOB
        #define SD_SPI_MOSI_PIN     GPIO_PIN_15
    #else 
        #define SD_SPI_MOSI_PORT    BOARD_SD_MOSI_PORT
        #define SD_SPI_MOSI_PIN     BOARD_SD_MOSI_PIN
    #endif

    #ifndef BOARD_SD_SCK_PORT
        #define SD_SPI_SCK_PORT     GPIOB
        #define SD_SPI_SCK_PIN      GPIO_PIN_13
    #else
        #define SD_SPI_SCK_PORT     BOARD_SD_SCK_PORT
        #define SD_SPI_SCK_PIN      BOARD_SD_SCK_PIN
    #endif

    #ifndef BOARD_SD_CS_PORT
        #define SD_SPI_CS_PORT      GPIOB
        #define SD_SPI_CS_PIN       GPIO_PIN_12
    #else
        #define SD_SPI_CS_PORT      BOARD_SD_CS_PORT
        #define SD_SPI_CS_PIN       BOARD_SD_CS_PIN
    #endif

    #ifndef BOARD_SD_DET_PORT
        #define SD_DET_PORT         GPIOC
        #define SD_DET_PIN          GPIO_PIN_3
    #else
        #define SD_DET_PORT         BOARD_SD_DET_PORT
        #define SD_DET_PIN          BOARD_SD_DET_PIN
    #endif


        #define _SD_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE();\
                                        __HAL_RCC_GPIOA_CLK_ENABLE();\
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
void hal_sd_register(void);

#endif
