#include "hal.h"

hal_info_t hal_info;

void printf_info(void) {

    hal_info.is_has_sd_disk = false;
    hal_info.is_has_u_disk = false;
    hal_info.mcu_size = 256;

    printf("/*************************************************/\n");
    printf("                    Boot Info\n");
    printf(" -Board:ZNP Robin Nano_DW V2.0\n");
    printf(" -U disk:%d\n", hal_info.is_has_u_disk);
    printf(" -SD disk:%d\n", hal_info.is_has_sd_disk);
    printf(" -MCU SIZE:%d\n", hal_info.mcu_size);
    printf("/*************************************************/\n");
}
