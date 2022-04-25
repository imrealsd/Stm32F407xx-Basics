#include <stm32f407xx.h>
#include "I2c.h"
#define SLAVE_ADDRESS 0x27                   // PCF8574 IO EXPANDER

void init_i2c (void)
{
    /*------------------ Gpio init --------------------------------*/
    RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOBEN;                                     // GPIOB clk enable
    
    GPIOB->MODER  |= GPIO_MODER_MODE6_1;                                       // sck PB6
    GPIOB->MODER  |= GPIO_MODER_MODE7_1;                                       // sda PB7
    GPIOB->AFR[0] |= (0x4 << GPIO_AFRL_AFSEL6_Pos);
    GPIOB->AFR[0] |= (0x4 << GPIO_AFRL_AFSEL7_Pos);

    GPIOB->OTYPER |= (1 << GPIO_OTYPER_OT6_Pos) | ( 1 << GPIO_OTYPER_OT7_Pos);
    GPIOB->OSPEEDR |= (0b11 << GPIO_OSPEEDR_OSPEED6_Pos) | ( 0b11 << GPIO_OSPEEDR_OSPEED7_Pos);
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD6_0 | GPIO_PUPDR_PUPD7_0;
    
    /*--------------------i2c init----------------------------------*/

    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;                                       // I2C1 clk enable
    I2C1->CR2 |= (0b000010 << I2C_CR2_FREQ_Pos);                              // 2Mhz clk to I2c, T_pclk = 500 ns 
    I2C1->CCR |= (0xA << I2C_CCR_CCR_Pos);                                    // SCL = 100 khz [T_high or T_low = 500 * 10 = 5000 ns], sm mode
    I2C1->TRISE = 3;                                                          // (1000/500) + 1 = 3
    I2C1->CR1 |= I2C_CR1_PE;                                                  // I2c peripheral enable
}

void start_i2c (void)
{
   I2C1->CR1 |= I2C_CR1_START;
   while (!(I2C1->SR1 & I2C_SR1_SB));                                     // wait for start cond to generate
}

void stop_i2c (void)
{   
    while (!(I2C1->SR1 & I2C_SR1_BTF));                                    // wait for byte tranasfer finish
    I2C1->CR1 |= I2C_CR1_STOP;
}

void send_i2c (char data)
{   
    while (!(I2C1->SR1 & I2C_SR1_TXE));                                    // wait for transmit data register to empty  or ack recieved
    I2C1->DR = (0x00FF & data);
    while (!(I2C1->SR1 & I2C_SR1_BTF));                                    // wait for byte tranasfer finish
}

void send_i2c_addr (char addr)                                             // No TXE flag for addr
{
    I2C1->DR = (0x00FF & addr);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));                                   // wait for address to transmit
    int16_t temp = I2C1->SR1 | I2C1->SR2;                                  // reading SR1 and SR2 to clear addr flag
}

/*---------------------------------------------------------------------*/
/**
 * upper 4 bit of send_i2c() is data [pa4 to pa7]
 * lower 4 bit is rs, en, r/w, [pa0 to pa3]
*/


// void lcd_cmd (char cmd)                  
// {   
//     char upper_nibble = cmd & 0xF0;
//     char lower_nibble = 0xF0 & (cmd << 4);

//     start_i2c();
//     send_i2c_addr(SLAVE_ADDRESS << 1);                                        // slave address + write bit


//     send_i2c((upper_nibble)| 0x08);                                           // en = 0, rs = 0 , led on
//     send_i2c((upper_nibble)| 0x0C);                                           // en = 1, rs = 0 , led on
//     wait();
//     send_i2c((upper_nibble)| 0x08);                                           // en = 0, rs = 0, led on

//     send_i2c((lower_nibble)| 0x08);                                           // en = 0, rs = 0, led on
//     send_i2c((lower_nibble)| 0x0C);                                           // en = 1, rs = 0, led on
//     wait();
//     send_i2c((lower_nibble)| 0x08);                                           // en = 0, rs = 0, led on

//     stop_i2c();
// }


// void lcd_data (char data)
// {
//     char upper_nibble = 0xF0 & data;
//     char lower_nibble = 0xF0 & (data << 4);

//     start_i2c();

//     send_i2c_addr(SLAVE_ADDRESS << 1);


//     send_i2c((upper_nibble)| 0x09);                                          // en = 0, rs = 1, led on
//     send_i2c((upper_nibble)| 0x0D);                                          // en = 1, rs = 1, led on
//     wait();
//     send_i2c((upper_nibble)| 0x09);                                          // en = 0, rs = 1, led on

//     send_i2c((lower_nibble)| 0x09);                                          // en = 0, rs = 1;, led on
//     send_i2c((lower_nibble)| 0x0D);                                          // en = 1, rs = 1, led on
//     wait();
//     send_i2c((lower_nibble)| 0x09);                                          // en = 0, rs = 1, led on

//     stop_i2c();
// }


// void lcd_str (char *str)
// {
//     while (*str != '\0'){
//         lcd_data(*str);
//         str++;
//     }
// }

// void init_lcd (void)
// {   
//     lcd_cmd(0x28);                                                          // 4 bit , 2 line
// 	lcd_cmd(0x0C);                                                          // display on cursor off
// 	lcd_cmd(0x06);                                                          // auto increment
// 	lcd_cmd(0x01);                                                          // clear display
// 	lcd_cmd(0x80);                                                          // cursor at home
// }


// void wait (void)
// {
//     volatile long i;
//     for(i = 0; i < 1000; i++);
// }


// /*------------------------------------*/

void debug_led (void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODE6_0;

    GPIOA->BSRR = GPIO_BSRR_BR_6;
    delay_ms(500);
    GPIOA->BSRR = GPIO_BSRR_BS6;
    delay_ms(500);
}


void delay_ms (long val)
{
    volatile long i;
    for (i = 0; i < (val*2000); i++);
}