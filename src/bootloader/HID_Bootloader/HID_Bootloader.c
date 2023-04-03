/*
 HID_Bootloader.c

 Copyright (c) 2021-2023 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

/*
  Note:
  HID bootloader is originally an open source software, which can 
  be updated through USB/Serial. It originally adapted STM32F1XX and STM32F4XX, 
  and compiled using GCC+Makefile. The actual application is mainly to be 
  compatible with Arduino protocol, so that STM32F1XX and STM32F4XX can burn 
  firmware and update through Arduino.
  Info:
  +-----------------------------------------------------------------------+
  |         HID-Flash v2.2.1 - STM32 HID Bootloader Flash Tool            |
  |     (c)      2018 - Bruno Freitas       http://www.brunofreitas.com   |
  |     (c) 2018-2019 - Vassilis Serasidis  https://www.serasidis.gr      |
  |   Customized for STM32duino ecosystem   https://www.stm32duino.com    |
  +-----------------------------------------------------------------------+
*/

#include "HID_Bootloader.h"


uint32_t magic_val;

#define READ_FILE_PAGE_SIZE             ((uint16_t)0x400)  
uint32_t    *hlfP;

volatile uint8_t new_data_is_received = 0;  // 用来标志是否有数据过来  
volatile uint32_t hidTick = 0;              // TickDelay
volatile uint32_t hidTickTimeOut = TIME_OUT;              

static uint8_t CMD_SIGNATURE[7]         = {'B','T','L','D','C','M','D'};
static uint8_t CMD_DATA_RECEIVED[8]     = {'B','T','L','D','C','M','D',0x02};
static uint8_t CMD_OK_ACK[2]            = {'O', 'K'};

const uint8_t CMD_RESET_PAGES_BUFF[]             = "BLTTTTTT";

uint8_t USB_RX_Buffer[HID_RX_SIZE];

HID_RX_t bootRX;
uint8_t isHaveCMD = 0;

uint8_t getCmdFlag = 0;

uint8_t compareCMD(void);
void searchCMD(uint8_t data);

void HID_Bootloader_Task(void) {

    /* Init bootloader GPIO. if you need. */
    boot_GPIO_Init();  

    /* Reset UART RX buff. */
    memset(bootRX.hid_rx_buff, 0, sizeof(bootRX.hid_rx_buff));
    bootRX.hid_rx_len = 0;      

    /* Get MCU restart data. */
    magic_val = bootGet_BAK_Register(); 

    /* wait 6s to connect bootloader */
    hidTick = 6000;
    while(hidTick) {
        isHaveCMD = compareCMD();
        if(isHaveCMD) break;
    }

    /* if no, jump to app now. */
    if(!isHaveCMD) {    
        // typedef void (*pFunction)(void);
        // pFunction Jump_To_Application;
        // uint32_t JumpAddress;

        // JumpAddress = *(__IO uint32_t*) (FLASH_BASE + USER_CODE_OFFSET + 4);
        // Jump_To_Application = (pFunction) JumpAddress;
        // __set_MSP(*(uint32_t *) (FLASH_BASE + USER_CODE_OFFSET));
        // Jump_To_Application();

        msp = *((uint32_t *)(APP_STAR_ADDR));
        reset = *((uint32_t *)(APP_STAR_ADDR + 4));
        bl_jump_to_app(APP_STAR_ADDR, msp, reset);
    }

    HAL_Delay(100);         // 确保中断里面没有数据进行接收

    memset(bootRX.hid_rx_buff, 0, sizeof(bootRX.hid_rx_buff));
    bootRX.hid_rx_len = 0;

    // bootSet_EnableBkUpAccess();
    // bootSet_BAK_Register();
    // bootSet_DisableBkUpAccess();

    bootSendReport(CMD_OK_ACK, 2);

    static volatile uint32_t writeAddr = FLASH_BASE + USER_CODE_OFFSET;

    hidTickTimeOut = TIME_OUT;

    while(1) {

        /* 超时 */
        if(hidTickTimeOut == 0) {
            HAL_NVIC_SystemReset();
        }

        if(new_data_is_received == 1) {     // 有64buff数据

            hidTickTimeOut = TIME_OUT;

            new_data_is_received = 0;

            memset(USB_RX_Buffer, 0, sizeof(USB_RX_Buffer));
            memcpy(USB_RX_Buffer, bootRX.hid_rx_buff, sizeof(bootRX.hid_rx_buff));
            memset(bootRX.hid_rx_buff, 0, sizeof(bootRX.hid_rx_buff));


            if (memcmp(USB_RX_Buffer, CMD_SIGNATURE, sizeof (CMD_SIGNATURE)) == 0) {
                switch(USB_RX_Buffer[7]) {
                    case 0x01:
                        HAL_NVIC_SystemReset();
                    break;
                }
            }else {
                bootRX.hid_rx_len = 0; // 从0开始继续

                hlfP = (uint32_t *)USB_RX_Buffer;

                COMMON_FLASH_WRITE(writeAddr, hlfP, READ_FILE_PAGE_SIZE / 2);

                writeAddr += 0x400;

                bootSendReport(CMD_DATA_RECEIVED, 8);   // 应答
            }
        }
    }

}

/* Debug UART HandleIRQ */
void DEBUG_UART_IRQHANDLER(void) {

    volatile uint16_t data;

    if(hal_get_uart_rx_flag() == SET) {
        data = BspUartReadData();
        searchCMD(data);
        bootRX.hid_rx_buff[bootRX.hid_rx_len] = data;
        bootRX.hid_rx_len++;
        if(bootRX.hid_rx_len == HID_RX_SIZE) {
            new_data_is_received = 1;
        }
    }

    HAL_UART_IRQHandler(&debug_uart);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {

}

    // if (memcmp(bootRX.hid_rx_buff, CMD_RESET_PAGES, sizeof (CMD_RESET_PAGES)) == 0) {
    // if((strstr((char *)bootRX.hid_rx_buff, CMD_RESET_PAGES_BUFF) != NULL) || (memcmp(bootRX.hid_rx_buff, CMD_RESET_PAGES, sizeof (CMD_RESET_PAGES)) == 0) ) {
    

uint8_t compareCMD(void) {

    // if((strstr((char *)bootRX.hid_rx_buff, (char *)CMD_RESET_PAGES_BUFF) != NULL)) {
    if(getCmdFlag) {
        bootSendReport(CMD_OK_ACK, 2);
        COMMON_FLASH_ERASE();
        return 1;
    }else{
        return 0;
    }
}

void searchCMD(uint8_t data) {
    static uint32_t on = 0;
    switch(on) {
        case 0: if(data == 'B') on++; break;
        
        case 1: 
            if(data == 'L') on++;
            else on = 0;
        break;

        case 2:
            if(data == 'T') on++;
            else on = 0;
        break;

        case 3:
            if(data == 'T') on++;
            else on = 0;
        break;

        case 4:
            if(data == 'T') on++;
            else on = 0;
        break;

        case 5:
            if(data == 'T') on++;
            else on = 0;
        break;

        case 6:
            if(data == 'T') on++;
            else on = 0;
        break;

        case 7:
            if(data == 'T') {
                on++; 
                getCmdFlag = 1;
            } 
            else on = 0;
        break;
    }
}