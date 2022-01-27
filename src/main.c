#include "main.h"

/* From FATFS demo */
FATFS fs;
FIL fil;
FRESULT fr;

FRESULT open_append (
    FIL* fp,            /* [OUT] File object to create */
    const char* path    /* [IN]  File name to be opened */
)
{
    FRESULT fr;

    /* Opens an existing file. If not exist, creates a new file. */
    fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
    if (fr == FR_OK) {
        /* Seek to end of the file to append data */
        fr = f_lseek(fp, f_size(fp));
        if (fr != FR_OK)
            f_close(fp);
    }
    return fr;
}

int main() {

    FRESULT fs_res;

    nvic_set_vector_table(NVIC_VectTab_FLASH, 0x0000);

    HAL_Init();        

    SYSTEM_INIT();          // set system clock

    hal_uart_init();        // init uart 

    hal_sd_register();      // register sd

    printf_info();          // print debug info

    if(!hal_sd.sd_get_status()) {
        fs_res = f_mount(&fs,"1:",1);
        if(fs_res == 0) DEBUG_PRINT("SD mount succeed");  
        hal_sd.is_has_sd = 1; 
    }else{
        hal_sd.is_has_sd = 0; 
        DEBUG_PRINT("No SD Inser");
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
