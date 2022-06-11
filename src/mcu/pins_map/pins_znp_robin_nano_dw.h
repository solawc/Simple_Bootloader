#ifndef __pins_znp_robin_nano_dw_h
#define __pins_znp_robin_nano_dw_h

#define MKS_BOARD_NAME      "ZNP ROBIN NANO DW"

#define BL_NAME             "1:/ZNP_ROBIN_NANO.bin"
#define BL_OLD_NAME         "1:/ZNP_ROBIN_NANO.CUR"

#define BOARD_SD_SCK_PORT   GPIOB
#define BOARD_SD_SCK_PIN    GPIO_PIN_13

#define BOARD_SD_MISO_PORT  GPIOB
#define BOARD_SD_MISO_PIN   GPIO_PIN_14

#define BOARD_SD_MOSI_PORT  GPIOB
#define BOARD_SD_MOSI_PIN   GPIO_PIN_15

#define BOARD_SD_CS_PORT    GPIOB
#define BOARD_SD_CS_PIN     GPIO_PIN_12

#define BOARD_SD_DET_PORT   GPIOC
#define BOARD_SD_DET_PIN    GPIO_PIN_3

#define DEBUG_UART		                USART1
#define DEBUG_UART_IRQn                 UART_IRQn(USART1)
#define DEBUG_UART_CLK_ENABLE()         __HAL_UART_CLK(USART1)
#define DEBUG_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define DEBUG_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define DEBUG_UART_TX_PORT              GPIOA
#define DEBUG_UART_TX_PIN               GPIO_PIN_9
#define DEBUG_UART_RX_PORT              GPIOA
#define DEBUG_UART_RX_PIN               GPIO_PIN_10
#define DEBUG_UART_AF_MODE              GPIO_AF7_USART1
#define DEBUG_UART_IRQHANDLER           USART1_IRQHandler


#endif
