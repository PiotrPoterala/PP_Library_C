#ifndef _PP_POINT_H
	#define _PP_POINT_H
	
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include <stdbool.h>
	#include "sparam.h"
	
	
		typedef struct{
			SValue *axes;
			int size;
			int maxSize;
		}PAxesList;
		

		
	typedef struct{
		PAxesList data;

		_Bool (*insert)(PAxesList *data, SValue* param);
		void (*clear)(PAxesList* data);
		void (*erase)(PAxesList *data, int pos, int len);
		
		SValue (*getAx)(PAxesList *data, char acronim);
		int (*getAxValue)(PAxesList *data, char acronim);
		
		SValue (*findAxWithLargestAbsValue)(PAxesList *data);
	
		void (*setPoint)(PAxesList *dataToSet, PAxesList *data);
		void (*setPointByValTab)(PAxesList *dataToSet, SValue *valTab, int valTabSize);
		_Bool (*exacComparePoints)(PAxesList *data, PAxesList *dataToComp);
		_Bool (*exacComparePointWithValTab)(PAxesList *data, SValue *valTab, int valTabSize);
		_Bool (*comparePointWithValTab)(PAxesList *data, SValue *valTab, int valTabSize);
		void (*addPoints)(PAxesList *data, PAxesList *dataToAdd);
		void (*subtractPoints)(PAxesList *data, PAxesList *dataToSubtract);
		
		_Bool (*setAx)(PAxesList *data, SValue ax);
		_Bool (*setAxValue)(PAxesList *data, char acronim, int val);
		void (*setAxesByZero)(PAxesList *data);

		_Bool (*exists)(PAxesList *data, char acronim);
		
	}PPoint;
	
	void PPointConstruct(PPoint *list, SValue *tab, int maxSize);
	
	_Bool insertPAxesList(PAxesList *data, SValue *param);
	void clearPAxesList(PAxesList* data);
	void erasePAxes(PAxesList *data, int pos, int len);
	
	SValue getAx(PAxesList *data, char acronim);
	int getAxValue(PAxesList *data, char acronim);
	SValue getAxFromValTab(SValue *valTab, int valTabSize, char acronim);
	SValue* getAxPtr(PAxesList *data, char acronim);
	
	SValue findAxWithLargestAbsValue(PAxesList *data);
	
	void setPoint(PAxesList *dataToSet, PAxesList *data);
	void setPointByValTab(PAxesList *dataToSet, SValue *valTab, int valTabSize);
	_Bool exacComparePoints(PAxesList *data, PAxesList *dataToComp);
	_Bool exacComparePointWithValTab(PAxesList *data, SValue *valTab, int valTabSize);
	_Bool comparePointWithValTab(PAxesList *data, SValue *valTab, int valTabSize);
	
	void addPoints(PAxesList *data, PAxesList *dataToAdd);
	void subtractPoints(PAxesList *data, PAxesList *dataToSubtract);
	
	_Bool setAx(PAxesList *data, SValue ax);
	_Bool setAxValue(PAxesList *data, char acronim, int val);
	void setAxesByZero(PAxesList *data);

	_Bool existsAx(PAxesList *data, char acronim);
	
	#ifdef __cplusplus
}
#endif
	
#endif
