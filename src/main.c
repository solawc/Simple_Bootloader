/*
 main.c

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#include "main.h"

FIL bootFile;
FATFS bootFs;

int main(void) {

    FRESULT fs_res;

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

    SdcardApiReg();                 /* Regiest SDCard Driver for SPI or SDIO(TODO..) */

    if(!hal_sd.sd_get_status()) {
        fs_res = f_mount(&bootFs, SD_PATH, 1);
        if(fs_res == FR_OK){ hal_sd.is_has_sd = 1; }
        else { hal_sd.is_has_sd = 0; }
    }else{ hal_sd.is_has_sd = 0; }
    
    printf_info(); 
     
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

    UpdateCheck();

    /* Never into here */ 
    while(1) {};
}


/**************************************************************
 * Author:sola
 * Fix time:2022-01-20
 * Describe:
 * This is for the tick of the HAL library, 
 * using Systick's interrupt to perform the count
**************************************************************/
void SysTick_Handler(void)
{
    HAL_IncTick();
}

void HardFault_Handler(void) {

    while(1) {


    }
}
