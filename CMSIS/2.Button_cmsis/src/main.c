#include <stm32f407xx.h>

void config_clk (void);
void config_gpio (void);
void delay_ms (long);
void onboard_led (char*);
short read_button_k0(void);

int main (void)
{   
    short data;
    config_clk();
    config_gpio();

    while (1){
        data = read_button_k0();
        if(data == 0){
            onboard_led("on");
        } else {
            onboard_led("off");
        }
    }
}

void config_clk (void)
{
    RCC->CR |= RCC_CR_HSION;                      // enable system clk
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;          // enable gpio_a clk
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;          // enable gpio_e clk

    while (!(RCC->CR & RCC_CR_HSIRDY));
}

void config_gpio (void)
{
    GPIOA->MODER |= GPIO_MODER_MODE7_0;           // PA7 output  [0 1]
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;   //  high speed [1 0]

    GPIOE->PUPDR |= GPIO_PUPDR_PUPD4_0;           // pullup enable PA4 [ onboard button k1]
}

void onboard_led (char* str)
{   
    if (str == "on")
        GPIOA->BSRR = GPIO_BSRR_BR_7;             // reset PA7 [ onboard led on] [PA7 coonected to cathode of led]
    else 
        GPIOA->BSRR = GPIO_BSRR_BS7;              // set PA7
}

void delay_ms (long val)
{
    volatile long i;
    for (i = 0; i < (val * 2000); i++){}
}

short read_button_k0 (void)
{
    short val;
    val = GPIOE->IDR & (GPIO_IDR_ID4);
    return val;
}