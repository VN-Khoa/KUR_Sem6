#include "stm32f10x.h"                  // Device header


void systick_init(void);
void DelayMs(unsigned long t);
void dot(void);
void dash(void);
void SoundLetter(char text);

char text;

int main(void)
{
	systick_init(); // Delay function
	RCC->APB2ENR |= 1;  // Enable clock port A
	RCC->APB2ENR |=0x10; // Enable clock port C
	RCC->APB1ENR |= 0x20000; // Enable USART2
	
	/*Enable pins for USART2*/
	GPIOA->CRL |= 0xB00; // Set PA2 as output mode 50 Mhz and alternate func PP
	GPIOA->CRL |=0x8000; // Set PA3 as input  mode and Input with PU/PD
	
	USART2 -> BRR = 0xEA6;  // Set up baud rate = 9600 bps
	
	USART2->CR1 |= 8; // Enable USART transmit
	USART2->CR1 |= 4; // Enable USART receive
	USART2->CR1 |= 0x2000; // Enable USART
	
	GPIOC->CRH   &=0xFF0FFFFF;     //Reset PC13 
	GPIOC->CRH   |=0x700000;     // General purpose output Open-drain
	GPIOC->BSRR = 0x2000;
	
		while(1)
	{
		//Receive Char
		while((USART2->SR & 0x20) == 0x00)
		{};
		text = USART2->DR;
		
		// Compiler
    if(text >= 'a' && text <='z')
    {      
      text = text - 32;
    }
    if(text < 65 || text > 90)
    {
      text = ' ';
    }
    SoundLetter(text);
    DelayMs(400);
	}
	
}

void systick_init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 5;
}

void DelayMs(unsigned long t)
{
	for(;t>0;t--)
		{
			SysTick->LOAD = 0x11940;
			SysTick->VAL = 0;
			while((SysTick->CTRL & 0x00010000) == 0);
		}
}
void dot(void)
{
	GPIOC->BSRR = 0x2000;
	DelayMs(100);
	GPIOC->BSRR = 0x20000000;
	DelayMs(200);
	GPIOC->BSRR = 0x2000;
}

void dash(void)
{
	GPIOC->BSRR = 0x2000;
	DelayMs(300);
	GPIOC->BSRR = 0x20000000;
	DelayMs(200);
	GPIOC->BSRR = 0x2000;
}

void SoundLetter(char text)
{
  switch(text)
  {
    case 'E':
      dot();
      return; 
    case 'T':
      dash();
      return; 
    case 'A':
      dot();
      dash();
      return;
    case 'O':
      dash();
      dash();
      dash();
      return; 
    case 'I':
      dot();
      dot();
      return;
    case 'N':
      dash();
      dot();
      return;
    case 'S':
      dot();
      dot();
      dot();
      return;
    case 'H':
      dot();
      dot();
      dot();
      dot();
      return;
    case 'R':
      dot();
      dash();
      dot();
      return;
    case 'D':
      dash();
      dot();
      dot();
      return;
    case 'L':
      dot();
      dash();
      dot();
      dot();
      return;
    case 'C':
      dash();
      dot();
      dash();
      dot();
      return;
    case 'U':
      dot();
      dot();
      dash();
      return;
    case 'M':
      dash();
      dash();
      return;
    case 'W':
      dot();
      dash();
      dash();
      return;
    case 'F':
      dot();
      dot();
      dash();
      dot();
      return;
    case 'G':
      dash();
      dash();
      dot();
      return;
    case 'Y':
      dash();
      dot();
      dash();
      dash();
      return;
    case 'P':
      dot();
      dash();
      dash();
      dot();
      return;
    case 'B':
      dash();
      dot();
      dot();
      dot();
      return;
    case 'V':
      dot();
      dot();
      dot();
      dash();
      return;
    case 'K':
      dash();
      dot();
      dash();
      return;
    case 'J':
      dot();
      dash();
      dash();
      dash();
      return;
    case 'X':
      dash();
      dot();
      dot();
      dash();
      return;
    case 'Q':
      dash();
      dash();
      dot();
      dash();
      return;
    case 'Z':
      dash();
      dash();
      dot();
      dot();
      return;
    case ' ':
      DelayMs(400);
      return; 
  }
}


