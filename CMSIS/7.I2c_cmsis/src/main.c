#include <stm32f407xx.h>
#include "sysclk.h"
#include "I2c_lcd.h"


int main (void)
{   
    init_sys_clk();
    init_i2c();

    start_i2c();
    send_i2c_addr(0x27 << 1 | 0);

    while (1){

        send_i2c(0xFF);
        delay_ms(500);
        send_i2c(0x00);
        delay_ms(500);
        debug_led();
    }
}



