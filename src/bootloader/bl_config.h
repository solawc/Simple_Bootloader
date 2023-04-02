/*
 bl_config.h

 Copyright (c) 2021-2022 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef __bl_config_h
#define __bl_config_h

/* Bootloader version and date. */
#define BOOTLOAD_VERSION                "V0.8"
#define BOOTLOAD_DATE                   "2023-03-01"

/* Board info. */
#ifdef CUSTOM_BOARD_NAME
    #define BOARD_NAME                  CUSTOM_BOARD_NAME
#else
    #define BOARD_NAME                  "Custom"
#endif

/* You can define your CPU Freq. */
#ifndef MCU_FREQ
    #define MCU_FREQ                    F_CPU
#endif

/* Enabled bootload if you want know debug info. */
#define BL_DEBUG_MODE           /* Flash will use about 0.5Kb, so I suggest open it */
#ifdef BL_DEBUG_MODE
    #define DEBUG_SWITCH 
#endif

/* Enabled W25qxx if need to write pic and font. */
// #define HAS_W25QXX_ON_BOARD

/* Enabled mother board test mode */
// #define USE_TEST_MODE

/* Enabled SD Card, SD_USE_SPI use SPI mode, SD_USE_SDIO use SDIO mode. */
#define HAS_SD_ON_BOARD
#ifdef HAS_SD_ON_BOARD
#endif // HAS_SD_ON_BOARD

/* Enabled and settings LCD type */
// #define LCD_DGUS_DWIN            /* Use 5A A5 type           */ 
// #define LCD_FSMA_TFT             /* Use FSMC to driver LCD   */ 
// #define LCD_SPI_TS35             /* Use SPI to driver LCD    */ 
// #define LCD_SPI_TS24             /* Use SPI to driver LCD    */

/* Enabled USE_HID_BOOT */
// #define USE_HID_BOOT             /* Use HID bootloader       */


#endif
