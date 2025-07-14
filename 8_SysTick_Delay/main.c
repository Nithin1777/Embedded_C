#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/

void systickDelayMs(int n);

int main(void) {
    RCC->AHB1ENR |=  1;             
    GPIOA->MODER |=  0x400;    

    while (1) {
        systickDelayMs(50);              
        GPIOA->ODR ^= 0x20;  
    }
}

void systickDelayMs(int n) {

    /* Configure SysTick */
    SysTick->LOAD = 16000;  // Reload with number of clocks per millisecond 
    SysTick->VAL = 0;       // Clear current value register 
    SysTick->CTRL = 0x5;    // Enable the timer 

    for(int i = 0; i < n; i++) {
		
		// Wait until the COUNTFLAG is set
        while((SysTick->CTRL & 0x10000) == 0) 
            { }
    }
    SysTick->CTRL = 0;      
}
