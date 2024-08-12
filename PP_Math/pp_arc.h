#ifndef _PP_ARC_H
	#define _PP_ARC_H
	
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include "pp_math.h"
	#include "pp_pointXY.h"
//	#include "pp_pointXY_double.h"
	
		typedef enum
	{ CLOCKWISE = 0,
		COUNTERCLOCKWISE
	}defTurnCircle;
	
	
	double arcImplicitFunction(double X, double Y, double R, unsigned int unit);
	
	unsigned int calculateNrOfStepCircle(PXY circleEndPoint, PXY circleCenterPoint, PXY circleStartPoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, defTurnCircle turnCircle);
	PXY getRealEndOfArc(PXY circleEndPoint, PXY circleCenterPoint, PXY circleStartPoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, defTurnCircle turnCircle);
	PXY getNextStepPointOnArc(PXY pointTest, unsigned int radius, unsigned int precisionX, unsigned int precisionY, unsigned int unit, defTurnCircle turnCircle);
	
//	double arcImplicitFunction(double X1, double Y1, double R2);
//	unsigned int calculateNrOfStepCircle(PXYdouble circleEndPoint, PXYdouble circleCenterPoint, PXYdouble circleStartPoint, double precisionX, double precisionY, defTurnCircle turnCircle);
//	PXYdouble getRealEndOfArc(PXYdouble circleEndPoint, PXYdouble circleCenterPoint, PXYdouble circleStartPoint, double precisionX, double precisionY, defTurnCircle turnCircle);
//	void getNextStepPointOnArc(PXYdouble *pointTest, double R2, double precisionX, double precisionY, defTurnCircle turnCircle);
	
	
		#ifdef __cplusplus
}
#endif
	
#endif
