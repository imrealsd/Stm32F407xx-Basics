#include <stm32f407xx.h>
#include <stdint.h>
#include "sysclk.h"

void config_RNG (void);
void config_led (void);
void delay_ms (int32_t);
void blink_led (void);
int32_t get_Random_Number (void);

int main()
{   
    int32_t val;

    init_sysclk();
    config_RNG();
    config_led();

    while (1){
        val = get_Random_Number();
        delay_ms(100);
    }
}


void config_RNG (void)                                        // [ RNG needs 48Mhz dedicated PLL clk] 
{   
    RCC->PLLCFGR = 0x00000000;
    RCC->PLLCFGR &= ~(1 << RCC_PLLCFGR_PLLSRC_Pos);            //  16Mhz HSI clk as PLL input
    RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLM_Pos);               // 16/8 = 2Mhz vco input
    RCC->PLLCFGR |= (96 << RCC_PLLCFGR_PLLN_Pos);              // 96 x 2 = 192Mhz vco output
    RCC->PLLCFGR |= (4 << RCC_PLLCFGR_PLLQ_Pos);               // VCO division factor for RNG [196/4 = 48Mhz]

    RCC->CR |= RCC_CR_PLLON;                                   // Main PLL ON
    while (!(RCC->CR & RCC_CR_PLLRDY));                        // wait for PLL ready

    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;                         // Clk enable for RNG  
    RNG->CR |= RNG_CR_RNGEN;                                   // RNG enable
}

int32_t get_Random_Number(void)
{
    int32_t num = 0;

    if ((!(RNG->SR & RNG_SR_SECS)) && (!(RNG->SR & RNG_SR_CECS))){

        num = RNG->DR;                                      // read generated random number
        blink_led();
    }
    return num;
}


void config_led (void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODE6_0;                     // PA6 output [onboard led]
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_1;               // Highspeed
    GPIOA->BSRR = GPIO_BSRR_BS_6;                           // Initially pin high
}

void delay_ms (int32_t val)
{
    volatile int32_t i;
    for (i = 0; i < (val * 2000); i++);
}

void blink_led (void)
{
    GPIOA->BSRR = GPIO_BSRR_BR_6;                       // blink led
    delay_ms(500);
    GPIOA->BSRR = GPIO_BSRR_BS_6;
    delay_ms(500);
}