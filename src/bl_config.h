#ifndef __bl_config_h
#define __bl_config_h

// set bootload version num
#define BOOTLOAD_VERSION        "V0.1"
#define BOOTLOAD_DATE           "2022-02-28"
#define BOARD_NAME              "ZNP Robin Nano_DW V2.0"

#ifndef MCU_FREQ
#define MCU_FREQ        F_CPU
#endif

#ifndef MCU_RAM
#define MCU_RAM         64*1024     // default for STM32F401RC, is 64k RAM 
#endif

#ifndef MCU_FLASH
#define MCU_FLASH       256*1024    // default for STM32F401RC is 256k Flash
#endif

/* Enabled bootload if you want know debug info. */
#define BL_DEBUG_MODE
#ifdef BL_DEBUG_MODE
#define DEBUG_SWITCH        1
#endif

// set bootload address   
#define BL_END_ADDR             ((uint32_t)0x8007fff)       // Bootload end address
#define APP_STAR_ADDR           ((uint32_t)0x8008000)       // Jump to this addr to star app
#define BL_OFFSET               0X8000                      // Set bootloader offset       

/* Enabled W25qxx if need to write pic and font. */
//#define HAS_W25QXX_ON_BOARD

/* Enabled SD Card, SD_USE_SPI use SPI mode, SD_USE_SDIO use SDIO mode. */
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
