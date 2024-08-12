#ifndef _PP1_PP2_IO_SIGNALS_H
	#define _PP1_PP2_IO_SIGNALS_H

#include "def_pins_stm32.h"


	#define  LED_PORT GPIOA 
	#define  LED1 PA13 
	#define  LED2 PA14 

	#define  LED_ADD_PORT GPIOE 
	#define  LED3 PE13 


	#define LCD_PORT GPIOE
	#define CD PE8
	#define RD PE9
	#define WR PE10
	#define CE PE11
	#define RES PE12

//UART
	#define UART_COMM_NO 		3

//USBB
	#define UART_USBB_NO 		4

//WIFI
	#define UART_WIFI_NO 		5
	#define PORT_WIFI 			GPIOE
	#define PIN_WIFI_EN 		PE15
	
//UART select	

	#define PORT_UART_SEL 		GPIOA
	#define PIN_UART_SEL 			PA15

//karta SD
	#define SPI_SD 					SPI1
	#define PORT_SD 				GPIOA
	#define PIN_SD_CS 			PA4
	#define PIN_SD_DETECT 	PA8


	#define  PORT_LIM_STOP		GPIOA
	#define  PIN_LS_Xplus 		Pin12 
	#define  PIN_LS_Xmin 			Pin11 
	#define  PIN_LS_Yplus 		Pin10 
	#define  PIN_LS_Ymin 			Pin9 
	#define  PIN_LS_Zplus 		Pin3 
	#define  PIN_LS_Zmin 			Pin2 
	

	//sygnały błędów pozycji dla poszczególnych silników (sygnalizacja przeciążenia silnika)
	#define PORT_AC_SERVO_TPOS_X 		GPIOB
	#define PIN_AC_SERVO_TPOS_X 		Pin9
	#define PORT_AC_SERVO_TPOS_Y 		GPIOB
	#define PIN_AC_SERVO_TPOS_Y 		Pin5
	#define PORT_AC_SERVO_TPOS_Z 		GPIOB
	#define PIN_AC_SERVO_TPOS_Z 		Pin4
	
	#define NZPA_GEN	PD3


	#define  PORT_FUN_SYG		GPIOB
	#define  PIN_OWE 					Pin0			//OWE=1, gdy Okresowe Wycofanie lub generator wyłączone, OWE=sygnał_prostokątny, gdy Okresowe Wycofanie i generator załączone 
	#define  PIN_ZSA 					Pin1			//ZSA=0 jeżeli zdetekowano Zespolony Sygnał Awarii (temperatura radiatora, temperatura nafty, poziom nafty lub pożar) 

	#define  PORT_SYG_PRACY		GPIOB
	#define  PIN_Cplus 				Pin6
	#define  PIN_Cmin					Pin7
	

	#define ZWARCIE 			((PORT_SYG_PRACY->IDR & (1<<PIN_Cplus)))
	#define BRAK_ZWARCIA 	(!(PORT_SYG_PRACY->IDR & (1<<PIN_Cplus)))
	#define PRACA 				(!(PORT_SYG_PRACY->IDR & (1<<PIN_Cmin)))
	#define BRAK_PRACY 		((PORT_SYG_PRACY->IDR & (1<<PIN_Cmin)))


//motors
	#define  	M1_PORT 			GPIOD	
	#define  	M1_PH1_DIR 			Pin1		
	#define  	M1_PH2_CLK 			Pin0		
	#define  	M2_PORT 			GPIOD	
	#define  	M2_PH1_DIR 			Pin5		
	#define  	M2_PH2_CLK 			Pin4		
	#define  	M3_PORT 			GPIOD	
	#define  	M3_PH1_DIR 			Pin7		
	#define  	M3_PH2_CLK 			Pin6		
	#define  	M4_PORT 			GPIOD	
	#define  	M4_PH1_DIR 			Pin9		
	#define  	M4_PH2_CLK 			Pin8		
	
//keyboard
	#define PORT_DMUX 		GPIOC
	#define PIN_DMUX1 		Pin0
	#define PIN_DMUX2 		Pin1
	#define PIN_DMUX3 		Pin2
	
	#define PORT_KBRIN 		GPIOC
	#define PIN_KBRIN1 		Pin3
	#define PIN_KBRIN2 		Pin4
	#define PIN_KBRIN3 		Pin5
	#define PIN_KBRIN4 		Pin6
	#define PIN_KBRIN5 		Pin7
	#define PIN_KBRIN6 		Pin8




	enum{
		mAC_SERVO_TPOS_X=0,
		mAC_SERVO_TPOS_Y,
		mAC_SERVO_TPOS_Z
	};
	
#endif
