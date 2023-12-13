#ifndef __hal_spi_h
#define __hal_spi_h

#include "../main.h"

struct spi_info {
    SPI_TypeDef *spi;
    uint8_t miso_pin, mosi_pin, sck_pin, function;
};





#endif
