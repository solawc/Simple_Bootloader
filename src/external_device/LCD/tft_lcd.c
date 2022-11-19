#include "tft_lcd.h"

tft_lcd_t tft_lcd;


void tftLcdApiReg(void) {

}


void tft_write_cmd(uint8_t cmd) {

} 

void tft_write_8_data(uint8_t data) {

}

void tft_write_16_date(uint16_t data) {


}

void tft_lcd_init() {

    tft_lcd.tft_spi_init();
    tft_lcd.tft_delay_ms(100);

#ifdef LCD_SPI_TS35
    #include "tft_lcd_init/ST7796_init.h"
#elif defined LCD_SPI_TS24

#else 
    #error:"Please select LCD type at bl_config.h, LCD_SPI_TS35 or LCD_SPI_TS24."
#endif 

    tft_lcd.tft_delay_ms(100);
}

void tft_lcd_bk_on();

