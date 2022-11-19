#ifndef _hal_h
#define _hal_h

#include "../main.h"
#include "stdbool.h"

/************************************************************************************************************
 *                                                  bit_flag                                                *
 *--------------------------------------------------------------------------------------------------------- *
 * 0 | 0 |    0         |      0    |       0        |       0       |       0       |        0        |    *
 *   |   | bit_size_err | bit_erase | bit_wait_finsh | bit_open_file | bit_uploading | bit_read_finish |    *
 *   |   |              |           |                |               |               |                 |    *
 *--------------------------------------------------------------------------------------------------------- *
************************************************************************************************************/

typedef struct {
    uint8_t bit_erase:1;
    uint8_t bit_wait_finsh:1;
    uint8_t bit_open_file:1;
    uint8_t bit_uploading:1;
    uint8_t bit_read_finish:1;
    uint8_t bit_size_err:1;
    uint8_t bit_flag;
}hal_flag_t;
extern hal_flag_t hal_flag;

typedef struct {
    uint16_t mcu_freq;
    uint16_t mcu_size;
    uint16_t bl_size;
    uint16_t app_size;
    bool is_has_u_disk;
}hal_info_t;
extern hal_info_t hal_info;


void printInfo(void);
void PrintInfoInit(void);
void printf_result_info(void);
#endif
