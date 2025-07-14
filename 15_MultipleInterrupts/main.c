#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/



void systickDelayMs(int n);

volatile int pb10_counter;
volatile int pc13_counter;

int main(void) {
    __disable_irq();                    

    RCC->AHB1ENR |= 1;                  
    RCC->AHB1ENR |= 4;	                
    RCC->AHB1ENR |= 2;                  
    RCC->APB2ENR |= 0x4000;             

    GPIOA->MODER |=  0x400;       

    
    SYSCFG->EXTICR[3] |= 0x0020;          
    EXTI->IMR |= 0x2000;                // unmask EXTI13 
    EXTI->FTSR |= 0x2000;               // select falling edge trigger 

    GPIOB->PUPDR |=  0x00100000;        // Enable pull up resistor 
    
    SYSCFG->EXTICR[2] |= 0x0100;        // Select port B for EXTI10 
    
    EXTI->IMR |= 0x0400;                // Unmask EXTI10 
    EXTI->FTSR |= 0x0400;               // Select falling edge trigger

    NVIC_EnableIRQ(EXTI15_10_IRQn);     
    __enable_irq();                    
    
    while(1) {
    }
}

void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR == 0x2000) {      
			
			 pc13_counter++;

       EXTI->PR = 0x2000;          //clear interrupt pending flag 
    }
    else if (EXTI->PR == 0x0400) {  
		
				pb10_counter++;

        EXTI->PR = 0x0400;          //clear interrupt pending flag 
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

