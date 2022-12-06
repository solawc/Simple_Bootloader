#include "mid_fs.h"

FIL bootFile;
FATFS bootFs;

/* Check SDCard state. */
uint8_t mCardCheck(void) {
    return hal_sd.sd_get_status();
}

/* Mount SDCard */
uint8_t mCardMount(void) {

    FRESULT fs_res;

    if(!mCardCheck()) {
        fs_res = f_mount(&bootFs, SD_PATH, 1);
        if(fs_res == FR_OK){ 
            hal_sd.is_has_sd = 1; 
            return 1;
        }
        else { 
            hal_sd.is_has_sd = 0; 
            return 0;
        }
    }else{ 
        hal_sd.is_has_sd = 0; 
        return 0;
    }
}






