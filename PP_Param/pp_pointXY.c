	#include <stdlib.h>
	#include <string.h>
	#include "pp_pointXY.h"

void PPointXYConstruct(PPointXY *point){
		
	point->setPoint=setPointXY;
	point->compare=comparePointsXY;
	point->add=addPointXY;
	point->subtract=subtractPointXY;
	point->clear=clearPointXY;
		
}

void setPointXY(PXY *data, PConstParamsList *list){
	
	data->x=list->getParamValue(&list->data, 'X');
	data->y=list->getParamValue(&list->data, 'Y');
}


void addPointXY(PXY *data, PXY dataToAdd){
		data->x+=dataToAdd.x;
		data->y+=dataToAdd.y;

}

void subtractPointXY(PXY *data, PXY dataToSubstract){

		data->x-=dataToSubstract.x;
		data->y-=dataToSubstract.y;

}



_Bool comparePointsXY(PXY data, PXY data2){
		if(data.x==data2.x && data.y==data2.y)return true;
		return false;
}


PXY extractPointXYfromList(PConstParamsList *list){
		PXY newPoint;
		newPoint.x=list->getParamValue(&list->data, 'X');
		newPoint.y=list->getParamValue(&list->data, 'Y');
		return newPoint;

}

PXY extractPointXYfromPoint(PPoint *point){
		PXY newPoint;
		newPoint.x=point->getAxValue(&point->data, 'X');
		newPoint.y=point->getAxValue(&point->data, 'Y');
		return newPoint;

}

PXY addPointsXY(PXY data, PXY data2){
		PXY newPoint;
		newPoint.x=data.x+data2.x;
		newPoint.y=data.y+data2.y;
		return newPoint;

}

PXY subtractPointsXY(PXY data, PXY dataToSubstract){
		PXY newPoint;
		newPoint.x=data.x-dataToSubstract.x;
		newPoint.y=data.y-dataToSubstract.y;
		return newPoint;

}

void clearPointXY(PXY* data){
	data->x=0;
	data->y=0;
}
