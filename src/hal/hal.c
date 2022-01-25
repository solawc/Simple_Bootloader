#include "hal.h"

hal_info_t hal_info;

void printf_info(void) {

    hal_info.mcu_freq = HAL_RCC_GetHCLKFreq() / 1000000;

    hal_info.is_has_sd_disk = false;
    hal_info.is_has_u_disk = false;
    hal_info.mcu_size = 256;

    DEBUG_PRINTF("/*************************************************/\n");
    DEBUG_PRINTF("                  MKS Boot Info\n");
    DEBUG_PRINTF(" -Board:%s\r\n", BOARD_NAME);
    DEBUG_PRINTF(" -Version:%s\r\n",BOOTLOAD_VERSION);
    DEBUG_PRINTF(" -Update Time:%s\r\n",BOOTLOAD_DATE);
    DEBUG_PRINTF(" -U disk:%d\r\n", hal_info.is_has_u_disk);
    DEBUG_PRINTF(" -SD disk:%d\r\n", hal_info.is_has_sd_disk);
    DEBUG_PRINTF(" -MCU size:%dK\r\n", hal_info.mcu_size);
    DEBUG_PRINTF(" -MCU clk:%dMHz\r\n", hal_info.mcu_freq);
    DEBUG_PRINTF("/*************************************************/\n");

}

