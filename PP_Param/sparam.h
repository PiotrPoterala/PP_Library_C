#ifndef _SPARAM_H
	#define _SPARAM_H

	typedef struct{
		int value;
		int lowerLimit;
		int upperLimit;
		int precision;
		int unit;
		int defaultValue;
		char acronim;
		char unitStr[5];
		char *name;
	}SParam;
	
	typedef struct{
		char acronim;
		char acronimUnionParam;
	}SUnionParams;
	
	typedef struct{
		char acronim;
		int value;
	}SValue;
	
	typedef struct{
		int value;
		int unit;
		int precision;
	}SSimpleParam;
	
	typedef struct{
		char acronim;
		double value;
	}SValueDouble;
	
#endif
