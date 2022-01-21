#ifndef __bl_config_h
#define __bl_config_h

// set bootload version num
#define BOOTLOAD_VERSION        "V0.0.1"
#define BOOTLOAD_DATE           "2022-01-21"

// Enabled bootload if you want know debug info.
#define BL_DEBUG_MODE

// set bootload address 
#define BL_STAR_ADDR           0X00                 // Bootload star address
#define BL_END_ADDR            0X8000               // Bootload end address
#define BL_SIZE                BL_END_ADDR          // Bootload size

// Enabled W25qxx if need to write pic and font.
#define HAS_W25QXX_ON_BOARD

// Enabled SD Card, SD_USE_SPI use SPI mode, SD_USE_SDIO use SDIO mode.
#define HAS_SD_ON_BOARD
#ifdef HAS_SD_ON_BOARD

    #define SD_USE_SPI
    // #define SD_USE_SDIO

    #ifdef SD_USE_SPI
        #ifdef SD_USE_SDIO
            #error:"Please undefine SD_USE_SPI! or SD_USE_SDIO!";    
        #endif // SD_USE_SDIO
    #endif // SD_USE_SPI
#endif // HAS_SD_ON_BOARD


#endif
