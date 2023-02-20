#ifndef _DEF_PINS_MOCK_H
	#define _DEF_PINS_MOCK_H


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


typedef struct
{
  unsigned int IDR;     
  unsigned int ODR;      
} GPIO_TypeDef;



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
