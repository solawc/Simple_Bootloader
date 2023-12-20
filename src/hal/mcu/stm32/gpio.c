#include "gpio.h"



// compiler.h
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


GPIO_TypeDef * const digital_regs[] = {
    ['A' - 'A'] = GPIOA, GPIOB, GPIOC,
#ifdef GPIOD
    ['D' - 'A'] = GPIOD,
#endif
#ifdef GPIOE
    ['E' - 'A'] = GPIOE,
#endif
#ifdef GPIOF
    ['F' - 'A'] = GPIOF,
#endif
#ifdef GPIOG
    ['G' - 'A'] = GPIOG,
#endif
#ifdef GPIOH
    ['H' - 'A'] = GPIOH,
#endif
#ifdef GPIOI
    ['I' - 'A'] = GPIOI,
#endif
};

// static int regs_to_pin(GPIO_TypeDef *regs, uint32_t bit)
// {
//     int i;
//     for (i=0; i<ARRAY_SIZE(digital_regs); i++)
//         if (digital_regs[i] == regs)    // 查找对应的GPIO端口, bit用于计算对应的GPIO引脚
//             return GPIO('A' + i, ffs(bit)-1);
//     return 0;
// }

// Verify that a gpio is a valid pin
static int gpio_valid(uint32_t pin)
{
    uint32_t port = GPIO2PORT(pin);
    return port < ARRAY_SIZE(digital_regs) && digital_regs[port];
}

struct gpio_out gpio_out_setup(uint32_t pin, uint32_t val)
{
    if (!gpio_valid(pin)) 
        DEBUG_PRINT("Not an output pin!");

    GPIO_TypeDef *regs = digital_regs[GPIO2PORT(pin)];

    struct gpio_out g = { .regs=regs, .bit=GPIO2BIT(pin) };

    GPIO_InitTypeDef GPIO_Init = {
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pin = pin,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
    };

    HAL_GPIO_Init(g.regs, &GPIO_Init);

    return g;
}

void gpio_out_toggle_noirq(struct gpio_out g)
{
    GPIO_TypeDef *regs = g.regs;
    regs->ODR ^= g.bit;
}

void gpio_out_write(struct gpio_out g, uint32_t val)
{
    GPIO_TypeDef *regs = g.regs;
    if (val)
        regs->BSRR = g.bit;
    else
        regs->BSRR = g.bit << 16;
}

struct gpio_in gpio_in_setup(uint32_t pin, uint32_t val)
{
    if (!gpio_valid(pin)) 
        DEBUG_PRINT("Not an input pin!");

    GPIO_TypeDef *regs = digital_regs[GPIO2PORT(pin)];

    struct gpio_in g = { .regs=regs, .bit=GPIO2BIT(pin) };

    GPIO_InitTypeDef GPIO_Init = {
        .Mode = GPIO_MODE_INPUT,
        .Pin = pin,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
    };

    HAL_GPIO_Init(g.regs, &GPIO_Init);

    return g;
}

uint8_t gpio_in_read(struct gpio_in g)
{
    GPIO_TypeDef *regs = g.regs;
    return !!(regs->IDR & g.bit);
}
