#include <stm32f407xx.h>
#include <stdint.h>
#include "led.h"
#include "adc.h"
#include "sys_clk.h"


/* 12 bit adc, [ 0 to 4095]
 * Vref = 3.6 volt
 * value = 0   : 0 volt
 * value = 4095: 3.6 volt
*/

void delay (void);

int main()
{   
    init_sys_clk();
    init_led();
    init_adc();

    int16_t raw_data;

    while (1){
        raw_data = read_adc();

        if (raw_data >= 0 && raw_data <= 1023){
            glow_led(0);
            delay();

        } else if (raw_data >= 1024 && raw_data <= 2046){
            glow_led(1);
            delay();

        } else if (raw_data >= 2047 && raw_data <= 3069){
            glow_led(2);

        } else if (raw_data >= 3070 && raw_data <= 4095){
            glow_led(3);
            delay();

        } else {
            continue;
        }
    }
}

void delay(void)
{
    volatile long i;
    for (i = 0; i < 1000; i++);
}
 

