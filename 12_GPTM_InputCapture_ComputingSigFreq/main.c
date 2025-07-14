#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/


int period;
float frequency;

int main(void) {
    int last = 0;
    int current;
    
    RCC->AHB1ENR |=  1;             
    GPIOA->MODER |=  0x00000800;    
    GPIOA->AFR[0] |= 0x00100000;    
    
    RCC->APB1ENR |= 1;              
    TIM2->PSC = 1600 - 1;          
    TIM2->ARR = 3000 - 1;           
    TIM2->CCMR1 = 0x30;            
    TIM2->CCR1 = 0;                
    TIM2->CCER |= 1;               
    TIM2->CNT = 0;                  
    TIM2->CR1 = 1;                  
        
    RCC->AHB1ENR |=  1;             
    GPIOA->MODER |=  0x00002000;    
    GPIOA->AFR[0] |= 0x02000000;   

    RCC->APB1ENR |= 2;             
    TIM3->PSC = 16000 - 1;          
    TIM3->CCMR1 = 0x41;            
    TIM3->CCER = 0x0B;             
    TIM3->CR1 = 1;                 

    while (1) {
        while (!(TIM3->SR & 2)) {} 
        current = TIM3->CCR1;      
        period = current - last;   
        last = current;
        frequency = 1000.0f / period;
        last = current;
    }
}