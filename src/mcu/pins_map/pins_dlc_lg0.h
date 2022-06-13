#ifndef __pins_dlc_lg0_h
#define __pins_dlc_lg0_h

#define MKS_BOARD_NAME      "DLC LG0 v2.0"

#define BL_NAME             "1:/DLC_LG0_V2.bin"
#define BL_OLD_NAME         "1:/DLC_LG0_V2.CUR"



#define BOARD_SD_SPI        SPI1
#define BOARD_SD_SCK_PORT   GPIOA
#define BOARD_SD_SCK_PIN    GPIO_PIN_5
#define BOARD_SD_MISO_PORT  GPIOA
#define BOARD_SD_MISO_PIN   GPIO_PIN_6
#define BOARD_SD_MOSI_PORT  GPIOA
#define BOARD_SD_MOSI_PIN   GPIO_PIN_7
#define BOARD_SD_CS_PORT    GPIOA
#define BOARD_SD_CS_PIN     GPIO_PIN_4
#define BOARD_SD_DET_PORT   GPIOB
#define BOARD_SD_DET_PIN    GPIO_PIN_0
#define BOARD_SD_GPIO_AF    GPIO_AF0_SPI1

#define _SD_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE();\
                                __HAL_RCC_GPIOA_CLK_ENABLE();\
                                __HAL_RCC_GPIOC_CLK_ENABLE();\
                                __HAL_RCC_SPI1_CLK_ENABLE()

#define _SD_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE();\
                                __HAL_RCC_GPIOC_CLK_DISABLE();\
                                __HAL_RCC_SPI1_CLK_DISABLE()


#define DEBUG_UART		                USART2
#define DEBUG_UART_IRQn                 UART_IRQn(USART2)
#define DEBUG_UART_CLK_ENABLE()         __HAL_UART_CLK(USART2)
#define DEBUG_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define DEBUG_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define DEBUG_UART_TX_PORT              GPIOA
#define DEBUG_UART_TX_PIN               GPIO_PIN_2
#define DEBUG_UART_RX_PORT              GPIOA
#define DEBUG_UART_RX_PIN               GPIO_PIN_3
#define DEBUG_UART_AF_MODE              GPIO_AF1_USART2
#define DEBUG_UART_IRQHANDLER           USART2_IRQHandler


#endif
