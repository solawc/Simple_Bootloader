#include "main.h"


FFOBJID fs;

int main() {

    FRESULT fs_res;

    nvic_set_vector_table(NVIC_VectTab_FLASH, 0x0000);

    HAL_Init();        

    SYSTEM_INIT();          // set system clock

    hal_uart_init();        // init uart 

    hal_info.is_has_sd_disk = SD_Initialize();

    printf_info();          // print debug info

    fs_res = f_mount(fs.fs,"0:",1);

    DEBUG_PRINT("FS get:%d", fs_res);

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
