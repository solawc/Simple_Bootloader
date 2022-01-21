#ifndef __sdcard_h
#define __sdcard_h

#include "../../main.h"

#define SD_SPI_SPEED    SPI_BAUDRATEPRESCALER_4

#define SD_DUMMY_BYTE       0xFF

typedef struct {


    void (*sdcard_init)(void);

    bool (*get_sd_status)(void);

}hal_sd_t;


#endif
