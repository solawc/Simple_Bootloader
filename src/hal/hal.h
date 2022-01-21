#ifndef _hal_h
#define _hal_h

#include "../main.h"
#include "stdbool.h"

typedef struct {
    uint16_t mcu_size;
    bool is_has_u_disk;
    bool is_has_sd_disk;
}hal_info_t;



void printf_info(void);

#endif
