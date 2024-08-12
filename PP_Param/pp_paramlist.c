#include <stdio.h>
#include <string.h>
#include "pp_math.h"
#include "pp_paramlist.h"
#include "pstring.h"

void PConstParamsListConstruct(PConstParamsList *list, SParam *tab, int maxSize){

		list->data.par=tab;
		list->data.maxSize=maxSize;
		clearPParamsList(&list->data);
	
		list->insert=insertPParamsList;
		list->clear=clearPParamsList;
	
	
		list->data.maxSizeUnionParamsList=MAX_UNION_PARAMS;
		clearUnionParams(&list->data);
	
		list->insertUnionParam=insertUnionParam;
		list->clearUnionParams=clearUnionParams;
	
		list->copyListOfParams=copyListOfParams;
			
		list->getParam=getParam;
		list->getParamPtr=getParamPtr;
	
		list->exists=existsParam;

		list->getParamValue=getParamValue;
		list->getParamUpperLimit=getParamUpperLimit;
		list->getParamLowerLimit=getParamLowerLimit;
		list->getParamUnit=getParamUnit;
		list->getParamPrecision=getParamPrecision;
	
		list->getParamRealValue=getParamRealValue;

		list->getParamsAcronims=getParamsAcronims;
		list->getStringWithParam=getStringWithParam;
		list->getStringWithParamDesc=getStringWithParamDesc;
		list->getStringWithParams=getStringWithParams;

		list->getParamValues=getParamValues;

		list->setParam=setParam;
		list->setParamValue=setParamValue;
		list->setParamRealValue=setParamRealValue;
		list->setParamLowerLimit=setParamLowerLimit;
		list->setParamUpperLimit=setParamUpperLimit;
		list->setParamDefaultValue=setParamDefaultValue;
		list->setParamPrecision=setParamPrecision;
		list->setParamRealLowerLimit=setParamRealLowerLimit;
		list->setParamName=setParamName;
		
		list->setParamsValueByDefaultValue=setParamsValueByDefaultValue;
		list->setParamsValue=setParamsValue;
		list->setParamsValueByCopy=setParamsValueByCopy;
		
		list->setParamsDefaultValue=setParamsDefaultValue;
		list->setParamsRealLowerLimit=setParamsRealLowerLimit;

		list->setParamsValuesByValTab=setParamsValuesByValTab;
		list->areParamsInString=areParamsInString;
		list->setParamsBasedString=setParamsBasedString;

		list->exacCompareParamsValue=exacCompareParamsValue;
		list->addParamValue=addParamValue;
		list->addValue=addValue;
		list->addParamsValue=addParamsValue;
		
		
	//	list->trimIntToRange=trimIntToRange;
//		list->trimDoubleToRange=trimDoubleToRange;

		list->decrementValue=decrementValue;
		list->incrementValue=incrementValue;
		
		list->tryIncrementParamValue=tryIncrementParamValue;
		list->tryDecrementParamValue=tryDecrementParamValue;
		
		
		list->incrementParamValue=incrementParamValue;
		list->decrementParamValue=decrementParamValue;
		
		list->correctData=correctData;
}


_Bool insertPParamsList(PParamsList *data, SParam *param){
	
	if(param!=NULL){
		if(data->size+1<=data->maxSize){
			data->par[data->size]=*param;
			data->par[data->size].value=correctData(&data->par[data->size], data->par[data->size].value);
			data->par[data->size].defaultValue=correctData(&data->par[data->size], data->par[data->size].defaultValue);
			data->size++;
			return true;
		}
	}
	return false;
}


void clearPParamsList(PParamsList* data){
			
		memset(data->par, 0, sizeof(SParam)*data->maxSize);
		data->size=0;
	
		clearUnionParams(data);
}

bool insertUnionParam(PParamsList *data, SUnionParams unionParams){
	
	if(unionParams.acronim!=unionParams.acronimUnionParam){
		if(data->sizeUnionParamsList+1<=data->maxSizeUnionParamsList){
			data->unionParams[data->sizeUnionParamsList]=unionParams;
			data->sizeUnionParamsList++;
			return true;
		}
	}
	return false;
}


void clearUnionParams(PParamsList* data){
	
		memset(data->unionParams, 0, sizeof(SUnionParams)*data->maxSizeUnionParamsList);
		data->sizeUnionParamsList=0;
	
}

void copyListOfParams(PParamsList *data, const PParamsList *copyParams){
	
		clearPParamsList(data);
		for(int i=0; i<copyParams->size; i++){
			insertPParamsList(data, &copyParams->par[i]);
		}
	
}


SParam getParam(PParamsList* data, char acronim){
	SParam value={0};
	
	for(int i=0; i<data->size; i++){
		if(data->par[i].acronim==acronim){
			value=data->par[i];
			break;
		}
	}
	return value;
}

SParam* getParamPtr(PParamsList* data, char acronim){
	
	for(int i=0; i<data->size; i++){
		if(data->par[i].acronim==acronim){
			return &data->par[i];
		}
	}
	return NULL;
}

int getUnionParamsPtrTab(PParamsList* data, char acronim, SParam** unionParamsTab, int unionParTabSize){
	int j=0;
	
	for(int i=0; i<data->sizeUnionParamsList; i++){
		if(data->unionParams[i].acronim==acronim){
			unionParamsTab[j]=getParamPtr(data, data->unionParams[i].acronimUnionParam);
			j++;
		}
	}
	return j;
}


_Bool existsParam(PParamsList* data, char acronim){
	
	SParam *param=getParamPtr(data, acronim);
	
	if(param!=NULL) return true;
	
	return false;
}

int getParamValue(PParamsList* data, char acronim){
	
	return getParam(data, acronim).value;
}

double getParamRealValue(PParamsList* data, char acronim){
	
		SParam par=getParam(data, acronim);
	
	return (double)par.value/pow_pp(10, par.unit);
}
	
int getParamUpperLimit(PParamsList* data, char acronim){
	
	return getParam(data, acronim).upperLimit;
}
	
int getParamLowerLimit(PParamsList* data, char acronim){
	
	return getParam(data, acronim).lowerLimit;
}

int getParamUnit(PParamsList* data, char acronim){
	
	return getParam(data, acronim).unit;
}
	
int getParamPrecision(PParamsList* data, char acronim){
	
	return getParam(data, acronim).precision;
}

SValue* getParamValues(PParamsList* data, SValue *valTab, int valTabSize){
	
	memset(valTab, 0, sizeof(SValue)*valTabSize);
	
	for(int i=0; i<data->size && i<valTabSize; i++){
		valTab[i].acronim=data->par[i].acronim;
		valTab[i].value=data->par[i].value;
	}
	
	return valTab;
}


char* getParamsAcronims(PParamsList* data, char *str, unsigned int strSize){
	PString strFun;
	PStringConstruct(&strFun);
	
	str[0]='\0';
	
	for(int i=0; i<data->size; i++){
		strFun.pushBack(str, strSize, data->par[i].acronim);
	}
	
	return str;
}


char* getStringWithParamValueStatic(SParam* param, char *str){
	PString strFun;
	PStringConstruct(&strFun);
	str[0]='\0';
	
	if(param!=NULL){
		
		if(strlen(param->unitStr)==1 && param->unitStr[0]=='\"'){
			strFun.doubleToString(str, sec2deg(((double)param->value)/pow_pp(10, param->unit)), 3);
		}else{
			strFun.doubleToString(str, ((double)param->value)/pow_pp(10, param->unit), param->unit);
		}
		
	}
	
	return str;
}




char* getStringWithParam(PParamsList* data, char acronim, char *str, unsigned int strSize){
	
	SParam *param=getParamPtr(data, acronim);
	
	return getStringWithParamStatic(param, str, strSize);
}

char* getStringWithParamStatic(SParam* param, char *str, unsigned int strSize){
	PString strFun;
	PStringConstruct(&strFun);
	str[0]='\0';
	
	if(param!=NULL){
		char parLine[10]={0};
		strFun.pushBack(str, strSize, param->acronim);
		strFun.append(str, strSize, getStringWithParamValueStatic(param, parLine));
	}
	
	return str;
}


char* getStringWithParamDesc(PParamsList* data, char acronim, char *str, unsigned int strSize){

	SParam *param=getParamPtr(data, acronim);

	return getStringWithParamDescStatic(param, str, strSize);
		
}

char* getStringWithParamDescStatic(SParam* param, char *str, unsigned int strSize){
	PString strFun;
	PStringConstruct(&strFun);
	
	str[0]='\0';
	
	if(param!=NULL){
		char parLine[10]={0};
		strFun.pushBack(str, strSize, param->acronim);
		strFun.append(str, strSize, getStringWithParamValueStatic(param, parLine));
		strFun.append(str, strSize, param->unitStr);
	}
	
	return str;
}


char* getStringWithParamValueDescStatic(SParam* param, char *str, unsigned int strSize){
	PString strFun;
	PStringConstruct(&strFun);
	
	str[0]='\0';
	
	if(param!=NULL){
		char parLine[10]={0};
		strFun.append(str, strSize, getStringWithParamValueStatic(param, parLine));
		strFun.append(str, strSize, param->unitStr);
	}
	
	return str;
}

char* getStringWithParams(PParamsList* data, char *str, unsigned int strSize){
	PString strFun;
	PStringConstruct(&strFun);
	
	str[0]='\0';
	
	char parLine[10];
	for(int i=0; i<data->size; i++){
		strFun.append(str, strSize, getStringWithParam(data, data->par[i].acronim, parLine, sizeof(parLine)));
		if(i<data->size-1)strFun.pushBack(str, strSize, ' ');

	}
	return str;
}


unsigned int getMaxLengthOfStringWithParamStatic(SParam* param){
	PString strFun;
	PStringConstruct(&strFun);
	char str[30];
	int freeSpaceForData=0, freeSpaceForLowerLimit=0, freeSpaceForUpperLimit=0;
	
	if(param!=NULL){
		
		if(strlen(param->unitStr)==1 && param->unitStr[0]=='\"'){
			freeSpaceForUpperLimit=strlen(strFun.doubleToString(str, sec2deg(((double)param->upperLimit-param->precision)), 3));
			freeSpaceForLowerLimit=strlen(strFun.doubleToString(str, sec2deg(((double)param->lowerLimit+param->precision)), 3));
			freeSpaceForData=(freeSpaceForUpperLimit>freeSpaceForLowerLimit)?freeSpaceForUpperLimit:freeSpaceForLowerLimit;
		}else{
			if(param->unit>0){
				freeSpaceForUpperLimit=strlen(strFun.doubleToString(str, (double)(param->upperLimit-param->precision)/pow_pp(10, param->unit), param->unit));
				freeSpaceForLowerLimit=strlen(strFun.doubleToString(str, (double)(param->lowerLimit+param->precision)/pow_pp(10, param->unit), param->unit));
			}else{
				freeSpaceForUpperLimit=strlen(strFun.intToString(str, param->upperLimit));
				freeSpaceForLowerLimit=strlen(strFun.intToString(str, param->lowerLimit));
			}
			freeSpaceForData=(freeSpaceForUpperLimit>freeSpaceForLowerLimit)?freeSpaceForUpperLimit:freeSpaceForLowerLimit;
		}
		freeSpaceForData+=1;	//miejsce na akronim 
	}
	
	return freeSpaceForData;
}

unsigned int getMaxLengthOfStringWithParamDescStatic(SParam* param){
	int freeSpaceForData=0;
	
	if(param!=NULL){
		freeSpaceForData=getMaxLengthOfStringWithParamStatic(param)+strlen(param->unitStr);
	}
	
	return freeSpaceForData;
}



_Bool setParam(PParamsList *data, SParam *param){
	
	if(param!=NULL){
		SParam* par=getParamPtr(data, param->acronim);
		
		if(par!=NULL){
			*par=*param;
			return true;
		}
	}
	return false;
}

void setUnionsParamValue(PParamsList *data, SParam** unionParTab, int noOfUnions, int val){

		if(noOfUnions){
			for(int i=0; i<noOfUnions; i++){
				if(unionParTab[i]!=NULL){
					unionParTab[i]->value=correctData(unionParTab[i], val);
				}
			}
		}
		
}

void setUnionsParamRealValue(PParamsList *data, SParam** unionParTab, int noOfUnions, int val){

		if(noOfUnions){
			for(int i=0; i<noOfUnions; i++){
				if(unionParTab[i]!=NULL){
					unionParTab[i]->value=correctData(unionParTab[i], val*pow_pp(10, unionParTab[i]->unit));
				}
			}
		}
		
}

bool setParamValue(PParamsList *data, char acronim, int val){
	SParam* par=getParamPtr(data, acronim);
	
	if(par!=NULL){
		par->value=correctData(par, val);
		
		SParam* unionParTab[data->sizeUnionParamsList];
		int noOfUnions=getUnionParamsPtrTab(data, acronim, unionParTab, data->sizeUnionParamsList);
		setUnionsParamValue(data, unionParTab, noOfUnions, val);
		
		return true;
	}
	
	return false;
}

bool setParamRealValue(PParamsList *data, char acronim, double val){
	SParam* par=getParamPtr(data, acronim);
	
	if(par!=NULL){
		par->value=correctData(par, val*pow_pp(10, par->unit));
		
		
		SParam* unionParTab[data->sizeUnionParamsList];
		int noOfUnions=getUnionParamsPtrTab(data, acronim, unionParTab, data->sizeUnionParamsList);
		setUnionsParamRealValue(data, unionParTab, noOfUnions, val);
		
		return true;
	}
	
	return false;
}

_Bool setParamLowerLimit(PParamsList *data, char acronim, int val){
	SParam* par=getParamPtr(data, acronim);
	
	if(par!=NULL){
		par->lowerLimit=val;
		par->value=trim_pp(par->value, par->upperLimit, par->lowerLimit);
		par->defaultValue=trim_pp(par->defaultValue, par->upperLimit, par->lowerLimit);
		return true;
	}
	
	return false;
}

_Bool setParamUpperLimit(PParamsList *data, char acronim, int val){
	SParam* par=getParamPtr(data, acronim);
	
	if(par!=NULL){
		par->upperLimit=val;
		par->value=trim_pp(par->value, par->upperLimit, par->lowerLimit);
		par->defaultValue=trim_pp(par->defaultValue, par->upperLimit, par->lowerLimit);
		return true;
	}
	
	return false;
}

_Bool setParamDefaultValue(PParamsList *data, char acronim, int val){
	SParam* par=getParamPtr(data, acronim);
	
	if(par!=NULL){
		par->defaultValue=correctData(par, val);
		return true;
	}
	
	return false;
}

_Bool setParamPrecision(PParamsList *data, char acronim, int val){
	SParam* par=getParamPtr(data, acronim);
	
	if(par!=NULL){
		par->precision=val;

		par->value=correctData(par, par->value);
		par->defaultValue=correctData(par, par->defaultValue);
		
		return true;
	}
	
	return false;
}

_Bool setParamRealLowerLimit(PParamsList *data, char acronim, double value){
	SParam* par=getParamPtr(data, acronim);
	
	if(par!=NULL){
		par->lowerLimit=value*pow_pp(10, par->unit);
		par->value=trim_pp(par->value, par->upperLimit, par->lowerLimit);
		par->defaultValue=trim_pp(par->defaultValue, par->upperLimit, par->lowerLimit);
		return true;
	}
	
	return false;
}

_Bool setParamName(PParamsList *data, char acronim, char* name){
	
	SParam* par=getParamPtr(data, acronim);
	
	if(par!=NULL){
		par->name=name;
		return true;
	}
	
	return false;

}

void setParamsValueByDefaultValue(PParamsList *data){
	
	for(int i=0; i<data->size; i++){
		setParamValue(data, data->par[i].acronim, data->par[i].defaultValue);
	}
	
}
	
	
void setParamsValue(PParamsList *data, int value){
	
	
	for(int i=0; i<data->size; i++){
		setParamValue(data, data->par[i].acronim, value);
	}
	
}

void setParamsValueByCopy(PParamsList *data, PParamsList *dataToCopy){
	SParam parToCopy={0};
	
	
	for(int i=0; i<data->size; i++){
		 parToCopy=getParam(dataToCopy, data->par[i].acronim);
		if(parToCopy.acronim==data->par[i].acronim)data->par[i].value=parToCopy.value;
	}
}


void setParamsDefaultValue(PParamsList *data, int value){
	
	for(int i=0; i<data->size; i++){
		setParamDefaultValue(data, data->par[i].acronim, value);
	}
}

void setParamsRealLowerLimit(PParamsList *data, double value){
	
	for(int i=0; i<data->size; i++){
		setParamLowerLimit(data, data->par[i].acronim, value*pow_pp(10, data->par[i].unit));
	}
	
}


void setParamsValuesByValTab(PParamsList* data, SValue *valTab, int valTabSize){

	for(int i=0; i<valTabSize; i++){
		setParamValue(data, valTab[i].acronim, valTab[i].value);
		
	}	
	
}


void setParamsBasedString(PParamsList *data, const char *str){
	PString strFun;
	PStringConstruct(&strFun);

	for(int i=0; i<data->size; i++){
		
		if(strlen(data->par[i].unitStr)==1 && data->par[i].unitStr[0]=='\"'){
			double newValue=strFun.findValueAfterAcronim(str, data->par[i].acronim, sec2deg(data->par[i].value));
			setParamValue(data, data->par[i].acronim, deg2sec(newValue));
		}else{
			setParamValue(data, data->par[i].acronim, strFun.findValueAfterAcronim(str, data->par[i].acronim, ((double)data->par[i].value)/pow_pp(10, data->par[i].unit))*pow_pp(10, data->par[i].unit));
		}
	}	
	
}

unsigned int areParamsInString(PParamsList *data, const char *str){
	PString strFun;
	PStringConstruct(&strFun);
	unsigned int count=0;

	for(int i=0; i<data->size; i++){
     if(strFun.isCorrectValueAfterAcronim(str, data->par[i].acronim))count++;
	}	
	
	return count;
}


void addParamsValue(PParamsList *data, PParamsList *dataToAdd){
		SParam parToAdd={0};

		for(int i=0; i<data->size; i++){
			parToAdd=getParam(dataToAdd, data->par[i].acronim);
			if(parToAdd.acronim==data->par[i].acronim){
				data->par[i].value=correctData(&data->par[i], data->par[i].value+parToAdd.value);
			}
		}
}

_Bool exacCompareParamsValue(PParamsList *data, PParamsList *dataToComp){
	
	_Bool same=true;
	SParam parToComp={0};

	if(data->size==dataToComp->size){
		for(int i=0; i<data->size; i++){
			parToComp=getParam(dataToComp, data->par[i].acronim);
			if(parToComp.acronim==data->par[i].acronim){
				if(parToComp.value!=data->par[i].value){
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


void addParamValue(PParamsList *data, PParamsList *dataToAdd, char acronim){

		SParam* par=getParamPtr(data, acronim);
		SParam* parToAdd=getParamPtr(dataToAdd, acronim);
		if(par!=NULL && parToAdd!=NULL){
			par->value=correctData(par, par->value+parToAdd->value);
		}
}

void addValue(PParamsList *data, char acronim, int val){

		SParam* par=getParamPtr(data, acronim);
		if(par!=NULL){
			par->value=correctData(par, par->value+val);
		}
}

_Bool tryIncrementParamValue(SParam *param){
	_Bool possible=false;

	if(param!=NULL){
		if(param->value+param->precision<=param->upperLimit){
			possible=true;
		}
	}
	return possible;
}

_Bool tryDecrementParamValue(SParam *param){
	_Bool possible=false;

	if(param!=NULL){
		if(param->value-param->precision>=param->lowerLimit){
			possible=true;
		}
	}
	return possible;
}


_Bool decrementParamValue(SParam *param){
	_Bool changeParam=false;

	if(tryDecrementParamValue(param)){
			param->value-=param->precision;
			changeParam=true;
		}
	

	return changeParam;
}


_Bool incrementParamValue(SParam *param){
	_Bool changeParam=false;

	if(tryIncrementParamValue(param)){
			param->value+=param->precision;
			changeParam=true;
		}
	
	return changeParam;
}

_Bool decrementValue(SParam *param, int value){
	_Bool changeParam=false;

	if(param!=NULL){
		if(param->value-value>=param->lowerLimit){
			param->value-=value;
			changeParam=true;
		}
	}

	return changeParam;
}

_Bool incrementValue(SParam *param, int value){
	_Bool changeParam=false;

	if(param!=NULL){
		if(param->value+value<=param->upperLimit){
			param->value+=value;
			changeParam=true;
		}
	}
	return changeParam;
}

//void trimIntToRange(int *value, int upperLimit, int lowerLimit){

//		if(value!=NULL){
//			if(*value>=upperLimit)*value=upperLimit;
//			else if(*value<=lowerLimit)*value=lowerLimit;
//		}
//}

//void trimDoubleToRange(double *value, double upperLimit, double lowerLimit){

//	if(value!=NULL){
//		if(*value>=upperLimit)*value=upperLimit;
//		else if(*value<=lowerLimit)*value=lowerLimit;
//	}
//}


int correctData(SParam *param, int data){
	
		if(param!=NULL){
			data=trimAcc_pp(data, param->upperLimit, param->lowerLimit, param->precision);
		}
		return data;
}


int indexOfLineInValTab(SValue *valTab, int sizeTab, char acronim){
		int index=NPOS;
		for(int i=0; i<sizeTab;i++){
			if(valTab[i].acronim==acronim){
				index=i;
				break;
			}
		}
		return index;
}

