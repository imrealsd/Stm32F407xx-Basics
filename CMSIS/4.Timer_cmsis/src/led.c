#include <stm32f407xx.h>
#include "led.h"

void init_onboard_led (void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;         // eanble clk for port a

    GPIOA->MODER |= GPIO_MODER_MODER6_0;         // PA6 output
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;  // high speed
}

void onboard_led (char *str)
{
    if (str == "ON"){
        GPIOA->BSRR =  GPIO_BSRR_BR6;     
    } else {
        GPIOA->BSRR = GPIO_BSRR_BS6;
    }
}