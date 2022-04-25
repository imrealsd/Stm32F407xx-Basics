#include <stm32f407xx.h>
#include <stdint.h>

void init_adc (void)
{   
    /*------  GPIO & CLK -------------------*/

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;                 // Adc clk enable [ for wiriting data into reg] 
    GPIOA->MODER |= GPIO_MODER_MODE3_Msk;               // Analog mode PA3 pin
 
    /*------- ADC REGISTERS----------------*/

    ADC1->CR2  |= ADC_CR2_ADON;                          // power on ADC
    ADC->CCR   |= (0b11 << (ADC_CCR_ADCPRE_Pos));        // 16/8 = 2 MHZ clk for data conversion
    ADC1->SQR1 |= (0b0000 << ADC_SQR1_L_Pos);            // one conversion, using PA3 pin [ ADC1_IN3]
    ADC1->SQR3 = (3 << 0);                               // first conversion in the seq , channel 3  [ ADC1_IN3]
}

int16_t read_adc(void)
{   
    int16_t data;

    ADC1->CR2 |= ADC_CR2_SWSTART;                         // start conversion
    while (!(ADC1->SR & ADC_SR_EOC));                     // wait for conversion complete
    data = ADC1->DR;
    return data;                                          // 12 bit data
}