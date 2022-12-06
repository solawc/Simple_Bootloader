#ifndef __tft_lcd_h
#define __tft_lcd_h

#include "../../main.h"


typedef struct {
/* spi driver */
    void (*tft_spi_init)(void);
    void (*tft_spi_trans_enable)(void);
    void (*tft_spi_trans_disable)(void);
    void (*tft_delay_ms)(uint32_t);
    uint8_t (*tft_spi_read_write_byte)(uint8_t);
    uint8_t (*tft_spi_read_write_buff)(uint8_t *);
    
/* spi dma driver. */
    uint8_t (*tft_spi_trans_dma)(uint8_t *, uint32_t);
}tft_lcd_t;


#endif
