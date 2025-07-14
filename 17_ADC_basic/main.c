#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/


int analogValue;


int main (void) {

    RCC->AHB1ENR |=  1;	            
    GPIOA->MODER |=  0xC;    

    RCC->AHB1ENR |=  1;	            
    GPIOA->MODER |=  0xC;          

    /* setup ADC1 */
    RCC->APB2ENR |= 0x100;     
    ADC1->CR2 = 0;                  
    ADC1->SQR3 = 1;                 
    ADC1->CR2 |= 1;                 

    while (1) {
        ADC1->CR2 |= 0x40000000;  
        // Wait for conv complete			
        while(!(ADC1->SR & 2)) {}       
        analogValue = ADC1->DR;              

    }
}