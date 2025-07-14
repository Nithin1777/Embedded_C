#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/

int main(void) {
    RCC->AHB1ENR |=  1;            
    GPIOA->MODER |=  0x400;    

    /* Configure SysTick */
    SysTick->LOAD = 3200000-1;      
		SysTick->VAL = 0;
    SysTick->CTRL = 5;    

    while (1) {
		
		   if(SysTick->CTRL & 0x10000)

        GPIOA->ODR ^= 0x20;
    }
}