#ifndef __bl_config_h
#define __bl_config_h

// set bootload version num


//#define CUSTOM_BOARD_NAME       

#define BOOTLOAD_VERSION        "V0.1"
#define BOOTLOAD_DATE           "2022-07-06"

#ifndef CUSTOM_BOARD_NAME

#ifdef MKS_BOARD_NAME
    #define BOARD_NAME              MKS_BOARD_NAME
#else
    #define BOARD_NAME              "MKS MotherBoard"
#endif

#else 
#define BOARD_NAME              "ZNP Robin Nano_DW V2.0"
#endif

#ifndef MCU_FREQ
#define MCU_FREQ                F_CPU
#endif

#ifndef MCU_RAM
#define MCU_RAM         256*1024     // default for STM32F401RC, is 256k RAM 
#endif

#ifndef MCU_FLASH
#define MCU_FLASH       1024*1024    // default for STM32F401RC is 1024k Flash

#endif

#ifndef BL_SIZE
#define BL_SIZE                 32*1024
#endif

/* Enabled bootload if you want know debug info. */
#define BL_DEBUG_MODE
#ifdef BL_DEBUG_MODE
#define DEBUG_SWITCH        1
#endif

// set bootload address   
#ifndef BL_END_ADDR
#define BL_END_ADDR             ((uint32_t)0x8007fff)       // Bootload end address
#endif

#ifndef APP_STAR_ADDR
#define APP_STAR_ADDR           ((uint32_t)0x8008000)       // Jump to this addr to star app
#endif

#ifndef BL_OFFSET
#define BL_OFFSET               ((uint32_t)0X8000)          // Set bootloader offset      
#endif 

/* Enabled W25qxx if need to write pic and font. */
//#define HAS_W25QXX_ON_BOARD

/* Enabled mother board test mode */
#define USE_TEST_MODE

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

/* Enabled and settings LCD type */
// #define LCD_DGUS_DWIN           // use 5A A5 type 
// #define LCD_FSMA_TFT            // use FSMC to driver LCD
// #define LCD_SPI_TS              // use SPI to driver LCD
#endif
