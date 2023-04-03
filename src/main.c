/*
 main.c

 Copyright (c) 2021-2023 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#include "main.h"

int main(void) {
    
    /* if use Keil/IAR toolchain, you need set VectorTable offset at 0x0000 */
    NvicSetVectorTable(NVIC_VectTab_FLASH, 0x0000);     /* Set IRQn Offset 0x0000 */

    HAL_Init();                     /* Init STM32 HAL Lib and systick       */  
    SYSTEM_INIT();                  /* Config MCU Freq                      */     
    PrintInfoInit();                /* Get bootloader info                  */
    hal_uart_init();                /* Init UART                            */

#ifdef BOOT_LED_PORT
    bsp_led_init();                 /* If you need LED to show program Flash */
#endif

#ifdef LCD_DGUS_DWIN
    lcd_dgus_begin();               /* If your lcd use Dwin dgus(5A A5)     */
#endif

#ifndef USE_HID_BOOT
    SdcardApiReg();                 /* Regiest SDCard Driver for SPI or SDIO(TODO..) */

    mCardMount();                   /* Mount SDCard. */

    printInfo(); 
#endif

     
    /**************************************************************
     *             * Why is there a delay here? *
     * Because after the MCU is initialized and started, 
     * maybe due to hardware reasons, 
     * it needs to wait for the clock to stabilize. 
     * The initialization is actually very fast, 
     * but the stabilization process is relatively long. 
     * You have no way of knowing if the SD card is already 
     * clock stabilized, even if it initializes normally 
     * and hangs normally on FATFS.
     * So I put a 500ms delay in this place, maybe it's too long, 
     * but it's enough to make sure it's stable
    **************************************************************/
    HAL_Delay(500);

#ifndef USE_HID_BOOT
    UpdateCheck();
#else 
    HID_Bootloader_Task();
#endif

    /* Never into here */ 
    while(1) {};
}

void HardFault_Handler(void) {

    /* Never into here */
    while(1) {}
}
