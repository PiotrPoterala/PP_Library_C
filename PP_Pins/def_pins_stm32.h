#ifndef _DEF_PINS_H
	#define _DEF_PINS_H

#if defined(STM32F446xx) || defined(STM32F427_437xx) || defined(PP1_PP2_PLATFORM)
	#include "def_pins_stm32f4.h"
#elif defined(STM32L4R5xx) || defined(PP16_PLATFORM)
  #include "def_pins_stm32l4.h"
#endif

typedef enum{ 
		B_LOW=0,
		B_HIGH
}inputStatus;

typedef struct{
	GPIO_TypeDef* port;
	int pin;
}uPin;

typedef struct{
	GPIO_TypeDef* port;
	int clrMask;
	int mask;
}uPortMask;

#endif
