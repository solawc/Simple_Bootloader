#include "bootloader.h"

hal_bootloader_t hal_bl;

#ifdef STM32G0xx
typedef uint64_t _FLASH_SIZE_TYPE;
#define SIZE_DIV    4
#else 
typedef uint32_t _FLASH_SIZE_TYPE;
#define SIZE_DIV    2
#endif

typedef uint32_t MSP_TYPE;
typedef uint32_t RST_TYPE;

#ifndef BL_NAME
const char *FW_FILE_SD        = "1:/ROBIN_E3D_V2.bin";
#else 
const char *FW_FILE_SD        = BL_NAME;
#endif

#ifndef BL_OLD_NAME
const char *FW_OLD_FILE_SD    = "1:/ROBIN_E3D_V2.CUR";
#else
const char *FW_OLD_FILE_SD    = BL_OLD_NAME;
#endif

char firmware_name_buff[FW_NAME_SIZE];
char old_name_buff[FW_NAME_SIZE];

MSP_TYPE msp = 0;               /* Point to Msp         */
RST_TYPE reset = 0;             /* Point to void*       */
uint32_t Address = 0x00;        /* 擦除计数，擦除地址   */

_FLASH_SIZE_TYPE    *hlfP; //= (_FLASH_SIZE_TYPE *)file_read_buff;

/* only support cortex-M */
void NvicSetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset) {

    /* Check the parameters */
    assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
    assert_param(IS_NVIC_OFFSET(Offset)); 
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/* only support cortex-M */
void bl_reset_systick(void) {
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;     /* Disable systick */
}

void bl_erase_flash(void) {
    COMMON_FLASH_ERASE();                           /* A define at pins_xxx.h */
}

/****************************************************************************
 * Why not use memset() ?
 * After a certain period of testing, memset can achieve the same effect, 
 * but when memset is executed, the array is not completely written to 0xff, 
 * which may cause the data to be wrong. The effect is that the motherboard 
 * cannot be powered on, and the running firmware is not completely correct.
 * 
 * Therefore, it is relatively stable to use the for loop to realize this 
 * emptying function. Maybe different microcontrollers will have different 
 * differences.
 * *************************************************************************/
void bufferSet(uint8_t* pBuffer, uint8_t data, uint16_t BufferLength)
{
  uint16_t i;
  for(i = 0; i<BufferLength; i++)
  {
    pBuffer[i] = data;
  }
}

uint32_t fw_size_count = 0;

void bl_write_flash(void) {

    UINT br;

    Address = APP_STAR_ADDR;

    INFO_PRINT("[DEBUG]Firmware Size=%ldK\n", hal_sd.fw_file_size/1024);

    uint8_t *file_read_buff;

    while(1) {

#ifdef BOOT_LED_PORT
        bsp_led_toggle();
#endif
        file_read_buff = (uint8_t *)malloc(READ_FILE_PAGE_SIZE);

        bufferSet(file_read_buff, 0xff, READ_FILE_PAGE_SIZE);

        f_read(&fil, file_read_buff, READ_FILE_PAGE_SIZE, &br);

        fw_size_count++;

        if(msp == 0 && reset == 0)
        {
            msp = *((uint32_t *)(file_read_buff));

            reset = *((uint32_t *)(file_read_buff + 4));
        }

        hlfP = (_FLASH_SIZE_TYPE *)file_read_buff;
        
        COMMON_FLASH_WRITE(Address, hlfP, READ_FILE_PAGE_SIZE / SIZE_DIV);

        free(file_read_buff);

		Address += READ_FILE_PAGE_SIZE;

        if(br < READ_FILE_PAGE_SIZE) {

            hal_flag.bit_read_finish = 1;

            break;
        };
        INFO_PRINT("Update...[%d%%]", (int)(((fw_size_count) * 100) / (hal_sd.fw_file_size / 1024))); 
    }
}

uint8_t bl_open_update_file(void) {

    FRESULT fr;
    uint32_t file_size = 0;

    memset(hal_bl.fw_name_buf, 0, sizeof(hal_bl.fw_name_buf));
    memset(old_name_buff, 0, sizeof(hal_bl.fw_old_name_buf));

    strcpy(hal_bl.fw_name_buf, FW_FILE_SD);
    strcpy(hal_bl.fw_old_name_buf, FW_OLD_FILE_SD);    

    fr = f_open(&fil, hal_bl.fw_name_buf,  FA_READ|FA_WRITE);

    file_size = fil.obj.objsize;

    if(file_size > (MCU_FLASH - BL_SIZE)) { return 1; }

    if(fr == FR_OK) {
        hal_sd.fw_file_size = fil.obj.objsize;
        bl_erase_flash();
        hal_flag.bit_open_file = 1;
        return 0;
    }else {
        hal_flag.bit_open_file = 0;
        return 1;
    }
}

void bl_rename_file(void) {
    f_close(&fil);
    f_unlink(hal_bl.fw_old_name_buf);
    f_rename(hal_bl.fw_name_buf, hal_bl.fw_old_name_buf);
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

    __IO uint32_t base;
    __IO uint32_t offset;

#ifdef LCD_DGUS_DWIN
    jump_to_star();
#endif

    SdSpiDrvDeinit();

    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;

    base = (sect > NVIC_VectTab_FLASH)? NVIC_VectTab_FLASH:NVIC_VectTab_RAM; //中断向量表基地址

    offset = sect-base;	

    NvicSetVectorTable(base, offset);

    __set_MSP(Msp);

    ((void(*)()) (reset_msp))();
}


void jump_without_update(void) {

    printf_result_info();

    msp = *((uint32_t *)(APP_STAR_ADDR));

	reset = *((uint32_t *)(APP_STAR_ADDR + 4));

    bl_jump_to_app(APP_STAR_ADDR, msp, reset);
}

void jump_with_update() {

#ifdef LCD_DGUS_DWIN
    jump_into_boot_screen();
#endif

    bl_write_flash();
    bl_rename_file();
    printf_result_info();
    bl_jump_to_app(APP_STAR_ADDR, msp, reset);
}

void update_check(void) {

    uint8_t is_need_update;

    is_need_update = bl_open_update_file();

    if(is_need_update == 0) {
        hal_flag.bit_uploading = 1;
        jump_with_update();
    }
    else   {        
        hal_flag.bit_uploading = 0;     // open file fail or no fw file
        jump_without_update();
    }
}

#ifdef BOOT_LED_PORT
void bsp_led_init(void) {

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_Init;
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pin = BOOT_LED_PIN;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BOOT_LED_PORT, &GPIO_Init);
}

void bsp_led_on(void) {
    HAL_GPIO_WritePin(BOOT_LED_PORT, BOOT_LED_PIN, GPIO_PIN_SET);
}

void bsp_led_off(void) {
    HAL_GPIO_WritePin(BOOT_LED_PORT, BOOT_LED_PIN, GPIO_PIN_RESET);
}

void bsp_led_toggle(void) {

    static uint8_t count = 0;
    
    if(count < 5) {
        count++;
    }else {
        HAL_GPIO_TogglePin(BOOT_LED_PORT, BOOT_LED_PIN);
        count = 0;
    }
}

#endif
