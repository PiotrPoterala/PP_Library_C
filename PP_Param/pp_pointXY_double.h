#ifndef _PP_POINTXY_DOUBLE_H
	#define _PP_POINTXY_DOUBLE_H
	
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include <stdbool.h>
	#include "pp_paramlist.h"
	#include "pp_point.h"
	
		typedef struct{
			double x;
			double y;
		}PXYdouble;
		

		
	typedef struct{
		PXYdouble data;

		void (*setPoint)(PXYdouble *data, PConstParamsList *list);
		void (*clear)(PXYdouble* data);
		void (*add)(PXYdouble *data, PXYdouble data2);
		void (*subtract)(PXYdouble *data, PXYdouble data2);
		_Bool (*compare)(PXYdouble data, PXYdouble data2, double precisionX, double precisionY);
	}PPointXYdouble;

	void PPointXYdoubleConstruct(PPointXYdouble *point);
	
	void setPointXYdouble(PXYdouble *data, PConstParamsList *list);
	
	void addPointXYdouble(PXYdouble *data, PXYdouble dataToAdd);
	void subtractPointXYdouble(PXYdouble *data, PXYdouble dataToSubstract);
	
	_Bool comparePointsXYdouble(PXYdouble data, PXYdouble data2, double precisionX, double precisionY);
	PXYdouble extractPointXYdoubleFromList(PConstParamsList *list);
	PXYdouble extractPointXYdoubleFromPoint(PPoint *point);
	PXYdouble addPointsXYdouble(PXYdouble data, PXYdouble data2);
	PXYdouble subtractPointsXYdouble(PXYdouble data, PXYdouble dataToSubstract);
	void clearPointXYdouble(PXYdouble* data);
	
	
	#ifdef __cplusplus
}
#endif
	
#endif
