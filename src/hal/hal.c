#include "hal.h"

hal_info_t hal_info;
hal_flag_t hal_flag;

/*********************************************************
 *  Init motherboard info and get size
 * ******************************************************/

void printf_info_init(void) {
    hal_sd.is_has_sd = 0;
    hal_info.is_has_u_disk = false;
    hal_info.mcu_freq = HAL_RCC_GetHCLKFreq() / 1000000;
    hal_info.mcu_size = (MCU_FLASH / 1024);
    hal_info.app_size = hal_info.mcu_size - hal_info.mcu_size;
}


/*********************************************************
 *  For print motherboard Info, info about
 * - Board name.
 * - Board Version , Build date.
 * - If use u disk or SD.
 * - MCU info, include Flash size and Freq.
 * ******************************************************/ 
void printf_info(void) {
    DEBUG_PRINTF("MKS Boot Info\n");
    DEBUG_PRINTF("-Board:%s\n", BOARD_NAME);
    DEBUG_PRINTF("-Version:%s, %s\n",BOOTLOAD_VERSION, BOOTLOAD_DATE);
    DEBUG_PRINTF("-U:%d|SD:%d\n", hal_info.is_has_u_disk, hal_sd.is_has_sd);
    DEBUG_PRINTF("-MCU info:%dK,%dMHz\n", hal_info.mcu_size, hal_info.mcu_freq);
}


/*********************************************************
 *  For bootloader result
 * - When the mother have problem if update the firware,
 *   you have to read the result and check num.
 *   every bit will meant different problem 
 * ******************************************************/
void printf_result_info(void) {
    hal_flag.bit_flag = 0;
    if(hal_flag.bit_erase) hal_flag.bit_flag        |= 1 << 4;
    if(hal_flag.bit_wait_finsh) hal_flag.bit_flag   |= 1 << 3;
    if(hal_flag.bit_open_file) hal_flag.bit_flag    |= 1 << 2;
    if(hal_flag.bit_uploading) hal_flag.bit_flag    |= 1 << 1;
    if(hal_flag.bit_read_finish) hal_flag.bit_flag  |= 1 << 0;
    DEBUG_PRINT("Result:0x%x", hal_flag.bit_flag);
}
