#include "main.h"


FIL fil;

int main(void) {

    FATFS fs;
    
    FRESULT fs_res;

    nvic_set_vector_table(NVIC_VectTab_FLASH, 0x0000);

    HAL_Init();        

    SYSTEM_INIT();          // set system clock

    printf_info_init();

    hal_uart_init();        // init uart 

#ifdef LCD_DGUS_DWIN
    lcd_dgus_init();        // init dgus uart
    HAL_Delay(2000);        // wait for dwin display setup
    jump_to_rst();          // reset dwin dispaly
#endif

    hal_sd_register();      // register sd
#ifdef STM32F429xx

    fs_res = f_mount(&fs,"1:",1);
        if(fs_res == FR_OK){
            hal_sd.is_has_sd = 1;
        }else {
             hal_sd.is_has_sd = 0;
        }
#endif 

#ifdef STM32F401xC
    if(!hal_sd.sd_get_status()) {
        fs_res = f_mount(&fs,"1:",1);
        if(fs_res == FR_OK){
            hal_sd.is_has_sd = 1;
        }else {
             hal_sd.is_has_sd = 0;
        }
    }else{
       hal_sd.is_has_sd = 0; 
    }
#endif
    
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

    update_check();

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
    // USART2_IRQn
}

void HardFault_Handler(void) {

    while(1) {


    }
}
