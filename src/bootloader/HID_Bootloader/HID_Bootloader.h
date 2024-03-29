/*
 HID_Bootloader.h

 Copyright (c) 2021-2023 sola

 SimpleBootloader is an open source bootloader. It follows the open 
 source protocol of GPL 3.0, and users can republish it based on the 
 GPL 3.0 protocol.
*/

#ifndef __HID_BOOTLOADER_H
#define __HID_BOOTLOADER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "HID_boot_port.h"

#define HID_RX_SIZE         1024
#define USER_CODE_OFFSET    0x8000
#define SECTOR_SIZE         1024
#define TIME_OUT            4000        /* 4s的超时时间，2s内没有满足一帧数据，重启 */

/* 用于管理HID BOOT接收buff */
typedef struct {

    uint8_t hid_rx_buff[HID_RX_SIZE];        /* 用于存储数据                 */
    uint32_t hid_rx_len;                    /* 用于对数据进行计数           */

}HID_RX_t;



void HID_Bootloader_Task(void);


#ifdef __cplusplus
}
#endif

#endif /* __HID_BOOTLOADER_H */
