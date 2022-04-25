#include <stm32f407xx.h>
#include "servo.h"

void init_servo (void)
{
    /*------------------gpio config-------------------------------*/

    RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOAEN;                                     // GPIOA clk enbale
    GPIOA->MODER  |= GPIO_MODER_MODE0_1;                                      // Tim2 ch1 PA0
    GPIOA->AFR[0] |= (0x1 << GPIO_AFRL_AFSEL0_Pos);                           // AF1

    /*------------------pwm config---------------------------------*/

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;                                        // timer2 clk enable 16MHz
    TIM2->PSC     = 15;                                                        // clk = (16/16) = 1 MHz, 1 clk period = 1 micro sec

	TIM2->CR1    |= TIM_CR1_ARPE;                                              // upcounting, ARR preload enable 

	TIM2->CCMR1  |= (0b110 << TIM_CCMR1_OC1M_Pos);                             // pwm mode 1
	TIM2->CCMR1  |= TIM_CCMR1_OC1PE;										   // output compare preload register enable
	TIM2->CCER   |= TIM_CCER_CC1E;                                             // Output compare enable, active high

	TIM2->EGR |= TIM_EGR_UG;                                                   // Initialize ARR with the written values [ from preload ]

	/*-----------------------------------------------------------------*/

    /**  counter counts from zero to ARR register value
      *  pwm signal output oc1 remain 1 until compare match [ccr1 = arr]
      *  pwm signal output become 0 after compare match
      *  and remain 0 untill ARR value is reached , then set again
      *	 pwm mode 1
      * pwm o/p signal total period 20 ms [ 50hz freq for servo]  
	  */

}

void servo_left (void)                                                          // 1ms high pulse , 19 ms low , servo left
{	
	TIM2->ARR  = 20000;                                                         // total period 20 ms
	TIM2->CCR1 = 1000;                                                          // compare register value
	TIM2->EGR |= TIM_EGR_UG;                                                    // Initialize compare register value [ from preload]
	TIM2->CR1 |= TIM_CR1_CEN;                                                   // counter enable
}


void servo_straight (void)                                                       // 1.5 ms high pulse , 18.5 ms low , servo left
{	
	TIM2->ARR  = 20000;
	TIM2->CCR1 = 1500;                                                            // compare register value
	TIM2->EGR |= TIM_EGR_UG;                                                      // Initialize compare register value [ from preload]
	TIM2->CR1 |= TIM_CR1_CEN;                                                     // counter enable
}


void servo_right (void)                                                           // 2 ms high pulse , 18 ms low , servo left
{	
	TIM2->ARR  = 20000;
	TIM2->CCR1 = 2000;                                                            // compare register value
	TIM2->EGR |= TIM_EGR_UG;                                                      // Initialize compare register value [ from preload]
	TIM2->CR1 |= TIM_CR1_CEN;                                                     // counter enable
}


void servo_stop(void)
{
	TIM2->CR1 &= ~(1 << TIM_CR1_CEN_Pos);
}