	#include <stdlib.h>
	#include <string.h>
	#include "pp_point_double.h"



void PPointDoubleConstruct(PPointDouble *list, SValueDouble *tab, int maxSize){
	
		list->data.axes=tab;
		list->data.maxSize=maxSize;
		clearPAxesDoubleList(&list->data);
	
		list->insert=insertPAxesDoubleList;
		list->clear=clearPAxesDoubleList;
		list->erase=erasePAxesDouble;
	
	
		list->getAx=getAxDouble;
	
		list->setPoint=setPointDouble;
		list->setPoint2=setPointDouble2;
		list->setPointByValTab=setPointDoubleByValTab;
		list->exacComparePoints=exacComparePointsDouble;
		list->comparePointWithValTab=comparePointDoubleWithValTab;
		list->addPoints=addPointsDouble;
		
		list->setAxValue=setAxDoubleValue;
		list->setAxesByZero=setAxesDoubleByZero;

		list->exists=existsAxDouble;
	
	
}
	
_Bool insertPAxesDoubleList(PAxesDoubleList *data, SValueDouble *param){
	
	if(data->size+1<=data->maxSize){
		data->axes[data->size]=*param;
		data->size++;
		return true;
	}
		
	return false;
}


void clearPAxesDoubleList(PAxesDoubleList *data){
			
		memset(data->axes, 0, sizeof(SValueDouble)*data->maxSize);
		data->size=0;
}

void erasePAxesDouble(PAxesDoubleList *data, int pos, int len){

	if(pos<data->size && pos>=0){
		if(len+pos>=data->size){
			
			data->size=pos;
			memset(&data->axes[data->size], 0, sizeof(SValueDouble)*(data->maxSize-pos));
		}else{
			
			memcpy(&data->axes[pos], &data->axes[pos+len], sizeof(SValueDouble)*(data->size-(pos+len)));	
			data->size-=len;
			memset(&data->axes[data->size], 0, sizeof(SValueDouble)*len);
		}
				
	}
}


	
SValueDouble getAxDouble(PAxesDoubleList *data, char acronim){
	SValueDouble value={0};
	
	for(int i=0; i<data->size; i++){
		if(data->axes[i].acronim==acronim){
			value=data->axes[i];
			break;
		}
	}
	return value;
}

SValueDouble getAxDoubleFromValTab(SValueDouble *valTab, int valTabSize, char acronim){
	SValueDouble value={0};
	
	for(int i=0; i<valTabSize; i++){
		if(valTab[i].acronim==acronim){
			value=valTab[i];
			break;
		}
	}
	return value;
}

SValueDouble* getAxDoublePtr(PAxesDoubleList *data, char acronim){
	
	for(int i=0; i<data->size; i++){
		if(data->axes[i].acronim==acronim){
			return &data->axes[i];
		}
	}
	return NULL;
}	


void setPointDouble(PAxesDoubleList *dataToSet, PAxesDoubleList *data){
	
	clearPAxesDoubleList(dataToSet);
	for(int i=0; i<data->size; i++){
		insertPAxesDoubleList(dataToSet, &data->axes[i]);
	}
	
}

void setPointDouble2(PAxesDoubleList *dataToSet, PAxesList *data){
	
	clearPAxesDoubleList(dataToSet);
	for(int i=0; i<data->size; i++){
		SValueDouble val;
		val.acronim=data->axes[i].acronim;
		val.value=(double)data->axes[i].value;
		insertPAxesDoubleList(dataToSet, &val);
	}
	
}
		
void setPointDoubleByValTab(PAxesDoubleList *dataToSet, SValueDouble *valTab, int valTabSize){

	clearPAxesDoubleList(dataToSet);
	for(int i=0; i<valTabSize; i++){
		if(valTab[i].acronim!='\0')insertPAxesDoubleList(dataToSet, &valTab[i]);
	}	
	
}
	
_Bool exacComparePointsDouble(PAxesDoubleList *data, PAxesDoubleList *dataToComp){
	
	_Bool same=true;
	SValueDouble parToComp={0};

	if(data->size==dataToComp->size){
		for(int i=0; i<data->size; i++){
			parToComp=getAxDouble(dataToComp, data->axes[i].acronim);
			if(parToComp.acronim==data->axes[i].acronim){
				if(parToComp.value!=data->axes[i].value){
						same=false;
						break;
				}
			}else{
				same=false;
				break;
			}
		}
	}else same=false;
	
	return same;
	
	
}

_Bool exacComparePointDoubleWithValTab(PAxesDoubleList *data, SValueDouble *valTab, int valTabSize){
	
	_Bool same=true;
	
	int tabSize=0;
	for(int i=0; i<valTabSize; i++){
		if(valTab[i].acronim!='\0')tabSize++;
		else break;
	}
	
	if(data->size==tabSize){
		same=comparePointDoubleWithValTab(data, valTab, valTabSize);
	}else same=false;
	
	return same;
	
	
}

_Bool comparePointDoubleWithValTab(PAxesDoubleList *data, SValueDouble *valTab, int valTabSize){
	
	_Bool same=true;
	SValueDouble parToComp={0};
	
	
		for(int i=0; i<data->size; i++){
			
			parToComp=getAxDoubleFromValTab(valTab, valTabSize, data->axes[i].acronim);
			if(parToComp.acronim==data->axes[i].acronim){
				if(parToComp.value!=data->axes[i].value){
						same=false;
						break;
				}
			}else{
				same=false;
				break;
			}
		}
	
	return same;
	
}

	
void addPointsDouble(PAxesDoubleList *data, PAxesDoubleList *dataToAdd){
		SValueDouble *parToAdd;
		for(int i=0; i<data->size; i++){
			parToAdd=getAxDoublePtr(dataToAdd, data->axes[i].acronim);
			if(parToAdd!=NULL){
				data->axes[i].value+=dataToAdd->axes[i].value;
			}
		}
	
}

	
_Bool setAxDoubleValue(PAxesDoubleList *data, char acronim, double val){
		SValueDouble *parToAdd=getAxDoublePtr(data, acronim);
		if(parToAdd!=NULL){
			parToAdd->value=val;
			return true;
		}
		return false;
}
	
void setAxesDoubleByZero(PAxesDoubleList *data){
	
		for(int i=0; i<data->size; i++){
			data->axes[i].value=0;
		}
}

_Bool existsAxDouble(PAxesDoubleList *data, char acronim){
		SValueDouble *parToAdd=getAxDoublePtr(data, acronim);
		if(parToAdd!=NULL){
			return true;
		}
		return false;
}
