#include <stm32f407xx.h>
#include <stdint.h>

void init_led (void)                             // 3 Leds are used PA0, PA1, PA2
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER |= GPIO_MODER_MODE0_0;
    GPIOA->MODER |= GPIO_MODER_MODE1_0;
    GPIOA->MODER |= GPIO_MODER_MODE2_0;

    /* All leds are off initially */
    GPIOA->BSRR  = GPIO_BSRR_BS0;         
    GPIOA->BSRR |= GPIO_BSRR_BS1;
    GPIOA->BSRR |= GPIO_BSRR_BS2;
}

void glow_led (int8_t value)
{
    switch (value)
    {
    case 0:                                         // OFF ALL LED
        GPIOA->ODR = 0xFFFF;
        break;

    case 1:
        GPIOA->ODR = ~(1 << 0);     // on led 0
        break;
    
    case 2:
        GPIOA->ODR = ~(1 << 1);   // on led 1
        break;
    case 3:
        GPIOA->ODR = ~(1 << 2);  // on led 2
        break;

    default:
        return;
    }
}