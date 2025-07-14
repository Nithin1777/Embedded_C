#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/



int main(void) {
    RCC->AHB1ENR |= 1;              
    
    GPIOA->AFR[0] |= 0x00100000;   
    GPIOA->MODER |=  0x00000800;
    
    RCC->APB1ENR |= 1;              // enable TIM2 clock 
    TIM2->PSC = 10 - 1;             // divided by 10 
    TIM2->ARR = 26667 - 1;          // divided by 26667 
    TIM2->CNT = 0;
    TIM2->CCMR1 = 0x0060;          
    TIM2->CCER = 1;                
    TIM2->CCR1 = 8889 - 1;          
    TIM2->CR1 = 1;                 

    while(1) {
    }
}