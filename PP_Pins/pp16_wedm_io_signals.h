#ifndef _PP16_IO_SIGNALS_H
	#define _PP16_IO_SIGNALS_H

	#include "def_pins_stm32.h"
	
	#define  LED_PORT GPIOA 
	#define  LED1 PA13 
	#define  LED2 PA14 

//wyświetlacz TFT
	#define PORT_TFT 		GPIOA
	#define PIN_TFT_PD 	PA4
	
//UART
	#define UART_COMM_NO 		4
	
//USBB
	#define UART_USBB_NO 		1
	
//WIFI
	#define UART_WIFI_NO 		3
	#define PORT_WIFI 			GPIOA
	#define PIN_WIFI_EN 		PA6
	
//USB
	#define PORT_USBA_EN 			GPIOA
	#define PIN_USBA_EN 			PA15
	
	#define PORT_USBA_FAULT 	GPIOC
	#define PIN_USBA_FAULT 		PC12
	

	#define  PORT_LIM_STOP		GPIOC
	#define  PIN_LS_Xplus 		Pin6 
	#define  PIN_LS_Xmin 			Pin7 
	#define  PIN_LS_Yplus 		Pin8 
	#define  PIN_LS_Ymin 			Pin9 
	#define  PIN_LS_Zplus 		Pin10 
	#define  PIN_LS_Zmin 			Pin11 
	

	//sygnały błędów pozycji dla poszczególnych silników (sygnalizacja przeciążenia silnika)
	#define PORT_AC_SERVO_TPOS_X 		GPIOB
	#define PIN_AC_SERVO_TPOS_X 		Pin6
	
	#define PORT_AC_SERVO_TPOS_Y 		GPIOB
	#define PIN_AC_SERVO_TPOS_Y 		Pin7
	
	#define PORT_AC_SERVO_TPOS_Z 		GPIOB
	#define PIN_AC_SERVO_TPOS_Z 		Pin8
	
	#define NZPA_GEN	PB5


	#define  PORT_FUN_SYG			GPIOB
	#define  PIN_OWE 					Pin3			//OWE=1, gdy Okresowe Wycofanie lub generator wyłączone, OWE=sygnał_prostokątny, gdy Okresowe Wycofanie i generator załączone 
	#define  PIN_ZSA 					Pin4			//ZSA=0 jeżeli zdetekowano Zespolony Sygnał Awarii (temperatura radiatora, temperatura nafty, poziom nafty lub pożar) 

	#define  PORT_SYG_PRACY		GPIOC
	#define  PIN_Cplus 				Pin1
	#define  PIN_Cmin					Pin0
	

	#define ZWARCIE 			((PORT_SYG_PRACY->IDR & (1<<PIN_Cplus)))
	#define BRAK_ZWARCIA 	(!(PORT_SYG_PRACY->IDR & (1<<PIN_Cplus)))
	#define PRACA 				(!(PORT_SYG_PRACY->IDR & (1<<PIN_Cmin)))
	#define BRAK_PRACY 		((PORT_SYG_PRACY->IDR & (1<<PIN_Cmin)))
	
	//motors
	#define  	M1_PORT 				GPIOB		
	#define  	M1_PH1_DIR 			Pin15		
	#define  	M1_PH2_CLK 			Pin14	
	#define  	M1_ENABLE_PORT 		GPIOB		
	#define  	M1_ENABLE 				Pin0
	#define  	M1_SEL_CUR_PORT 	GPIOF		
	#define  	M1_SEL_CUR 				Pin5	
	
	#define  	M1_I_PORT 			GPIOE
	#define  	M1_I0_1 				Pin11
	#define  	M1_I1_1 				Pin10
	#define  	M1_I2_1 				Pin9
	#define  	M1_I3_1 				Pin8
	#define  	M1_I0_2 				Pin12
	#define  	M1_I1_2 				Pin13
	#define  	M1_I2_2 				Pin14
	#define  	M1_I3_2 				Pin15
	
	#define  	M2_PORT 			GPIOB		
	#define  	M2_PH1_DIR 			Pin13		
	#define  	M2_PH2_CLK 			Pin12	
	#define  	M2_ENABLE_PORT 		GPIOB		
	#define  	M2_ENABLE 				Pin0
	#define  	M2_SEL_CUR_PORT 	GPIOF		
	#define  	M2_SEL_CUR 				Pin4	
	
	#define  	M2_I_PORT 			GPIOD
	#define  	M2_I0_1 				Pin11
	#define  	M2_I1_1 				Pin10
	#define  	M2_I2_1 				Pin9
	#define  	M2_I3_1 				Pin8
	#define  	M2_I0_2 				Pin12
	#define  	M2_I1_2 				Pin13
	#define  	M2_I2_2 				Pin14
	#define  	M2_I3_2 				Pin15
	
	#define  	M3_PORT 				GPIOB		
	#define  	M3_PH1_DIR 			Pin11		
	#define  	M3_PH2_CLK 			Pin10	
	#define  	M3_ENABLE_PORT 		GPIOB		
	#define  	M3_ENABLE 				Pin0
	#define  	M3_SEL_CUR_PORT 	GPIOF		
	#define  	M3_SEL_CUR 				Pin3	
	
	#define  	M3_I_PORT 			GPIOG
	#define  	M3_I0_1 				Pin3
	#define  	M3_I1_1 				Pin2
	#define  	M3_I2_1 				Pin1
	#define  	M3_I3_1 				Pin0
	#define  	M3_I0_2 				Pin4
	#define  	M3_I1_2 				Pin5
	#define  	M3_I2_2 				Pin6
	#define  	M3_I3_2 				Pin7
	
	#define  	M4_PORT 				GPIOF		
	#define  	M4_PH1_DIR 			Pin14		
	#define  	M4_PH2_CLK 			Pin13	
	#define  	M4_ENABLE_PORT 		GPIOA		
	#define  	M4_ENABLE 				Pin7	
	#define  	M4_SEL_CUR_PORT 	GPIOF		
	#define  	M4_SEL_CUR 				Pin2	
	
	#define  	M4_I_PORT 			GPIOD
	#define  	M4_I0_1 				Pin3
	#define  	M4_I1_1 				Pin2
	#define  	M4_I2_1 				Pin1
	#define  	M4_I3_1 				Pin0
	#define  	M4_I0_2 				Pin4
	#define  	M4_I1_2 				Pin5
	#define  	M4_I2_2 				Pin6
	#define  	M4_I3_2 				Pin7
	
	#define  	M5_PORT_PH1 		GPIOF		
	#define  	M5_PORT_PH2 		GPIOB		
	#define  	M5_PH1_DIR 			Pin11		
	#define  	M5_PH2_CLK 			Pin10	
	#define  	M5_ENABLE_PORT 		GPIOA		
	#define  	M5_ENABLE 				Pin7	
	#define  	M5_SEL_CUR_PORT 	GPIOF		
	#define  	M5_SEL_CUR 				Pin1	
	
	#define  	M5_I_PORT 			GPIOG
	#define  	M5_I0_1 				Pin11
	#define  	M5_I1_1 				Pin10
	#define  	M5_I2_1 				Pin9
	#define  	M5_I3_1 				Pin8
	#define  	M5_I0_2 				Pin12
	#define  	M5_I1_2 				Pin13
	#define  	M5_I2_2 				Pin14
	#define  	M5_I3_2 				Pin15
	
	//keyboard
	#define PORT_DMUX 		GPIOE
	#define PIN_DMUX1 		Pin0
	#define PIN_DMUX2 		Pin1
	#define PIN_DMUX3 		Pin2
	
	#define PORT_KBRIN 		GPIOE
	#define PIN_KBRIN1 		Pin4
	#define PIN_KBRIN2 		Pin5
	#define PIN_KBRIN3 		Pin6
	#define PIN_KBRIN4 		Pin7
	
	enum{
		mAC_SERVO_TPOS_X=0,
		mAC_SERVO_TPOS_Y,
		mAC_SERVO_TPOS_Z,
		mUSBA_FAULT
	};
	
	#define  PORT_WIRE_HEAD		GPIOB
	#define  PIN_T1_ZDR 			Pin4			
	#define  PIN_T2 					Pin5			
	#define  PIN_T3 					Pin6
	
	#define  PORT_DC_PWM 			GPIOB
	#define  PIN_DC1_PWM 			Pin2
	#define  PIN_DC2_PWM 			Pin1
	
	#define  PORT_DC_DIR 			GPIOF
	#define  PIN_DC1_DIR 			Pin0
	#define  PIN_DC2_DIR 			Pin0
	
	enum{
		mT1_ZDR=0,
		mT2,
		mT3
	};
	
#endif
