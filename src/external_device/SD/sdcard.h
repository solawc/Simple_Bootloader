#ifndef __sdcard_h
#define __sdcard_h

#include "../../main.h"

#define SD_SPI_SPEED        SPI_BAUDRATEPRESCALER_4

#define SD_SPI_LOW_SPEED    SPI_BAUDRATEPRESCALER_128

#define SD_DUMMY_BYTE       0xFF

/* SD卡类型定义 */
#define SD_TYPE_MMC     0
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    4

/* SD卡指令表 */
#define CMD0    0       //卡复位
#define CMD9    9       //命令9 ，读CSD数据
#define CMD10   10      //命令10，读CID数据
#define CMD12   12      //命令12，停止数据传输
#define CMD16   16      //命令16，设置SectorSize 应返回0x00
#define CMD17   17      //命令17，读sector
#define CMD18   18      //命令18，读Multi sector
#define ACMD23  23      //命令23，设置多sector写入前预先擦除N个block
#define CMD24   24      //命令24，写sector
#define CMD25   25      //命令25，写Multi sector
#define ACMD41  41      //命令41，应返回0x00
#define CMD55   55      //命令55，应返回0x01
#define CMD58   58      //命令58，读OCR信息
#define CMD59   59      //命令59，使能/禁止CRC，应返回0x00



typedef struct {

    uint8_t SD_type;                     /* 描述SD卡类型 */

    void (*sdcard_init)(void);

    uint8_t (*get_sd_status)(void);

}hal_sd_t;


#endif
