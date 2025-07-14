#include "stm32f4xx.h"
#include <stdio.h>

/*Tested with ARM Compiler : version 5*/



/*MCU - LCD connection pinout
 PC0-PC7 for LCD D0-D7
 PB5 for LCD R/S
 PB6 for LCD R/W
 PB7 for LCD EN
 */
 
#define RS 0x20     
#define RW 0x40     
#define EN 0x80     

void delayMs(int n);

void GPIO_Init(void);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_Init(void);

int main(void) {
    LCD_Init();

    while(1) {
        LCD_data('H');
        LCD_data('e');
        LCD_data('l');
        LCD_data('l');
        LCD_data('o');
        delayMs(500);

        LCD_command(1);
        delayMs(500);
    }
}


void LCD_Init(void) {
    GPIO_Init();

    delayMs(30);          
    LCD_command(0x30);	
    delayMs(10);
    LCD_command(0x30);
    delayMs(1);
    LCD_command(0x30);   

    LCD_command(0x38);      //set 8-bit data, 2-line, 5x7 font 
    LCD_command(0x06);      //move cursor right after each char 
    LCD_command(0x01);      //clear screen, move cursor to home
    LCD_command(0x0F);      //turn on display, cursor blinking 
}

void GPIO_Init(void) {

    RCC->AHB1ENR |=  0x06;        
    GPIOB->MODER |=  0x5400;   
    GPIOB->BSRR = 0x00C;       // Set EN and RW low
    //Set PC0-PC7 as output
    GPIOC->MODER |=  0x00005555;   
}

void LCD_command(unsigned char command) {
    GPIOB->BSRR = (RS | RW) << 16;  // RS = 0, R/W = 0 
    GPIOC->ODR = command;           
    GPIOB->BSRR = EN;               
    delayMs(0);
    GPIOB->BSRR = EN << 16;         // clear EN 
}

void LCD_data(char data) {

    GPIOB->BSRR = RS;               // RS = 1 
    GPIOB->BSRR = RW << 16;         // R/W = 0 
    GPIOC->ODR = data;              
    GPIOB->BSRR = EN;               
    delayMs(0);
    GPIOB->BSRR = EN << 16;         // clear EN 
}






/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int delay) {
    int i;
    for (; delay > 0; delay--){
        for (i = 0; i < 3195; i++) 
				{}
			}
}
