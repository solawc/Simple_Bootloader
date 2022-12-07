#include "HID_boot_port.h"

// #define BOOT_1_PIN          GPIO_PIN_2 //DIYMROE STM32F407VGT board (Button PD15, LED PE0)
// #define BOOT_1_PORT         GPIOB
// #define BOOT_1_ENABLED      GPIO_PIN_RESET
// #define BOOT_1_CLK_EN()     __HAL_RCC_GPIOB_CLK_ENABLE()

// #define BOOT_HID_LED_PIN        GPIO_PIN_0
// #define BOOT_HID_LED_PORT       GPIOE


void usleep(uint32_t us) {

    while(us-- ) {

        __NOP();
    }
}

extern uint32_t hidTick;
void HID_BootDelayMs(uint32_t ms) {
    // HAL_Delay(ms);
    hidTick = ms;
    while(hidTick--);
}

uint32_t bootGet_BAK_Register(void) {

    register uint32_t tmp = 0U;

    tmp = (uint32_t)(&(RTC->BKP0R));
    tmp += (HID_MAGIC_NUMBER_BKP_INDEX * 4U);

    /* Read the specified register */
    return (*(__IO uint32_t *)tmp);
}

void bootSet_EnableBkUpAccess(void) {
    SET_BIT(PWR->CR, PWR_CR_DBP);
}

void bootSet_DisableBkUpAccess(void) {
    CLEAR_BIT(PWR->CR, PWR_CR_DBP);
}

void bootSet_BAK_Register(void) {
    register uint32_t tmp = 0U;

  tmp = (uint32_t)(&(RTC->BKP0R));
  tmp += (HID_MAGIC_NUMBER_BKP_INDEX * 4U);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)0;

}


void boot_GPIO_Init(void) {

#ifdef BOOT_1_PIN

    GPIO_InitTypeDef GPIO_InitStruct;


    BOOT_1_CLK_EN();

    GPIO_InitStruct.Pin = BOOT_1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BOOT_1_PORT, &GPIO_InitStruct);
#endif

#ifdef BOOT_HID_LED_PIN
    GPIO_InitStruct.Pin = BOOT_HID_LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BOOT_HID_LED_PORT, &GPIO_InitStruct);
#endif
}


uint8_t bootGet_Boot_1_Pin(void) {

#ifdef BOOT_1_PIN
    if(HAL_GPIO_ReadPin(BOOT_1_PORT, BOOT_1_PIN)) return 1;
    else return 0;
#else   
    return 1;
#endif
}

void bootSet_BootLED(uint8_t ledState) {
    HAL_GPIO_WritePin(BOOT_LED_PORT, BOOT_LED_PIN, ledState);
}


void bootSendReport(uint8_t *report, uint16_t len) {
    HAL_UART_Transmit(&debug_uart, report, len, 1000);
}

void boot_writeFlash() {
    // TODO..
}

