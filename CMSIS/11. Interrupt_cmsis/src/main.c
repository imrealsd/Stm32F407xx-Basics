#include <stm32f407xx.h>
#include <stdint.h>
#include "sysclk.h"

void init_exti0 (void);
void init_led (void);
void delay_ms (int32_t);

int main()
{
    init_sysclk();
    init_exti0();
    init_led();

    while(1){}
}



void EXTI0_IRQHandler  (void)                                          // ISR for External interrupt line 0
{   
    GPIOA->ODR = ~ (GPIOA->ODR);                                       // toggle led pin

    if (EXTI->PR & EXTI_PR_PR0){

        EXTI->PR  = (1 << EXTI_PR_PR0_Pos);                           // clear interrupt pending flag
        
    }
    delay_ms(500);
}

/* led cathode pin is connected to PA0
 * we will turn the led on and off by 
 * tggling the PA0 pin
*/


void init_led (void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;                           // GPIOA clk enable
    GPIOA->MODER |= GPIO_MODER_MODE0_0;                            // PA0 as output pin
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_0;                    // medium speed
    GPIOA->ODR &= ~(1 << GPIO_ODR_OD0_Pos);                         // Initially pin is low;
} 

/* Button is connected to PB0
 * Pressing the button will cause
 * the pin to go high level and the
 * interrupt occurs [rising edge triggered]
*/


void init_exti0 (void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;                            // GPIOB clk enable
    GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODE0_Pos);                // PB0 input pin
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD0_1;                             // Pull down 

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;                           // system config. controlller clk enable
    SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PB;                    // PB0 as external interrupt line 0
    EXTI->IMR |=  EXTI_IMR_IM0;                                     // Unmusk ext. interrupt line 0
    EXTI->RTSR |= EXTI_RTSR_TR0;                                    // Rising edge triggerd

    NVIC_SetPriority (EXTI0_IRQn, 1);                               // Set Priority
	NVIC_EnableIRQ (EXTI0_IRQn);                                    // Enable Interrupt
}

void delay_ms (int32_t val)
{
    volatile int32_t i;
    
    for (i = 0; i < 2000*val; i++);
}