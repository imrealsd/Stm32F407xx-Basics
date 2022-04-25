#include <stm32f407xx.h>

void init_sysclk(void)
{
    RCC->CR |= RCC_CR_HSION;                 // enable 16mhz internal clk
    while (!(RCC->CR & RCC_CR_HSIRDY));    // wait for the clk to get ready
}
