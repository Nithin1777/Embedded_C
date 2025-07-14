
//PA7 MOSI
//PA5 SCK

//PA4  SS
#include "stm32f4xx.h"                  // Device header



int  main(){

}



void  SPI_Init(void){

	 RCC->AHB1ENR |= 1;      //Enable clock to GPIO A
	 RCC->APB2ENR |= 0x1000;  //Enable clock to SPI1 
	
	 GPIOA->MODER &= ~0x0000CC00;    /* clear pin mode */
	 GPIOA->MODER |=  0x00008800;  
   GPIOA->AFR[0] &= ~0xF0F00000; 
	 GPIOA->AFR[0] |=  0x50500000;
	
	 GPIOA->MODER &= ~0x00000300;
	 GPIOA->MODER |=  0x00000100; 
	
	//SPI Config
	 SPI1->CR1 = 0x31C;    // Set baudrate, 8-bit data frame
   SPI1->CR2 = 0;
	 SPI1->CR1 |= 0x40;
}


void spi_write_data(unsigned char data){
	
	while(!(SPI1->SR & 2)){}     //Wait until transfer buffer is empty
	GPIOA->BSRR = 0x00100000;    // assert slave select
	SPI1->DR = data;						 // write data
  while (SPI1->SR & 0x80) {}   //wait for transmission completion
  GPIOA->BSRR = 0x00000010;    //Deassert slave

}