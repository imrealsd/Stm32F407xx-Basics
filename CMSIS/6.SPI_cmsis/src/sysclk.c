#include <stm32f407xx.h>
#include "sysclk.h"

void init_sys_clk (void)                 // 16Mhz internal clk enable
{
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & (RCC_CR_HSIRDY)));
}

