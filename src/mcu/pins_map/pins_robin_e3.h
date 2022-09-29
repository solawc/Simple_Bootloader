#ifndef __pins_robin_e3_h
#define __pins_robin_e3_h

#define MKS_BOARD_NAME      "Robin E3 v2.0"

#define BL_NAME             "1:/ROBIN_E3_V2.bin"
#define BL_OLD_NAME         "1:/ROBIN_E3_V2.CUR"

#define SD_USE_SPI   


#define BOARD_SD_SCK_PORT   GPIOB
#define BOARD_SD_SCK_PIN    GPIO_PIN_13

#define BOARD_SD_MISO_PORT  GPIOB
#define BOARD_SD_MISO_PIN   GPIO_PIN_14

#define BOARD_SD_MOSI_PORT  GPIOB
#define BOARD_SD_MOSI_PIN   GPIO_PIN_15

#define BOARD_SD_CS_PORT    GPIOA
#define BOARD_SD_CS_PIN     GPIO_PIN_15

#define BOARD_SD_DET_PORT   GPIOC
#define BOARD_SD_DET_PIN    GPIO_PIN_10

#endif
