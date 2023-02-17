#include "delay.h"

#if defined(STM32F427_437xx)
	#include "stm32f4xx.h"
#else	
	unsigned int SystemCoreClock = 18000000;
#endif

void delay(unsigned int count){ 

  for(unsigned int i=0; i < count; i++);	 
  
}

void delay_ms(unsigned int ms){ 
	unsigned int count=0;

	count=ms*(SystemCoreClock/6000);

  for(unsigned int i=0; i < count; i++);	   
}
