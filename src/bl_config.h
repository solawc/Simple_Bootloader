#ifndef __bl_config_h
#define __bl_config_h

#define BL_DEBUG_MODE

#define BL_STAR_ADDR           0X00                 // Bootload star address
#define BL_END_ADDR            0X8000               // Bootload end address
#define BL_SIZE                BL_END_ADDR          // Bootload size

#define HAS_W25QXX_ON_BOARD


#define HAS_SD_ON_BOARD
#ifdef HAS_SD_ON_BOARD

    #define SD_USE_SPI
    // #define SD_USE_SDIO

    #ifdef SD_USE_SPI
        #ifdef SD_USE_SDIO
            #error:"Please undefine SD_USE_SPI! or SD_USE_SDIO!";    
        #endif
    #endif
#endif


#endif
