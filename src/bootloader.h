#ifndef __bootloader_h
#define __bootloader_h

#include "main.h"


/* Get from stm32f4 ST lib */
#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
#define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == NVIC_VectTab_RAM) || \
                                  ((VECTTAB) == NVIC_VectTab_FLASH))

#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)




void bl_jump_to_app(uint32_t sect,uint32_t Msp,uint32_t reset);
void nvic_set_vector_table(uint32_t NVIC_VectTab, uint32_t Offset);
void update_check(void);

#endif /* __bootload_h */ 
