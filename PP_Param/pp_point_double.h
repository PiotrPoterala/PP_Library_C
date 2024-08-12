#ifndef _PP_POINT_DOUBLE_H
	#define _PP_POINT_DOUBLE_H
	
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include <stdbool.h>
	#include "sparam.h"
	#include "pp_point.h"
	
	
		typedef struct{
			SValueDouble *axes;
			int size;
			int maxSize;
		}PAxesDoubleList;
		

		
	typedef struct{
		PAxesDoubleList data;

		_Bool (*insert)(PAxesDoubleList *data, SValueDouble* param);
		void (*clear)(PAxesDoubleList* data);
		void (*erase)(PAxesDoubleList *data, int pos, int len);
		
		SValueDouble (*getAx)(PAxesDoubleList *data, char acronim);
	
		void (*setPoint)(PAxesDoubleList *dataToSet, PAxesDoubleList *data);
		void (*setPoint2)(PAxesDoubleList *dataToSet, PAxesList *data);
		void (*setPointByValTab)(PAxesDoubleList *dataToSet, SValueDouble *valTab, int valTabSize);
		_Bool (*exacComparePoints)(PAxesDoubleList *data, PAxesDoubleList *dataToComp);
		_Bool (*comparePointWithValTab)(PAxesDoubleList *data, SValueDouble *valTab, int valTabSize);
		void (*addPoints)(PAxesDoubleList *data, PAxesDoubleList *dataToAdd);
		
		_Bool (*setAxValue)(PAxesDoubleList *data, char acronim, double val);
		void (*setAxesByZero)(PAxesDoubleList *data);

		_Bool (*exists)(PAxesDoubleList *data, char acronim);
		
	}PPointDouble;
	
	void PPointDoubleConstruct(PPointDouble *list, SValueDouble *tab, int maxSize);
	
	_Bool insertPAxesDoubleList(PAxesDoubleList *data, SValueDouble *param);
	void clearPAxesDoubleList(PAxesDoubleList* data);
	void erasePAxesDouble(PAxesDoubleList *data, int pos, int len);
	
	SValueDouble getAxDouble(PAxesDoubleList *data, char acronim);
	SValueDouble getAxDoubleFromValTab(SValueDouble *valTab, int valTabSize, char acronim);
	SValueDouble* getAxDoublePtr(PAxesDoubleList *data, char acronim);
	
	void setPointDouble(PAxesDoubleList *dataToSet, PAxesDoubleList *data);
	void setPointDouble2(PAxesDoubleList *dataToSet, PAxesList *data);
	void setPointDoubleByValTab(PAxesDoubleList *dataToSet, SValueDouble *valTab, int valTabSize);
	_Bool exacComparePointsDouble(PAxesDoubleList *data, PAxesDoubleList *dataToComp);
	_Bool exacComparePointDoubleWithValTab(PAxesDoubleList *data, SValueDouble *valTab, int valTabSize);
	_Bool comparePointDoubleWithValTab(PAxesDoubleList *data, SValueDouble *valTab, int valTabSize);
	void addPointsDouble(PAxesDoubleList *data, PAxesDoubleList *dataToAdd);
	
	_Bool setAxDoubleValue(PAxesDoubleList *data, char acronim, double val);
	void setAxesDoubleByZero(PAxesDoubleList *data);

	_Bool existsAxDouble(PAxesDoubleList *data, char acronim);
	
	#ifdef __cplusplus
}
#endif
	
#endif
