#ifndef __pins_mks_nano_v3_h
#define __pins_mks_nano_v3_h

#define CUSTOM_BOARD_NAME               "MKS Robin Nano V3"

#define BL_NAME                         "1:/Robin_nano_v3.bin"
#define BL_OLD_NAME                     "1:/Robin_nano_v3.CUR"

#define SD_USE_SPI    
#define BOARD_SD_SPI                    SPI3
#define BOARD_SD_SCK_PORT               GPIOC
#define BOARD_SD_SCK_PIN                GPIO_PIN_10
#define BOARD_SD_MISO_PORT              GPIOC
#define BOARD_SD_MISO_PIN               GPIO_PIN_11
#define BOARD_SD_MOSI_PORT              GPIOC
#define BOARD_SD_MOSI_PIN               GPIO_PIN_12
#define BOARD_SD_CS_PORT                GPIOC
#define BOARD_SD_CS_PIN                 GPIO_PIN_9
#define BOARD_SD_DET_PORT               GPIOD
#define BOARD_SD_DET_PIN                GPIO_PIN_12
#define BOARD_SD_GPIO_AF                GPIO_AF6_SPI3

#define _SD_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE();\
                                        __HAL_RCC_GPIOC_CLK_ENABLE();\
                                        __HAL_RCC_GPIOD_CLK_ENABLE();\
                                        __HAL_RCC_SPI3_CLK_ENABLE()

#define _SD_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE();\
                                        __HAL_RCC_GPIOC_CLK_DISABLE();\
                                        __HAL_RCC_GPIOD_CLK_DISABLE();\
                                        __HAL_RCC_SPI3_CLK_DISABLE()


#define DEBUG_UART		                USART3
#define DEBUG_UART_IRQn                 UART_IRQn(USART3)
#define DEBUG_UART_CLK_ENABLE()         __HAL_UART_CLK(USART3)
#define DEBUG_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE();
#define DEBUG_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE();
#define DEBUG_UART_TX_PORT              GPIOB
#define DEBUG_UART_TX_PIN               GPIO_PIN_10
#define DEBUG_UART_RX_PORT              GPIOB
#define DEBUG_UART_RX_PIN               GPIO_PIN_11
#define DEBUG_UART_AF_MODE              GPIO_AF7_USART3
#define DEBUG_UART_IRQHANDLER           USART3_IRQHandler

#endif
