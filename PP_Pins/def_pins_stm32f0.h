#ifndef _DEF_PINS_H
	#define _DEF_PINS_H

#include "stm32f0xx.h"
typedef enum
{ B_RESET = 0,
  B_SET=1
}BitStatus;

	#define Pin0     	 (0u) 
	#define Pin1       (1u)
	#define Pin2       (2u)
	#define Pin3       (3u)
	#define Pin4       (4u)
	#define Pin5       (5u)
	#define Pin6       (6u)
	#define Pin7       (7u)
	#define Pin8       (8u)
	#define Pin9       (9u)
	#define Pin10      (10u)
	#define Pin11      (11u)
	#define Pin12      (12u)
	#define Pin13      (13u)
	#define Pin14      (14u)
	#define Pin15      (15u)

	#define PORT_A		0
	#define PORT_B		1
	#define PORT_C		2
	#define PORT_D		3
	#define PORT_E		4

	#define Pin0_Mask     	(1u<<0)  
	#define Pin1_Mask       (1u<<1)
	#define Pin2_Mask       (1u<<2)
	#define Pin3_Mask       (1u<<3)
	#define Pin4_Mask       (1u<<4)
	#define Pin5_Mask       (1u<<5)
	#define Pin6_Mask       (1u<<6)
	#define Pin7_Mask       (1u<<7)
	#define Pin8_Mask       (1u<<8)
	#define Pin9_Mask       (1u<<9)
	#define Pin10_Mask      (1u<<10)
	#define Pin11_Mask      (1u<<11)
	#define Pin12_Mask      (1u<<12)
	#define Pin13_Mask      (1u<<13)
	#define Pin14_Mask      (1u<<14)
	#define Pin15_Mask      (1u<<15)
	#define Pin16_Mask      (1u<<16)

	#define PA0     	(1u<<0)  
	#define PA1      	(1u<<1u)
	#define PA2       (1u<<2)
	#define PA3       (1u<<3)
	#define PA4       (1u<<4)
	#define PA5       (1u<<5)
	#define PA6       (1u<<6)
	#define PA7       (1u<<7)
	#define PA8       (1u<<8)
	#define PA9       (1u<<9)
	#define PA10      (1u<<10)
	#define PA11      (1u<<11)
	#define PA12      (1u<<12)
	#define PA13      (1u<<13)
	#define PA14      (1u<<14)
	#define PA15      (1u<<15)

	#define PB0     	(1u<<0)  
	#define PB1       (1u<<1u)
	#define PB2       (1u<<2)
	#define PB3       (1u<<3)
	#define PB4       (1u<<4)
	#define PB5       (1u<<5)
	#define PB6       (1u<<6)
	#define PB7       (1u<<7)
	#define PB8       (1u<<8)
	#define PB9       (1u<<9)
	#define PB10      (1u<<10)
	#define PB11      (1u<<11)
	#define PB12      (1u<<12)
	#define PB13      (1u<<13)
	#define PB14      (1u<<14)
	#define PB15      (1u<<15)

	#define PC0     	(1u<<0)  
	#define PC1       (1u<<1)
	#define PC2       (1u<<2)
	#define PC3       (1u<<3)
	#define PC4       (1u<<4)
	#define PC5       (1u<<5)
	#define PC6       (1u<<6)
	#define PC7       (1u<<7)
	#define PC8       (1u<<8)
	#define PC9       (1u<<9)
	#define PC10      (1u<<10)
	#define PC11      (1u<<11)
	#define PC12      (1u<<12)
	#define PC13      (1u<<13)
	#define PC14      (1u<<14)
	#define PC15      (1u<<15)

	#define PD0     	(1u<<0)  
	#define PD1       (1u<<1)
	#define PD2       (1u<<2)
	#define PD3       (1u<<3)
	#define PD4       (1u<<4)
	#define PD5       (1u<<5)
	#define PD6       (1u<<6)
	#define PD7       (1u<<7)
	#define PD8       (1u<<8)
	#define PD9       (1u<<9)
	#define PD10      (1u<<10)
	#define PD11      (1u<<11)
	#define PD12      (1u<<12)
	#define PD13      (1u<<13)
	#define PD14      (1u<<14)
	#define PD15      (1u<<15)

	#define PE0     	(1u<<0)  
	#define PE1       (1u<<1)
	#define PE2       (1u<<2)
	#define PE3       (1u<<3)
	#define PE4       (1u<<4)
	#define PE5       (1u<<5)
	#define PE6       (1u<<6)
	#define PE7       (1u<<7)
	#define PE8       (1u<<8)
	#define PE9       (1u<<9)
	#define PE10      (1u<<10)
	#define PE11     	(1u<<11)
	#define PE12      (1u<<12)
	#define PE13      (1u<<13)
	#define PE14      (1u<<14)
	#define PE15      (1u<<15)

//mode
	#define IO_IN 		((uint32_t)0x0)			//wejśie
	#define IO_OUT 		((uint32_t)0x1)			//wyjśie
	#define IO_ALT		((uint32_t)0x2)			//funkcja alternatywna
	#define IO_AN			((uint32_t)0x3)			//analog

//output speed
	#define IO_OUT_LS 		((uint32_t)0x0)
	#define IO_OUT_MS 		((uint32_t)0x1)
	#define IO_OUT_HS 		((uint32_t)0x3)

//input pull-up/pull-down
	#define IO_IN_NPUD 	((uint32_t)0x0)
	#define IO_IN_PU 		((uint32_t)0x1)
	#define IO_IN_PD 		((uint32_t)0x2)


	#define PIN_TOG(PORT, PIN) (PORT->ODR^=PIN)
	#define PIN_SET(PORT, PIN) (PORT->BSRR=PIN)
	#define PIN_CLR(PORT, PIN) (PORT->BSRR=(PIN<<16))

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
