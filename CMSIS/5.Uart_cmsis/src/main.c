/* stm32f407 uart , tested through arduino [ as usb to ttl converter, bypassing bootloader]
 * connect arduino rst to gnd , connect stm32 gnd to arduino gnd
 * connect stm32 tx to arduino tx [ arduino tx is usb to ttls controller's rx]
*/


#include <stm32f407xx.h>
#include "uart.h"
#include "sys_clk.h"

void delay_ms (long);

int main (void)
{   
    init_sys_clk();
    init_uart();

    while (1){
        send_uart_str("subhadeep");
        send_uart('\n');
        delay_ms(1000);
    }
}

void delay_ms (long val)
{
    volatile long i;
    for (i = 0; i < (val * 2000); i++){}
}