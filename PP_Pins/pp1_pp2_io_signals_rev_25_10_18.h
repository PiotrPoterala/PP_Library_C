#ifndef _PP1_PP2_IO_SIGNALS_H
	#define _PP1_PP2_IO_SIGNALS_H

	#include "def_pins_stm32.h"


	#define  LED_PORT GPIOE 
	#define  LED1 PE13 
	#define  LED2 PE14 
	#define  LED3 PE15 

	#define  PORT_SPEAKER 			GPIOD 
	#define  SPEAK_STROBE 			PD12 
	#define  SPEAK_1 						PD13 
	#define  SPEAK_2 						PD14 
	#define  SPEAK_3 						PD15 
	#define  SPEAK_DATA_MASK 		0x1FFF 
	#define  SPEAK_PIN_SHIFT		13

	#define LCD_PORT GPIOE
	#define CD PE8
	#define RD PE9
	#define WR PE10
	#define CE PE11
	#define RES PE12

//karta SD
	#define PORT_SD 				GPIOA
	#define PIN_SD_CS 			PA4
	#define PIN_SD_DETECT 	PA8

	#define PORT_SD_PWR 		GPIOC
	#define PIN_SD_PWR 			PC13

	#define  mSD_DETECT				0x00000001	

	#define  PORT_LIM_STOP		GPIOA
	#define  PIN_KRAN_Xplus 	PA12 
	#define  PIN_KRAN_Xmin 		PA11 
	#define  PIN_KRAN_Yplus 	PA10 
	#define  PIN_KRAN_Ymin 		PA9 
	#define  PIN_KRAN_Zplus 	PA3 
	#define  PIN_KRAN_Zmin 		PA2 
	
	#define  PIN_LS_Xplus		Pin12 
	#define  PIN_LS_Xmin 		Pin11 
	#define  PIN_LS_Yplus 	Pin10 
	#define  PIN_LS_Ymin 		Pin9 
	#define  PIN_LS_Zplus 	Pin3 
	#define  PIN_LS_Zmin 		Pin2 

	#define kKRAN		      0x003F
	#define kKRAN_null		0x0000
	#define kKRAN_X				0x0003
	#define kKRAN_Xplus		0x0001
	#define kKRAN_Xmin		0x0002
	#define kKRAN_Y				0x000C
	#define kKRAN_Yplus		0x0004
	#define kKRAN_Ymin		0x0008
	#define kKRAN_Z				0x0030
	#define kKRAN_Zplus		0x0010
	#define kKRAN_Zmin		0x0020

	//sygnały błędów pozycji dla poszczególnych silników (sygnalizacja przeciążenia silnika)
	#define PORT_AC_SERVO_TPOS 			GPIOB
	#define PIN_AC_SERVO_TPOS_X 		PB9
	#define PIN_AC_SERVO_TPOS_Y 		PB8
	#define PIN_AC_SERVO_TPOS_Z 		PB2

	#define  mAC_SERVO_TPOS_X				0x00000001	
	#define  mAC_SERVO_TPOS_Y				0x00000002	
	#define  mAC_SERVO_TPOS_Z				0x00000004	

	#define  PORT_KLAW				GPIOC
	#define  KLAW_WIERSZE 		0xFFF8 
	#define  KLAW_KOLUMNA_1 	PC3
	#define  KLAW_KOLUMNA_2 	PC4
	#define  KLAW_KOLUMNA_3 	PC5
	#define  KLAW_KOLUMNA_4 	PC6
	#define  KLAW_KOLUMNA_5 	PC7
	#define  KLAW_KOLUMNA_6 	PC8


	#define NZPA_GEN	PD3

	#define  PORT_SYG_PRACY		GPIOB
	#define  wejOWE 					PB0			//OWE=1, gdy Okresowe Wycofanie lub generator wyłączone, OWE=sygnał_prostokątny, gdy Okresowe Wycofanie i generator załączone 
	#define  wejZSA 					PB1			//ZSA=0 jeżeli zdetekowano Zespolony Sygnał Awarii (temperatura radiatora, temperatura nafty, poziom nafty lub pożar) 
	#define  wejSYGP 					PB5			//sygP=0 jeżeli zdetekowano przypalenie
	#define  wejCplus 				PB6
	#define  wejCmin 					PB7

	#define  nSYGP 			0x00000001	
	#define  nZSA 			0x00000002	
	#define  nOWE 			0x00000004	
	#define  nZSAP 			0x00000008
	#define  nZWARCIE 	0x00000010	
	
	#define ZWARCIE 			((PORT_SYG_PRACY->IDR & wejCplus))
	#define BRAK_ZWARCIA 	(!(PORT_SYG_PRACY->IDR & wejCplus))
	#define PRACA 				(!(PORT_SYG_PRACY->IDR & wejCmin))
	#define BRAK_PRACY 		((PORT_SYG_PRACY->IDR & wejCmin))

#endif
