#include "sdcard.h"

#include "sd_spi_drv.h"
#include "sd_sdio_drv.h"

hal_sd_t hal_sd;

void SdcardApiReg(void) {
	hal_sd.sd_get_status = BspDetRead;
	hal_sd.sd_init = SdDrvInitAll;
	hal_sd.SdReadBuffer = SdSpiReadBuff;
	hal_sd.SdWriteBuffer = SdSpiWriteBuff;
	hal_sd.SdGetSector = SdGetSectorCount;
	
	hal_sd.sd_init();
}