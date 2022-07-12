#ifndef __lcd_dgus_h
#define __lcd_dgus_h

#include "../../main.h"

#ifdef LCD_DGUS_DWIN

#define LCD_DGUS_UART               USART6
#define LCD_DGUS_BAUD               115200
#define LCD_DGUS_CLK_EN()           __HAL_RCC_USART6_CLK_ENABLE()

#define LCD_DGUS_TX_PORT            GPIOA
#define LCD_DGUS_TX_PIN             GPIO_PIN_11
#define LCD_DGUA_TX_AF              GPIO_AF8_USART6
#define LCD_DGUS_TX_PIN_CLK_EN()    __HAL_RCC_GPIOA_CLK_ENABLE()

#define LCD_DGUS_RX_PORT            GPIOA
#define LCD_DGUS_RX_PIN             GPIO_PIN_12
#define LCD_DGUA_RX_AF              GPIO_AF8_USART6
#define LCD_DGUS_RX_PIN_CLK_EN()    __HAL_RCC_GPIOA_CLK_ENABLE()

void lcd_dgus_init(void);
void dgus_go_to_screen(uint8_t screen);
void jump_into_boot_screen(void);
void jump_to_rst(void);
void jump_to_star(void);

#endif

#endif
