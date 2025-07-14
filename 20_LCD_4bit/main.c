#include "stm32f4xx.h"
#include <stdio.h>

/*Tested with ARM Compiler : version 5*/



/*MCU - LCD connection pinout
PC4-PC7 for LCD D0-D7
PB5 for LCD R/S
LCD R/W is connected to GND
PB7 for LCD EN
 */
 
#define RS 0x20     
#define EN 0x80    

void delayMs(int n);
void LCD_nibble_write(char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_Init(void);
void GPIO_Init(void);


int main(void) {

    LCD_Init();

    while(1) {

        LCD_data('H');
        LCD_data('e');
        LCD_data('l');
        LCD_data('l');
        LCD_data('o');
        delayMs(500);
        LCD_command(0x01);
        delayMs(500);
    }
}

void LCD_Init(void) {
    GPIO_Init();

    delayMs(30);               
    LCD_nibble_write(0x30, 0);
    delayMs(5);
    LCD_nibble_write(0x30, 0);
    delayMs(1);
    LCD_nibble_write(0x30, 0);
    delayMs(1);

    LCD_nibble_write(0x20, 0);  // set 4-bit data mode
    delayMs(1);
    LCD_command(0x28);          // 4-bit data, 2-line, 5x7 font
    LCD_command(0x06);          // move cursor right 
    LCD_command(0x01);          // clear screen, move cursor to home
    LCD_command(0x0F);          // turn on display, cursor blinking 
}

void GPIO_Init(void) {

    RCC->AHB1ENR |=  0x06;        
    GPIOB->MODER |=  0x00004400;    
    GPIOB->BSRR = 0x00800000;       

    GPIOC->MODER |=  0x00005500;   
}

void LCD_nibble_write(char data, unsigned char control) {

    GPIOC->BSRR = 0x00F00000;      
    GPIOC->BSRR = data & 0xF0;     

    if (control & RS){
        GPIOB->BSRR = RS;
				}
    else{
        GPIOB->BSRR = RS << 16;
				}

    GPIOB->BSRR = EN;
    delayMs(0);
    GPIOB->BSRR = EN << 16;
}

void delayMs(int delay) {
    int i;
    for (; delay > 0; delay--)
        for (i = 0; i < 3195; i++) ;
}


void LCD_command(unsigned char command) {
    LCD_nibble_write(command & 0xF0, 0);    /* upper 4 bits */
    LCD_nibble_write(command << 4, 0);      /* lower 4 bits */

    if (command < 4){
        delayMs(2);  
     }				
    else
        delayMs(1);        
}

void LCD_data(char data) {
    LCD_nibble_write(data & 0xF0, RS);      /* upper nibble first */
    LCD_nibble_write(data << 4, RS);        /* then lower nibble */

    delayMs(1);
}

