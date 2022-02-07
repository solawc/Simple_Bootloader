#include "bootloader.h"
#include "core_cm4.h"

hal_bootloader_t hal_bl;

const char *FW_FILE_SD        = "1:/ZNP_ROBIN_DW.bin";
const char *FW_OLD_FILE_SD    = "1:/ZNP_ROBIN_DW.CUR";

char firmware_name_buff[FW_NAME_SIZE];
char old_name_buff[FW_NAME_SIZE];

uint32_t msp = 0;
uint32_t reset = 0;
UINT br;

uint32_t EraseCounter = 0x00, Address = 0x00;//擦除计数，擦除地址

uint8_t file_read_buff[1024];  // 用于装载读取回来的固件
uint16_t *hlfP = (uint16_t *)file_read_buff;

/* only support cortex-M */
void nvic_set_vector_table(uint32_t NVIC_VectTab, uint32_t Offset) {

    /* Check the parameters */
    assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
    assert_param(IS_NVIC_OFFSET(Offset)); 
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/* only support cortex-M */
void bl_reset_systick(void) {

    /* Disable systick */
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

void bl_erase_flash(void) {

    hal_flash_erase();
}


void bufferSet(uint8_t* pBuffer, uint8_t data, uint16_t BufferLength)
{
  uint16_t i;
  for(i = 0; i<BufferLength; i++)
  {
    pBuffer[i] = data;
  }
}

void bl_write_flash(void) {

    // FRESULT fr;
    FIL fil;

    Address = APP_STAR_ADDR;
    
    while(1) {

        bufferSet(file_read_buff, 0xff, READ_FILE_PAGE_SIZE);

        f_read(&fil, file_read_buff, READ_FILE_PAGE_SIZE, &br);

        if(msp == 0 && reset == 0)
        {
            msp = *((uint32_t *)(file_read_buff));

            reset = *((uint32_t *)(file_read_buff+4));
        }

        hlfP = (uint16_t *)file_read_buff;

        hal_flash_write(Address, hlfP, READ_FILE_PAGE_SIZE/2 );

		Address += READ_FILE_PAGE_SIZE;

        if(br < READ_FILE_PAGE_SIZE) {

            DEBUG_PRINT("File had read finish");

            break;
        }; 
    }
}

uint8_t bl_open_update_file(void) {

    FRESULT fr;
    FIL fil;

    memset(hal_bl.fw_name_buf, 0, sizeof(hal_bl.fw_name_buf));
    memset(old_name_buff, 0, sizeof(hal_bl.fw_old_name_buf));

    strcpy(hal_bl.fw_name_buf, FW_FILE_SD);
    strcpy(hal_bl.fw_old_name_buf, FW_OLD_FILE_SD);    

    fr = f_open(&fil, hal_bl.fw_name_buf,  FA_READ|FA_WRITE);

    if(fr == FR_OK) {

        bl_erase_flash();

        DEBUG_PRINT("open FW succeed");
        
        return 0;
    }else {

        DEBUG_PRINT("open FW fail");

        return 1;
    }
}


/*
 * Author:sola
 * Fix time:2022-01-22
 * Describe:
 * 1. update flash 
 * 2. set beep
 * 3. DeInit SPI, Systick
 * 4. Reset Systick 
 * 5. set MSP
 * 6. jump and reset mcu
*/
void bl_jump_to_app(uint32_t sect, uint32_t Msp, uint32_t reset_msp) {

    uint32_t base;
    uint32_t offset;

    /* Step 1. Update flash */
    // mks_update_flash();
    /* Step 2. set beep */

    /* Step 3. DeInit SPI, Systick */
    hal_sd_deinit();

    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;

    base = (sect > NVIC_VectTab_FLASH)? NVIC_VectTab_FLASH:NVIC_VectTab_RAM; //中断向量表基地址

    offset = sect-base;	

    nvic_set_vector_table(base, offset);

    __set_MSP(Msp);

    ((void(*)()) (reset_msp))();
}


void jump_without_update(void) {

    msp = *((uint32_t *)(APP_STAR_ADDR));

	reset = *((uint32_t *)(APP_STAR_ADDR + 4));

    bl_jump_to_app(APP_STAR_ADDR, msp, reset);

}

void jump_with_update() {

    bl_write_flash();
}

void update_check(void) {

    uint8_t is_need_update;

    is_need_update = bl_open_update_file();

    if(is_need_update == 0) 
    {   
        DEBUG_PRINT("Updating file");

        jump_with_update();
    }
    else  // open file fail or no fw file
    {
        jump_without_update();
    }

    DEBUG_PRINT("bootload jump to app");
}


