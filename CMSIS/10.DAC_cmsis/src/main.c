#include <stm32f407xx.h>
#include <stdint.h>
#include "sys_clk.h"
#include "dac.h"

void delay_ms (int32_t);

int main()
{   
    init_sys_clk();
    dac_init();

    while (1){

        write_dac(0xFF);
        delay_ms(2000);
        write_dac(0x00);
        delay_ms(2000);
    }
}


void delay_ms (int32_t val)
{
    volatile int32_t i;
    for (i = 0; i < (val * 2000); i++);
}