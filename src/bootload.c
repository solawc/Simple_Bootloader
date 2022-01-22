#include "bootload.h"

void nvic_set_vector_table(uint32_t NVIC_VectTab, uint32_t Offset) {

    /* Check the parameters */
    assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
    assert_param(IS_NVIC_OFFSET(Offset)); 
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
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
void bl_jump_to_app(uint32_t sect,uint32_t Msp,uint32_t reset) {

    uint32_t base;
    uint32_t offset;

    /* Step 1. Update flash */
    // mks_update_flash();

    /* Step 2. set beep */

    /* Step 3. DeInit SPI, Systick */
    // hal_sd_deinit();

    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;

    base = (sect > NVIC_VectTab_FLASH)? NVIC_VectTab_FLASH:NVIC_VectTab_RAM; //中断向量表基地址

    offset = sect-base;	

    nvic_set_vector_table(base, offset);

    __set_MSP(Msp);

    ((void(*)()) (reset))();
}

uint32_t msp = 0;
uint32_t reset = 0;


void update_check(void) {

    printf("bootload jump to app\n");

    msp = *((uint32_t *)(APP_STAR_ADDR));
	reset = *((uint32_t *)(APP_STAR_ADDR + 4));

    bl_jump_to_app(BL_END_ADDR, msp, reset);
}


