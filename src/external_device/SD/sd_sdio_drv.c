#include "sd_sdio_drv.h"

// SD_HandleTypeDef        SDCARD_Handler;              //SD卡句柄
// HAL_SD_CardInfoTypedef  SDCardInfo;                  //SD卡信息结构体
// DMA_HandleTypeDef SDTxDMAHandler,SDRxDMAHandler;     //SD卡DMA发送和接收句柄
// __align(4) u8 SDIO_DATA_BUFFER[512];


static void BspSdioGpioInit(void) {


}


void BspSdSdioInit(void) {

    BspSdioGpioInit();
}

uint8_t BspSdGetCardInfo(void) {

    return 0;
}

uint8_t BspSdioDetRead(void) {

    return 0;
}

uint8_t sdSdioReadBuff(uint8_t*buf,uint32_t sector,uint8_t cnt) {

    return 0;
}

uint8_t sdSdioWriteBuff(uint8_t*buf,uint32_t sector,uint8_t cnt) {

    return 0;
}






