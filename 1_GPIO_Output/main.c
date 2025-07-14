#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/

void delayMs(int delay); 

int main(void) {

          RCC->AHB1ENR |= 1;   
          GPIOA->MODER |=0x400;
					 
	  while (1) {

				 GPIOA->ODR |= 0x20;
				 delayMs(100);
				 GPIOA->ODR &=~0x20;
				 delayMs(100);
				 
     
		 }
}

void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 3195; i++) ;
}

