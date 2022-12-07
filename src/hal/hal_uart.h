#ifndef __hal_uart_h
#define __hal_uart_h

#include "../main.h"
#include "stdio.h"

extern UART_HandleTypeDef debug_uart;

#define  __HAL_UART_CLK(uart)	        __HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)                uart##_IRQn

#ifdef DEBUG_SWITCH
#define HAS_DEBUG_INFO
#define DEBUG_ERROR(fmt,arg...)         do{printf("<<-ERROR->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)
#define DEBUG_PRINT(fmt,arg...)         do{printf("<<-DEBUG->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)   
#define DEBUG_PRINTF(fmt, arg...)       do{printf(fmt, ##arg);}while(0)  
#else
#define DEBUG_ERROR(fmt,arg...)
#define DEBUG_PRINT(fmt,arg...)
#define DEBUG_PRINTF(fmt, arg...)      
#endif 

#define INFO_PRINT(fmt,arg...)          do{printf("<<-INFO->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)  


void hal_uart_gpio_init(void);
void hal_uart_init(void);
void hal_uart_rx_irq_enable(void);
uint32_t hal_get_uart_rx_flag(void);
uint8_t BspUartReadData(void);
#endif
