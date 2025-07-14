#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/

void USART2_init (void);
void USART2_write (int ch);

void delayMs(int delay); 

int main (void) {
    USART2_init();          /* initialize USART2 */

    while(1) {              /* Loop forever */
        USART2_write('Y');
        USART2_write('i');
        delayMs(10);        /* leave a gap between messages */
    }
}



void USART2_init (void) {

    RCC->APB1ENR |= 0x20000;    
    RCC->AHB1ENR |= 1;          
    GPIOA->AFR[0] |=  0x0700;  
    GPIOA->MODER  |=  0x0020;   /* Set PA2 to alternate function */


    USART2->BRR = 0x0683;       // 9600  @ 16 MHz 
    USART2->CR1 = 0x0008;       // enable Tx
    USART2->CR1 |= 0x2000;      // enable USART2 
}

void USART2_write (int ch) {
     // wait until Tx buffer empty
    while (!(USART2->SR & 0x0080)) {}   
    USART2->DR = (ch & 0xFF);
}


void delayMs(int delay) {
    int i;
    for (; delay > 0; delay--)
        for (i = 0; i < 3195; i++) ;
}
