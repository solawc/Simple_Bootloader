#ifndef __sd_spi_drv_h
#define __sd_spi_drv_h

#include "../../main.h"

/*
 * How to select sd speed?
 * 1. SD support 12M/s or 48M/s
 * but we use SPI to driver SDCard, so the speed
 * will be slow, when we need to init sd to begein,
 * you must set SPI_BAUDRATEPRESCALER_256 at STM32,
 * or if you use NXP or other MCU, for example TI or
 * HC32, or AT32, you just set the most slow speed.
 * 
 * 2. When the spi need to trans data to sdcard, the 
 * speed need to set between 8M/s and 12M/s, is SD_SPI_SPEED
 *
*/
#define SD_SPI_SPEED            SPI_BAUDRATEPRESCALER_4       
#define SD_SPI_LOW_SPEED        SPI_BAUDRATEPRESCALER_256
          
#ifdef SD_USE_SPI

    #define SD_CARD_SPI             BOARD_SD_SPI

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

        #ifndef _SD_GPIO_CLK_ENABLE
                #define _SD_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE();\
                                                __HAL_RCC_GPIOA_CLK_ENABLE();\
                                                __HAL_RCC_GPIOC_CLK_ENABLE();\
                                                __HAL_RCC_SPI2_CLK_ENABLE()
        #endif

        #ifndef _SD_GPIO_CLK_DISABLE
                #define _SD_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE();\
                                                __HAL_RCC_GPIOC_CLK_DISABLE();\
                                                __HAL_RCC_SPI2_CLK_DISABLE()
        #endif

    #endif /* SD_CARD_SPI */

#endif /* SD_USE_SPI */


void BspSdBegin();
void BspSdEnd();
uint8_t BspSdSpiReadWriteByte(uint8_t data);
uint8_t BspDetRead(void);
uint32_t BspSpiAutoSpeed(void);
uint8_t BspDetRead(void);
void SdSpiDrvDeinit(void);
void SdSpiDrvInit(void);
uint8_t SdDrvInitAll(void);
uint8_t SdSpiReadBuff(uint8_t*buf,uint32_t sector,uint8_t cnt);
uint8_t SdSpiWriteBuff(uint8_t*buf,uint32_t sector,uint8_t cnt);
uint32_t SdGetSectorCount(void);
#endif
