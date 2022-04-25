#include <stm32f407xx.h>
#include "spi.h"

void init_spi (void)
{
    /*-----------clk config -----------------------*/

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;                       // enable 16mhz ahb clk for spi1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;                      // gpioa clk enable

    /*-------------- i/o pin config ------------------*/

    GPIOA->MODER |= GPIO_MODER_MODER5_1;                      // Alternative Function for PA5, PA6, PA7 [sck, miso mosi]
    GPIOA->MODER |= GPIO_MODER_MODER6_1;
    GPIOA->MODER |= GPIO_MODER_MODER7_1;


    GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL5_Pos);           // AF5 for sck, miso , mosi
    GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL6_Pos);
    GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL7_Pos);
    GPIOA->PUPDR |= (0x2 << GPIO_PUPDR_PUPD5_Pos);             // pull down for sck[ idle state 0]

    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1;                // high speed
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;

    GPIOA->MODER |= GPIO_MODER_MODER0_0;                       // PA0 General purpose output for chip select 
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1;                // High speed
    

    /*------------- spi config ----------------------------*/

    SPI1->CR1 |= (0b011 << SPI_CR1_BR_Pos);                    // 16mhz/16 = 1 mhz 
    SPI1->CR1 |= SPI_CR1_DFF;                                  // 16 bit data format
    SPI1->CR1 |= (SPI_CR1_SSM)|(SPI_CR1_SSI);                  // software NSS
    SPI1->CR1 |= SPI_CR1_MSTR|SPI_CR1_SPE;                     // enable mstr, spi
    SPI1->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;            // Bidirectional Mode , Transmit only
}


void spi_send_16bit (short data)
{   
    GPIOA->BSRR = GPIO_BSRR_BR0;                                 // enable cs
    while (!(SPI1->SR & SPI_SR_TXE));                            // wait for TXE bit to set

    SPI1->DR = data;

    while (!(SPI1->SR & SPI_SR_TXE));                            // wait for TXE bit to set
    while (SPI1->SR & SPI_SR_BSY);                               // wait for transmission end
    GPIOA->BSRR = GPIO_BSRR_BS0;                                 // disable cs
}
