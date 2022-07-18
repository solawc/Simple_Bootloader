#ifndef __hal_sdio_H
#define __hal_sdio_H

#include "../main.h"

#if 0

extern SD_HandleTypeDef sd_hsdio;

#ifdef  SD_USE_SDIO
    #define SD_CARD_SDIO        SDIO

    #ifdef SD_CARD_SDIO
        #define SD_SDIO_CMD_PORT            GPIOD
        #define SD_SDIO_CMD_PIN             GPIO_PIN_2
        #define SD_SDIO_CLK_PORT            GPIOC
        #define SD_SDIO_CLK_PIN             GPIO_PIN_12
        #define SD_SDIO_D0_PORT             GPIOC
        #define SD_SDIO_D0_PIN              GPIO_PIN_8
        #define SD_SDIO_D1_PORT             GPIOC
        #define SD_SDIO_D1_PIN              GPIO_PIN_9
        #define SD_SDIO_D2_PORT             GPIOC
        #define SD_SDIO_D2_PIN              GPIO_PIN_10
        #define SD_SDIO_D3_PORT             GPIOC
        #define SD_SDIO_D3_PIN              GPIO_PIN_11

        #define   SD_TRANSFER_OK                ((uint8_t)0x00)
        #define   SD_TRANSFER_BUSY              ((uint8_t)0x01)

        
    #define _SD_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE();\
                                    __HAL_RCC_GPIOD_CLK_ENABLE();\
                                    __HAL_RCC_SDIO_CLK_ENABLE()

    #define _SD_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOC_CLK_DISABLE();\
                                    __HAL_RCC_GPIOD_CLK_DISABLE();\
                                    __HAL_RCC_SDIO_CLK_DISABLE()

    #endif

#endif

static void WIFI_PDN_INIT(void);
void hal_sd_init(void);
void hal_sd_read_block(uint32_t *pData, uint32_t ReadAddr,uint32_t NumberOfBlocks);
void hal_sd_write_block(uint32_t *pData, uint32_t WriteAddr,uint32_t NumberOfBlocks);
uint8_t hal_sd_get_cardstate(void);
uint8_t hal_sd_erase(uint32_t StartAddr, uint32_t EndAddr);
void hal_sd_get_cardinfo(HAL_SD_CardInfoTypeDef *CardInfo);
void hal_sd_get_cardcsd(HAL_SD_CardCSDTypeDef *pCSD);
void hal_sd_deinit(void);
void hal_sd_register(void);

#endif

#endif