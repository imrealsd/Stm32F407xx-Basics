#include <stm32f407xx.h>
#include "sysclk.h"
#include "servo.h"

void delay_ms (long);
int main (void)
{
    init_sys_clk();
    init_servo();
    delay_ms(500);


    while(1){
        
        servo_left();
        delay_ms(1000);
        servo_stop();

        servo_straight();
        delay_ms(1000);
        servo_stop();

        servo_right();
        delay_ms(1000);
        servo_stop();
    }
}


void delay_ms (long val)
{
    volatile long i;
    for(i = 0; i < (val * 2000); i++);
}
