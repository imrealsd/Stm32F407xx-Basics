/* PA5 - SCK , PA7 - MOSI , PA0 - CS , PA6 MISO */  

#include <stm32f407xx.h>
#include "sysclk.h"
#include "spi.h"

void init_max7219(void);
void delay_ms (long);
void show_pattern (void);

int main (void)
{
    init_sys_clk();
    init_spi();
    delay_ms(1000);                                   // wait for the module to power up

    init_max7219();

    show_pattern();

    while(1);
}

void init_max7219 (void)
{
    spi_send_16bit((0x09 << 8)| 0x00);                // disable decoding [ not required in matrix]
    spi_send_16bit((0x0B << 8)| 0x07);                // scan digit 0 to 7
    spi_send_16bit((0x0C << 8)| 0x01);                // turn on chip
    spi_send_16bit((0x0A << 8)| 0x0F);                // max intensity
}

void delay_ms (long val)
{
    volatile long i;
    for(i = 0; i < (val * 2000); i++){}
}

void show_pattern (void)
{
    spi_send_16bit((0x01 << 8)| (0xFF));
    spi_send_16bit((0x02 << 8)| (0x81));
    spi_send_16bit((0x03 << 8)| (0x81));
    spi_send_16bit((0x04 << 8)| (0x81));
    spi_send_16bit((0x05 << 8)| (0x81));
    spi_send_16bit((0x06 << 8)| (0x81));
    spi_send_16bit((0x07 << 8)| (0x81));
    spi_send_16bit((0x08 << 8)| (0xFF));
}