#ifndef _PP_MATH_H
	#define _PP_MATH_H
	
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include "math.h"
	
	int deg2sec(double angle);
	double sec2deg(int angle);
	
	int pow_pp(int base, unsigned int exponent);	//tylko to w przerwaniach
	double fpow_pp(double base, int exponent);
	int abs_pp(int data);	//tylko to w przerwaniach
	double fabs_pp(double data);
	int mulBy10_pp(int value, int exponent);
	
	int fs_mulBy10_pp(int value, int exponent);
	
	int trim_pp(int data, int upperLimit, int lowerLimit);
	int round_pp(int data, int precision);
	int trimAcc_pp(int data, int upperLimit, int lowerLimit, int precision);
	
		#ifdef __cplusplus
}
#endif
	
#endif
