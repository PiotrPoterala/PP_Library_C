#ifndef _STM_H
	#define _STM_H

#if defined(STM32F446xx) || defined(STM32F427_437xx) || defined(STM32F427xx) || defined(PP1_PP2_PLATFORM)
	#include "stm32f4xx.h"
#elif defined(STM32L4R5xx) || defined(PP16_PLATFORM)
  #include "stm32l4r5xx.h"
#endif


#endif
