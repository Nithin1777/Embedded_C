#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/

void delayMs(int delay); 



int main(void) {
    RCC->AHB1ENR |=  4;                
    RCC->AHB1ENR |=  1;              

    GPIOA->MODER |=  0x400;       


    while(1) {
        if (GPIOC->IDR & 0x2000)        
            GPIOA->BSRR = 0x00200000;   
        else
            GPIOA->BSRR = 0x00000020;   
    }
}
