#ifndef __HID_boot_port_h
#define __HID_boot_port_h

#ifdef __cplusplus
 extern "C" {
#endif


#include "../../main.h"

/* For STM32 BreakUp Regiester addr */
#define HID_MAGIC_NUMBER_BKP_INDEX  0x00000004U
#define HID_MAGIC_NUMBER_BKP_VALUE  0x424C

void HID_BootDelayMs(uint32_t ms);
uint32_t bootGet_BAK_Register(void);
uint8_t bootGet_Boot_1_Pin(void);
void bootSet_EnableBkUpAccess(void);
void bootSet_DisableBkUpAccess(void);
void bootSet_BAK_Register(void);
void bootSendReport(uint8_t *report, uint16_t len);
void boot_GPIO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __HID_boot_port_h */
