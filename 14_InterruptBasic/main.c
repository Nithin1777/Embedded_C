#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/



void systickDelayMs(int n);

int counter=0;

int main(void) {
    __disable_irq();                   

    RCC->AHB1ENR |= 4;	                
    RCC->AHB1ENR |= 1;                
    RCC->APB2ENR |= 0x4000;             

    //configure PA5 for LED 
    GPIOA->MODER &= ~0x00000C00;        
    GPIOA->MODER |=  0x00000400;        

    // configure PC13 for push button interrupt 
    GPIOC->MODER &= ~0x0C000000;        
    
    SYSCFG->EXTICR[3] &= ~0x00F0;       
    SYSCFG->EXTICR[3] |= 0x0020;        
    
    EXTI->IMR |= 0x2000;                
    EXTI->FTSR |= 0x2000;              

    NVIC_EnableIRQ(EXTI15_10_IRQn);
    
    __enable_irq();                     
    
    while(1) {
    }
}

void EXTI15_10_IRQHandler(void) {
        GPIOA->BSRR = 0x00000020;   
        systickDelayMs(400);
        GPIOA->BSRR = 0x00200000;   
        systickDelayMs(400);
        GPIOA->BSRR = 0x00000020;   
        systickDelayMs(400);        
        GPIOA->BSRR = 0x00200000;  
        systickDelayMs(400);
				counter++;
        EXTI->PR = 0x2000;         
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
