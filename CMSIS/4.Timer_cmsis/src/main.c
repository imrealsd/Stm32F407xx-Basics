#include <stm32f407xx.h>
#include "sys_clk.h"
#include "led.h"
#include "delay.h"


int main (void)
{
    init_sys_clk();
    init_onboard_led();
    init_delay();

    while (1){
        onboard_led("ON");
        delay_ms(1000);
        onboard_led("OFF");
        delay_ms(1000);
    }
}




