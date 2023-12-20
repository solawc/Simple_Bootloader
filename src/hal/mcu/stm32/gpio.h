#ifndef _gpio_h
#define _gpio_h

#include "../../../main.h"

extern GPIO_TypeDef * const digital_regs[];
#define GPIO(PORT, NUM) (((PORT)-'A') * 16 + (NUM))
#define GPIO2PORT(PIN) ((PIN) / 16)
#define GPIO2BIT(PIN) (1<<((PIN) % 16))


struct gpio_out {
    void *regs;
    uint32_t bit; 
};

struct gpio_in {
    void *regs;
    uint32_t bit; 
};





 #endif