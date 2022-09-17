#include "hal_flash.h"


void mcu_flash_erase() {

    COMMON_FLASH_ERASE();
}


void mcu_flash_write(uint32_t addr ,uint16_t *buff, uint32_t num) {

    COMMON_FLASH_WRITE(addr, buff, num);
}



