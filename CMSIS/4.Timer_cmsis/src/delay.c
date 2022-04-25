#include <stm32f407xx.h>
#include "delay.h"

void init_delay (void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;         // 16Mhz AHB1 clk given to ABP1

    TIM2->PSC |= 15;                            // APB1 clk / (16) = 1 Mhz [timer freq]
    TIM2->ARR = 1000;                           // 1 period takes 1 micro sec , 1000 period takes 1 mil. sec
}

void delay_ms (long val)
{
    while (val --){
        TIM2->CNT = 0;                              // reset counter value
        TIM2->CR1 |= TIM_CR1_CEN;                   // counter enable , upcounter

        while (TIM2->CNT != TIM2->ARR);
        TIM2->CR1 &= ~(1 << TIM_CR1_CEN_Pos);       // disable counter
    }
}