#include "main.h"


FATFS fs;
FIL fil;
FRESULT fr;
int main() {

    FRESULT fs_res;

    nvic_set_vector_table(NVIC_VectTab_FLASH, 0x0000);

    HAL_Init();        

    SYSTEM_INIT();          // set system clock

    hal_uart_init();        // init uart 

    // hal_info.is_has_sd_disk = SD_Initialize();
    // if(hal_info.is_has_sd_disk != 0) {
    //     DEBUG_PRINT("SD Init Fail");
    //     DEBUG_PRINT("error code:%d",hal_info.is_has_sd_disk);
    // }

    printf_info();          // print debug info

    f_mount(&fs,"0:",1);
    DEBUG_PRINT("FS get:%d", fs_res);

    fr = f_open(&fil, "0:/123.txt", FA_READ | FA_WRITE);
    if (fr) {
        DEBUG_PRINT("open fail\n");
        DEBUG_PRINT("error code:%d", fr);
    }else{  
        DEBUG_PRINT("open succeed\n");
    }

    update_check();

    while(1) {};
}


/*
 * Author:sola
 * Fix time:2022-01-20
 * Describe:
 * This is for the tick of the HAL library, using Systick's interrupt 
 * to perform the count
*/
void SysTick_Handler(void)
{
    HAL_IncTick();
}
