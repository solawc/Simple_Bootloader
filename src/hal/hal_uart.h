#ifndef __hal_uart_h
#define __hal_uart_h

#include "../main.h"
#include "stdio.h"

extern UART_HandleTypeDef debug_uart;

#define  __HAL_UART_CLK(uart)	__HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)        uart##_IRQn

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

#if DEBUG_SWITCH
#define HAS_DEBUG_INFO
#define DEBUG_ERROR(fmt,arg...)        do{printf("<<-ERROR->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)
#define DEBUG_PRINT(fmt,arg...)        do{printf("<<-DEBUG->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)   
#define DEBUG_PRINTF(fmt, arg...)      do{printf(fmt, ##arg);}while(0)  
#else
#define DEBUG_ERROR(fmt,arg...)
#define DEBUG_PRINT(fmt,arg...)
#define DEBUG_PRINTF(fmt, arg...)      
#endif 








void hal_uart_gpio_init(void);
void hal_uart_init(void);
#endif
