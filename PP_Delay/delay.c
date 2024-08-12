#include "delay.h"
#include "stm32.h"

void delay(unsigned int count){ 

	unsigned int i=0;
	
	do{										//nie może być for(), bo kompilator go pomija
		if (++i > count) {
			return ;
		}
	} while (1);	
  
}

void delay_ms(unsigned int ms){ 
	unsigned int count=0;
	unsigned int i=0;

	#if defined(STM32F446xx) || defined(STM32F427_437xx) || defined(PP1_PP2_PLATFORM)
		count=(((double)SystemCoreClock)/7080)*ms;
	#elif defined(STM32L4R5xx) || defined(PP16_PLATFORM)
		count=(((double)SystemCoreClock)/4160)*ms;	//4160 wzięło się z doświadczalnego sprawedzenie na płycie PP16 (oznacza to, że procesor potrzebuje 4,16 tyknięcia zegara do wykonania poniższej pętli)
	#endif
	
	do{
		if (++i > count) {
			return ;
		}
	} while (1);
}
