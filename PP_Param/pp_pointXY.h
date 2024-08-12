#ifndef _PP_POINTXY_H
	#define _PP_POINTXY_H
	
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include <stdbool.h>
	#include "pp_paramlist.h"
	#include "pp_point.h"
	
		typedef struct{
			int x;
			int y;
		}PXY;
		

		
	typedef struct{
		PXY data;

		void (*setPoint)(PXY *data, PConstParamsList *list);
		void (*clear)(PXY* data);
		void (*add)(PXY *data, PXY data2);
		void (*subtract)(PXY *data, PXY data2);
		_Bool (*compare)(PXY data, PXY data2);
	}PPointXY;

	void PPointXYConstruct(PPointXY *point);
	
	void setPointXY(PXY *data, PConstParamsList *list);
	
	void addPointXY(PXY *data, PXY dataToAdd);
	void subtractPointXY(PXY *data, PXY dataToSubstract);
	
	_Bool comparePointsXY(PXY data, PXY data2);
	PXY extractPointXYfromList(PConstParamsList *list);
	PXY extractPointXYfromPoint(PPoint *point);
	PXY addPointsXY(PXY data, PXY data2);
	PXY subtractPointsXY(PXY data, PXY dataToSubstract);
	void clearPointXY(PXY* data);
	
	
	#ifdef __cplusplus
}
#endif
	
#endif
