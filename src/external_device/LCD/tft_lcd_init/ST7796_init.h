
{
    tft_lcd.tft_delay_ms(20);
    tft_write_cmd(0x11);
    tft_lcd.tft_delay_ms(20);

	tft_write_cmd(0x36);

    tft_write_cmd(0xF0);
    tft_write_8_data(0xC3);
    tft_write_cmd(0xF0);
    tft_write_8_data(0x96);

    tft_write_cmd(0x36);
    // tft_write_8_data(0xE8);
    tft_write_8_data(0x28);
    tft_write_8_data(0x28);

    tft_write_cmd(0x3A);

    tft_write_8_data(0x55);
    tft_write_cmd(0xB4);
    tft_write_8_data(0x01);
    tft_write_cmd(0xB7);
    tft_write_8_data(0xC6);
    tft_write_cmd(0xE8);
    tft_write_8_data(0x40);
    tft_write_8_data(0x8A);
    tft_write_8_data(0x00);
    tft_write_8_data(0x00);
    tft_write_8_data(0x29);
    tft_write_8_data(0x19);
    tft_write_8_data(0xA5);
    tft_write_8_data(0x33);
    tft_write_cmd(0xC1);
    tft_write_8_data(0x06);
    tft_write_cmd(0xC2);
    tft_write_8_data(0xA7);
    tft_write_cmd(0xC5);
    tft_write_8_data(0x18);
    tft_write_cmd(0xE0);         // Positive Voltage Gamma Control
    tft_write_8_data(0xF0);
    tft_write_8_data(0x09);
    tft_write_8_data(0x0B);
    tft_write_8_data(0x06);
    tft_write_8_data(0x04);
    tft_write_8_data(0x15);
    tft_write_8_data(0x2F);
    tft_write_8_data(0x54);
    tft_write_8_data(0x42);
    tft_write_8_data(0x3C);
    tft_write_8_data(0x17);
    tft_write_8_data(0x14);
    tft_write_8_data(0x18);
    tft_write_8_data(0x1B);
    tft_write_cmd(0xE1);         // Negative Voltage Gamma Control
    tft_write_8_data(0xF0);
    tft_write_8_data(0x09);
    tft_write_8_data(0x0B);
    tft_write_8_data(0x06);
    tft_write_8_data(0x04);
    tft_write_8_data(0x03);
    tft_write_8_data(0x2D);
    tft_write_8_data(0x43);
    tft_write_8_data(0x42);
    tft_write_8_data(0x3B);
    tft_write_8_data(0x16);
    tft_write_8_data(0x14);
    tft_write_8_data(0x17);
    tft_write_8_data(0x1B);
    tft_write_cmd(0xF0);
    tft_write_8_data(0x3C);
    tft_write_cmd(0xF0);
    tft_write_8_data(0x69);
    tft_lcd.tft_delay_ms(120);                 // tft_lcd.tft_delay_ms 120ms
    tft_write_cmd(0x29);         // Display ON
}