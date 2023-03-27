/*
 * Author: sola    
 * Fix time:2022-01-20
 * 
*/

#include "hal_uart.h"

UART_HandleTypeDef debug_uart;

void hal_uart_gpio_init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	DEBUG_UART_CLK_ENABLE();
	DEBUG_UART_TX_CLK_ENABLE();
	DEBUG_UART_RX_CLK_ENABLE();

	GPIO_InitStruct.Pin = DEBUG_UART_TX_PIN|DEBUG_UART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	#ifdef DEBUG_UART_AF_MODE
    GPIO_InitStruct.Alternate = DEBUG_UART_AF_MODE;	
	#endif
    HAL_GPIO_Init(DEBUG_UART_TX_PORT, &GPIO_InitStruct);
}

void hal_uart_init(void) {

	hal_uart_gpio_init();

    debug_uart.Instance = DEBUG_UART;
	debug_uart.Init.BaudRate = 115200;
	debug_uart.Init.WordLength = UART_WORDLENGTH_8B;
	debug_uart.Init.StopBits = UART_STOPBITS_1;
	debug_uart.Init.Parity = UART_PARITY_NONE;
	debug_uart.Init.Mode = UART_MODE_TX_RX;
	debug_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	debug_uart.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&debug_uart) != HAL_OK)
  	{
    	Error_Handler();
  	}

#ifdef STM32G0B0xx
	if (HAL_UARTEx_SetTxFifoThreshold(&laser_uart, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&laser_uart, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&laser_uart) != HAL_OK)
	{
		Error_Handler();
	}
#endif
}

void hal_uart_rx_irq_enable(void) {
	HAL_NVIC_SetPriority(DEBUG_UART_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DEBUG_UART_IRQn);
	__HAL_UART_ENABLE_IT(&debug_uart, UART_IT_RXNE);
	// __HAL_UART_ENABLE_IT(&debug_uart, UART_IT_IDLE);
}

uint32_t hal_get_uart_rx_flag(void) {

	return __HAL_UART_GET_FLAG(&debug_uart, UART_FLAG_RXNE);
}

uint32_t hal_get_uart_idle_flag(void) {

	return __HAL_UART_GET_FLAG(&debug_uart, UART_FLAG_IDLE);
}

#ifdef RDR
#define USAR_READ_REG			RDR
#else 
#define USAR_READ_REG			DR
#endif

uint8_t BspUartReadData(void) { 
	return debug_uart.Instance->USAR_READ_REG;
}

#ifdef __CC_ARM
int fputc(int ch,FILE *f)
{
    uint32_t temp = ch;
    HAL_UART_Transmit(&debug_uart, (uint8_t *)&temp, 1, 1000);    
    return ch;
}
#else 
int _write(int fd, char *ptr, int len)
{	
	HAL_UART_Transmit(&debug_uart, (uint8_t *)ptr, len, 1000);    
	return len;
}
#endif