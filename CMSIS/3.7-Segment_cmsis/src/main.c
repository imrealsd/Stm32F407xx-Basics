#include <stm32f407xx.h>

void display_count (void);
void delay_ms (long);
void config_gpio (void);
void config_clk (void);

int main (void)
{
    config_clk();
    config_gpio();

    while (1){
        display_count();
    }
}
void config_clk (void)
{
    RCC->CR |= RCC_CR_HSION;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    while (!(RCC->CR & RCC_CR_HSIRDY));
}


void config_gpio (void)
{
    GPIOA->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0;                /* PA0 to PA7 output data, PA8 to PA11 digit control */
    GPIOA->MODER |= GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0;
    GPIOA->MODER |= GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0;
    GPIOA->MODER |= GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0;
    GPIOA->MODER |= GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0;
    GPIOA->MODER |= GPIO_MODER_MODE10_0 | GPIO_MODER_MODE11_0;

    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1 | GPIO_OSPEEDER_OSPEEDR1_1;   /* High speed output */
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1 | GPIO_OSPEEDER_OSPEEDR3_1;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1 | GPIO_OSPEEDER_OSPEEDR5_1;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR7_1;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1 | GPIO_OSPEEDER_OSPEEDR11_1;
}

void delay_ms (long val)
{
    volatile long i;
    for (i = 0; i < (val * 1000); i++){}
}


void display_count (void)
{
    long count;
    short d1, d2, d3, d4, i;
    char num[10] = {0xBf, 0x86, 0xDB, 0xCF, 0XE6, 0xED, 0xFD, 0x87, 0xFF, 0xE7};

    for (count = 0; count < 10000; count++){

        d1 = (count ) % 10;
        d2 = (count / 10) % 10;
        d3 = (count / 100) % 100;
        d4 = (count / 1000) % 1000;

        for (i = 0; i < 200; i++){

            GPIOA->ODR = (num[d1]) | (0xFF << 8);                 // data 
            GPIOA->ODR &= ~(1 << 8);                              // enable d1
            delay_ms(2);
            GPIOA->ODR |= (1 << 8);                               // disable d1

            GPIOA->ODR = (num[d2]) | (0xFF << 8);                 // data 
            GPIOA->ODR &= ~(1 << 9);                              // enable d2
            delay_ms(2);
            GPIOA->ODR |= (1 << 9);                               // disable d2

            GPIOA->ODR = (num[d3]) | (0xFF << 8);                 // data 
            GPIOA->ODR &= ~(1 << 10);                             // enable d3
            delay_ms(2);
            GPIOA->ODR |= (1 << 10);                              // disable d3

            GPIOA->ODR = (num[d4]) | (0xFF << 8);                 // data 
            GPIOA->ODR &= ~(1 << 11);                             // enable d4
            delay_ms(2);
            GPIOA->ODR |= (1 << 11);                              // disable d4
        }
    }
}  