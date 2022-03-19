#ifndef __pins_znp_robin_nano_dw_h
#define __pins_znp_robin_nano_dw_h

#define MKS_BOARD_NAME      "ZNP ROBIN NANO DW"

#define BL_NAME             "1:/ZNP_ROBIN_NANO.bin"
#define BL_OLD_NAME         "1:/ZNP_ROBIN_NANO.CUR"

#define BOARD_SD_SCK_PORT   GPIOB
#define BOARD_SD_SCK_PIN    GPIO_PIN_13

#define BOARD_SD_MISO_PORT  GPIOB
#define BOARD_SD_MISO_PIN   GPIO_PIN_14

#define BOARD_SD_MOSI_PORT  GPIOB
#define BOARD_SD_MOSI_PIN   GPIO_PIN_15

#define BOARD_SD_CS_PORT    GPIOB
#define BOARD_SD_CS_PIN     GPIO_PIN_12

#define BOARD_SD_DET_PORT   GPIOC
#define BOARD_SD_DET_PIN    GPIO_PIN_3

#endif
