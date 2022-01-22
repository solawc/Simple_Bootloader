#include "hal.h"

hal_info_t hal_info;

void printf_info(void) {

    hal_info.is_has_sd_disk = false;
    hal_info.is_has_u_disk = false;
    hal_info.mcu_size = 256;

    DEBUG_PRINTF("/*************************************************/\n");
    DEBUG_PRINTF("                    Boot Info\n");
    DEBUG_PRINTF(" -Board:ZNP Robin Nano_DW V2.0\n");
    DEBUG_PRINTF(" -Version:%s\n",BOOTLOAD_VERSION);
    DEBUG_PRINTF(" -Update Time:%s\n",BOOTLOAD_DATE);
    DEBUG_PRINTF(" -U disk:%d\n", hal_info.is_has_u_disk);
    DEBUG_PRINTF(" -SD disk:%d\n", hal_info.is_has_sd_disk);
    DEBUG_PRINTF(" -MCU SIZE:%d\n", hal_info.mcu_size);
    DEBUG_PRINTF("/*************************************************/\n");
}
