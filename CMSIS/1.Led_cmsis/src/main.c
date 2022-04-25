#include <stm32f407xx.h>

void config_clk (void);
void config_gpio (void);
void delay_ms (long);
void blink_onboard_led (void);

int main (void)
{
    config_clk();
    config_gpio();

    while (1){
        blink_onboard_led();
    }
}

void config_clk (void)
{
    RCC->CR |= RCC_CR_HSION;                      // enable system clk
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;          // enable gpio_a clk

    while (!(RCC->CR & RCC_CR_HSIRDY));
}

void config_gpio (void)
{
    GPIOA->MODER |= GPIO_MODER_MODE7_0;           // PA7 output  [0 1]
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;   //  high speed [1 0]
}

void blink_onboard_led (void)
{
    GPIOA->BSRR = GPIO_BSRR_BR_7;                // reset PA7
    delay_ms(500);
    GPIOA->BSRR = GPIO_BSRR_BS7;                 // set PA7
    delay_ms(500);
}

void delay_ms (long val)
{
    volatile long i;
    for (i = 0; i < (val * 2000); i++){}
}

