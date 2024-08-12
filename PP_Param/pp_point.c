	#include <stdlib.h>
	#include <string.h>
	#include "pp_point.h"



void PPointConstruct(PPoint *list, SValue *tab, int maxSize){
	
		list->data.axes=tab;
		list->data.maxSize=maxSize;
		clearPAxesList(&list->data);
	
		list->insert=insertPAxesList;
		list->clear=clearPAxesList;
		list->erase=erasePAxes;
	
		list->getAx=getAx;
		list->getAxValue=getAxValue;
	
		list->findAxWithLargestAbsValue=findAxWithLargestAbsValue;
	
		list->setPoint=setPoint;
		list->setPointByValTab=setPointByValTab;
		list->exacComparePoints=exacComparePoints;
		list->exacComparePointWithValTab=exacComparePointWithValTab;
		list->comparePointWithValTab=comparePointWithValTab;
		list->addPoints=addPoints;
		list->subtractPoints=subtractPoints;
		
		list->setAx=setAx;
		list->setAxValue=setAxValue;
		list->setAxesByZero=setAxesByZero;

		list->exists=existsAx;
	
	
}
	
_Bool insertPAxesList(PAxesList *data, SValue *param){
	
	if(data->size+1<=data->maxSize){
		data->axes[data->size]=*param;
		data->size++;
		return true;
	}
		
	return false;
}


void clearPAxesList(PAxesList *data){
			
		memset(data->axes, 0, sizeof(SValue)*data->maxSize);
		data->size=0;
}

void erasePAxes(PAxesList *data, int pos, int len){

	if(pos<data->size && pos>=0){
		if(len+pos>=data->size){
			
			data->size=pos;
			memset(&data->axes[data->size], 0, sizeof(SValue)*(data->maxSize-pos));
		}else{
			
			memcpy(&data->axes[pos], &data->axes[pos+len], sizeof(SValue)*(data->size-(pos+len)));	
			data->size-=len;
			memset(&data->axes[data->size], 0, sizeof(SValue)*len);
		}
				
	}
}


	
SValue getAx(PAxesList *data, char acronim){
	SValue value={0};
	
	for(int i=0; i<data->size; i++){
		if(data->axes[i].acronim==acronim){
			value=data->axes[i];
			break;
		}
	}
	return value;
}

int getAxValue(PAxesList *data, char acronim){
	int value=0;
	
	for(int i=0; i<data->size; i++){
		if(data->axes[i].acronim==acronim){
			value=data->axes[i].value;
			break;
		}
	}
	return value;
}

SValue getAxFromValTab(SValue *valTab, int valTabSize, char acronim){
	SValue value={0};
	
	for(int i=0; i<valTabSize; i++){
		if(valTab[i].acronim==acronim){
			value=valTab[i];
			break;
		}
	}
	return value;
}

SValue* getAxPtr(PAxesList *data, char acronim){
	
	for(int i=0; i<data->size; i++){
		if(data->axes[i].acronim==acronim){
			return &data->axes[i];
		}
	}
	return NULL;
}	


SValue findAxWithLargestAbsValue(PAxesList *data){
	SValue findValue=data->axes[0];
	findValue.value=abs(findValue.value);
	
	for(int i=0; i<data->size; i++){
		if(abs(data->axes[i].value)>abs(findValue.value)){
			findValue=data->axes[i];
		}
	}
	return findValue;
}


void setPoint(PAxesList *dataToSet, PAxesList *data){
	
	if(dataToSet!=NULL && data!=NULL){
		clearPAxesList(dataToSet);
		for(int i=0; i<data->size; i++){
			insertPAxesList(dataToSet, &data->axes[i]);
		}
	}
}
		
void setPointByValTab(PAxesList *dataToSet, SValue *valTab, int valTabSize){

	clearPAxesList(dataToSet);
	for(int i=0; i<valTabSize; i++){
		if(valTab[i].acronim!='\0')insertPAxesList(dataToSet, &valTab[i]);
	}	
	
}
	
_Bool exacComparePoints(PAxesList *data, PAxesList *dataToComp){
	
	_Bool same=true;
	SValue parToComp={0};

	if(data->size==dataToComp->size){
		for(int i=0; i<data->size; i++){
			parToComp=getAx(dataToComp, data->axes[i].acronim);
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

_Bool exacComparePointWithValTab(PAxesList *data, SValue *valTab, int valTabSize){
	
	_Bool same=true;
	
	int tabSize=0;
	for(int i=0; i<valTabSize; i++){
		if(valTab[i].acronim!='\0')tabSize++;
		else break;
	}
	
	if(data->size==tabSize){
		same=comparePointWithValTab(data, valTab, valTabSize);
	}else same=false;
	
	return same;
	
	
}

_Bool comparePointWithValTab(PAxesList *data, SValue *valTab, int valTabSize){
	
	_Bool same=true;
	SValue parToComp={0};
	
	
		for(int i=0; i<data->size; i++){
			
			parToComp=getAxFromValTab(valTab, valTabSize, data->axes[i].acronim);
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

	
void addPoints(PAxesList *data, PAxesList *dataToAdd){
		SValue *parToAdd;
		for(int i=0; i<data->size; i++){
			parToAdd=getAxPtr(dataToAdd, data->axes[i].acronim);
			if(parToAdd!=NULL){
				data->axes[i].value+=dataToAdd->axes[i].value;
			}
		}
	
}

void subtractPoints(PAxesList *data, PAxesList *dataToSubtract){
		SValue *parToAdd;
		for(int i=0; i<data->size; i++){
			parToAdd=getAxPtr(dataToSubtract, data->axes[i].acronim);
			if(parToAdd!=NULL){
				data->axes[i].value-=dataToSubtract->axes[i].value;
			}
		}
	
}

_Bool setAx(PAxesList *data, SValue ax){
		SValue *parToAdd=getAxPtr(data, ax.acronim);
		if(parToAdd!=NULL){
			parToAdd->value=ax.value;
			return true;
		}
		return false;
}
	
_Bool setAxValue(PAxesList *data, char acronim, int val){
		SValue *parToAdd=getAxPtr(data, acronim);
		if(parToAdd!=NULL){
			parToAdd->value=val;
			return true;
		}
		return false;
}
	
void setAxesByZero(PAxesList *data){
	
		for(int i=0; i<data->size; i++){
			data->axes[i].value=0;
		}
}

_Bool existsAx(PAxesList *data, char acronim){
		SValue *parToAdd=getAxPtr(data, acronim);
		if(parToAdd!=NULL){
			return true;
		}
		return false;
}
