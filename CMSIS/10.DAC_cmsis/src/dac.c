#include <stm32f407xx.h>
#include <stdint.h>
#include "dac.h"

void dac_init (void)
{   
    /*------- DAC GPIO---------------------------*/

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODE4_Msk;            // analog mode PA4  

    /*-------------------------------------------*/

    RCC->APB1ENR |= RCC_APB1ENR_DACEN;             // dac clk enable
    DAC1->CR |= DAC_CR_EN1 | DAC_CR_BOFF1;         // DAC channel 1 and Dac channel 1 buffer enable
}

void write_dac (int8_t data)
{
    DAC1->DHR8R1 = data;
}