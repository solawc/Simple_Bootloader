#ifndef __pins_mks_yz_cnc_v1_h
#define __pins_mks_yz_cnc_v1_h

#define CUSTOM_BOARD_NAME               "YZ_CNC_V1.0"

#define BL_NAME                         "1:/YZ_CNC_V1.bin"
#define BL_OLD_NAME                     "1:/YZ_CNC_V1.CUR"

#define MCU_RAM                         KB(128)
#define MCU_FLASH                       KB(256)
#define BL_SIZE                         KB(32)
#define BL_OFFSET                       ((uint32_t)0X8000)
#define APP_STAR_ADDR                   ((uint32_t)0x8000000 + BL_OFFSET) 

/******************************************************************************
 *                              UART Define
*******************************************************************************/
#define  __HAL_UART_CLK(uart)	        __HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)                uart##_IRQn

#define DEBUG_UART		                USART1
#define DEBUG_UART_IRQn                 UART_IRQn(USART1)
#define DEBUG_UART_CLK_ENABLE()         __HAL_UART_CLK(USART1)
#define DEBUG_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 
#define DEBUG_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 
#define DEBUG_UART_TX_PORT              GPIOA
#define DEBUG_UART_TX_PIN               GPIO_PIN_9
#define DEBUG_UART_RX_PORT              GPIOA
#define DEBUG_UART_RX_PIN               GPIO_PIN_10
#define DEBUG_UART_AF_MODE              GPIO_MODE_AF_PP
#define DEBUG_UART_IRQHANDLER           USART1_IRQHandler


/******************************************************************************
 *                              SDCard Define
*******************************************************************************/
#define SD_USE_SPI 
// #define SD_USE_SDIO              
#define BOARD_SD_SPI                    SPI2
#define BOARD_SD_SCK_PORT               GPIOB
#define BOARD_SD_SCK_PIN                GPIO_PIN_13
#define BOARD_SD_MISO_PORT              GPIOB
#define BOARD_SD_MISO_PIN               GPIO_PIN_14
#define BOARD_SD_MOSI_PORT              GPIOB
#define BOARD_SD_MOSI_PIN               GPIO_PIN_15
#define BOARD_SD_CS_PORT                GPIOB
#define BOARD_SD_CS_PIN                 GPIO_PIN_12
#define BOARD_SD_DET_PORT               GPIOB
#define BOARD_SD_DET_PIN                GPIO_PIN_11
#define BOARD_SD_GPIO_AF                GPIO_AF5_SPI2

#define _SD_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE();\
                                        __HAL_RCC_SPI2_CLK_ENABLE()

#define _SD_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE();\
                                        __HAL_RCC_SPI2_CLK_DISABLE()

#endif
