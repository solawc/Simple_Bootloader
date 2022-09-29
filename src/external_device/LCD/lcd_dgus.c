#include "lcd_dgus.h"

#ifdef LCD_DGUS_DWIN

UART_HandleTypeDef dgus_huart;

const uint8_t DGUS_HEADER1 = 0x5A;
const uint8_t DGUS_HEADER2 = 0xA5;

const uint8_t DGUS_CMD_WRITEVAR = 0x82;
const uint8_t DGUS_CMD_READVAR = 0x83;

uint8_t DGUS_RST_SCREEN = 0;
uint8_t DGUS_STAT_SCREEN = 1;
uint8_t DGUS_BOOT_SCREEN = 92;


static void lcd_dgus_uart_gpio_init(void) {

    GPIO_InitTypeDef GPIO_Init;

    LCD_DGUS_TX_PIN_CLK_EN();
    LCD_DGUS_RX_PIN_CLK_EN();
    LCD_DGUS_CLK_EN();
    
    GPIO_Init.Alternate = LCD_DGUA_TX_AF;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pin = LCD_DGUS_TX_PIN;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_DGUS_TX_PORT, &GPIO_Init);

    GPIO_Init.Alternate = LCD_DGUA_RX_AF;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pin = LCD_DGUS_RX_PIN;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_DGUS_RX_PORT, &GPIO_Init);
}

static void lcd_dgus_uart_init(uint32_t baud) {

    lcd_dgus_uart_gpio_init();

    dgus_huart.Instance = LCD_DGUS_UART;
	dgus_huart.Init.BaudRate = baud;
	dgus_huart.Init.WordLength = UART_WORDLENGTH_8B;
	dgus_huart.Init.StopBits = UART_STOPBITS_1;
	dgus_huart.Init.Parity = UART_PARITY_NONE;
	dgus_huart.Init.Mode = UART_MODE_TX_RX;
	dgus_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	dgus_huart.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&dgus_huart) != HAL_OK)
  	{
    	Error_Handler();
  	}
}
 
void lcd_dgus_init(void) {

    lcd_dgus_uart_init(LCD_DGUS_BAUD);
}


void dgus_uart_send_data(uint8_t data) {

    HAL_UART_Transmit(&dgus_huart, &data, 1, 1000);
}

void dgus_write_header(uint16_t adr, uint8_t cmd, uint8_t payloadlen) {

    dgus_uart_send_data(DGUS_HEADER1);
    dgus_uart_send_data(DGUS_HEADER2);
    dgus_uart_send_data(payloadlen + 3);
    dgus_uart_send_data(cmd);
    dgus_uart_send_data(adr >> 8);
    dgus_uart_send_data(adr & 0xFF);
}

void dgus_writeVariable(uint16_t adr, const void *values, uint8_t valueslen, bool isstr) {
    const char* myvalues = (char *)values;
    bool strend = !myvalues;
    dgus_write_header(adr, DGUS_CMD_WRITEVAR, valueslen);

    while (valueslen--) {
    char x = 0;
    if (!strend) x = *myvalues++;
    if ((isstr && !x) || strend) {
      strend = true;
      x = ' ';
    }
    dgus_uart_send_data(x);
  }
}

void dgus_write_uint16_value(uint16_t adr, uint16_t value) {
    value = (value & 0xFFU) << 8U | (value >> 8U);
    dgus_writeVariable(adr, (void*)(&value), sizeof(uint16_t), false);
}

void dgus_write_int16_value(uint16_t adr, int16_t value) {
    value = (value & 0xFFU) << 8U | (value >> 8U);
    dgus_writeVariable(adr, (void*)(&value), sizeof(uint16_t), false);
}

void dgus_write_uint8_value(uint16_t adr, uint8_t value) {
    dgus_writeVariable(adr, (void*)(&value), sizeof(uint8_t), false);
}

void dgus_write_int8_value(uint16_t adr, uint8_t value) {
    dgus_writeVariable(adr, (void*)(&value), sizeof(int8_t), false);
}

void dgus_reques_screen(uint8_t screen) {
    const unsigned char gotoscreen[] = { 0x5A, 0x01, (unsigned char) (screen >> 8U), (unsigned char) (screen & 0xFFU) };
    dgus_writeVariable(0x84, gotoscreen, sizeof(gotoscreen), false);
}

void dgus_go_to_screen(uint8_t screen) {
    dgus_reques_screen(screen);
}

void jump_into_boot_screen(void) {
    dgus_go_to_screen(DGUS_BOOT_SCREEN);
}

void jump_to_rst(void) {
    dgus_go_to_screen(DGUS_RST_SCREEN);
}

void jump_to_star(void) {
    dgus_go_to_screen(DGUS_STAT_SCREEN);
}
 
#endif //LCD_DGUS_DWIN

