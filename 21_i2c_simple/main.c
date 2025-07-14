
#include "stm32f4xx.h"                  // Device header


//SCL  - PB8
//SDA  - PB9


#define  SLAVE_ADDR		0x68
void i2c_Init(void);
int i2c_readbyte(char saddr,char maddr,char *data);
void delayMs(int n);

int main(){
	
	i2c_Init();
	RCC->AHB1ENR |=  1;	 
	GPIOA->MODER &= ~0x00000C00;
	GPIOA->MODER |=  0x00000400; 
	char data;
	
	while(1){
	i2c_readbyte(SLAVE_ADDR,0,&data);
		
		if(data &1)
			GPIOA->ODR |=  0x00000020; 
		else
			GPIOA->ODR &= ~0x00000020;
	  delayMs(10);		
	}

}




void i2c_Init(void){
	
	  RCC->AHB1ENR |=  2; 
	  RCC->APB1ENR |=  0x00200000;    //Enable clock to i2c1
	
	  GPIOB->MODER    &= ~0x000F0000;         /* PB8, PB9 use alternate function */
    GPIOB->MODER    |=  0x000A0000;

	  GPIOB->AFR[1]   &= ~0x000000FF;        //Set alternate functionn as i2c
	  GPIOB->AFR[1]   |=  0x00000044;
	
	  GPIOB->OTYPER   |=  0x00000300;         //Set as open-drain
	
 	  GPIOB->PUPDR    &= ~0x000F0000;         // pull-ups
	  GPIOB->PUPDR    |=  0x00050000;
	
	
	  //I2C Config
		 I2C1->CR1       =   0x8000;      //software reset
		 I2C1->CR1       &= ~0x8000;
		 I2C1->CR2       =   0x0010; 
		 I2C1->CCR       =   80;    //standard mode, 100kHz clock
		 I2C1->TRISE     =   17;   // mx rise time
		 I2C1->CR1       |=  0x0001;  
		
} 


int i2c_readbyte(char saddr,char maddr,char *data){

	 volatile int tmp;
	 while (I2C1->SR2 & 2){}   //  Make sure bus is nit busy
		
	 I2C1->CR1 |=  0x100;     //start 
	 while (!(I2C1->SR1 & 1)){}; 
		 
	 I2C1->DR = saddr << 1; 
	 while (!(I2C1->SR1 & 2)){};   
		tmp = I2C1->SR2; 

	  while (!(I2C1->SR1 & 0x80)){}; 
		  I2C1->DR = maddr; 
	 while (!(I2C1->SR1 & 0x80)){};
		 
		 I2C1->CR1 |= 0x100; 
		while (!(I2C1->SR1 & 1)){}; 
		I2C1->DR = saddr << 1 | 1; 
	
		while (!(I2C1->SR1 & 2)){}; 
			I2C1->CR1 &= ~0x400;  
		tmp = I2C1->SR2;
		
	I2C1->CR1 |= 0x200;
			
			 while (!(I2C1->SR1 & 0x40)){}; 
     *data++ = I2C1->DR; 			
   return 0;				 
}


void delayMs(int n){
	
  for(;n>0;n--){
	   for(int i =0;i<3195;i++);
	}
	
}
