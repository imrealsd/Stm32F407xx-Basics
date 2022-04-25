#include <stm32f407xx.h>

void init_sys_clk (void)
{
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));
}