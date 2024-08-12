	#include <stdlib.h>
	#include <string.h>
	#include "pp_math.h"
	#include "pp_pointXY_double.h"

void PPointXYdoubleConstruct(PPointXYdouble *point){
		
	point->setPoint=setPointXYdouble;
	point->compare=comparePointsXYdouble;
	point->add=addPointXYdouble;
	point->subtract=subtractPointXYdouble;
	point->clear=clearPointXYdouble;
		
}

void setPointXYdouble(PXYdouble *data, PConstParamsList *list){
	
	data->x=list->getParamValue(&list->data, 'X')/pow_pp(10, list->getParamUnit(&list->data, 'X'));
	data->y=list->getParamValue(&list->data, 'Y')/pow_pp(10, list->getParamUnit(&list->data, 'Y'));
}


void addPointXYdouble(PXYdouble *data, PXYdouble dataToAdd){
		data->x+=dataToAdd.x;
		data->y+=dataToAdd.y;

}

void subtractPointXYdouble(PXYdouble  *data, PXYdouble dataToSubstract){

		data->x-=dataToSubstract.x;
		data->y-=dataToSubstract.y;

}



_Bool comparePointsXYdouble(PXYdouble data, PXYdouble data2, double precisionX, double precisionY){
		if(fabs_pp(data.x-data2.x)<precisionX && fabs_pp(data.y-data2.y)<precisionY)return true;
		return false;
}


PXYdouble extractPointXYdoubleFromList(PConstParamsList *list){
		PXYdouble newPoint;
		newPoint.x=list->getParamValue(&list->data, 'X')/pow_pp(10, list->getParamUnit(&list->data, 'X'));
		newPoint.y=list->getParamValue(&list->data, 'Y')/pow_pp(10, list->getParamUnit(&list->data, 'Y'));
		return newPoint;

}

PXYdouble extractPointXYdoubleFromPoint(PPoint *point){
		PXYdouble newPoint;
		newPoint.x=point->getAxValue(&point->data, 'X');
		newPoint.y=point->getAxValue(&point->data, 'Y');
		return newPoint;

}

PXYdouble addPointsXYdouble(PXYdouble data, PXYdouble data2){
		PXYdouble newPoint;
		newPoint.x=data.x+data2.x;
		newPoint.y=data.y+data2.y;
		return newPoint;

}

PXYdouble subtractPointsXYdouble(PXYdouble data, PXYdouble dataToSubstract){
		PXYdouble newPoint;
		newPoint.x=data.x-dataToSubstract.x;
		newPoint.y=data.y-dataToSubstract.y;
		return newPoint;

}

void clearPointXYdouble(PXYdouble* data){
	data->x=0;
	data->y=0;
}
