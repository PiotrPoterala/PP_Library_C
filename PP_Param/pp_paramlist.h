#ifndef _PP_PARAM_LIST_H
	#define _PP_PARAM_LIST_H
	
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include <stdbool.h>
	#include "sparam.h"
	
	#define MAX_UNION_PARAMS	10
	
//		typedef struct{
//			SUnionParams *par;
//			int size;
//			int maxSize;
//		}PUnionParamsList;
	
		typedef struct{
			SParam *par;
			int size;
			int maxSize;
			
			SUnionParams unionParams[MAX_UNION_PARAMS];
			int sizeUnionParamsList;
			int maxSizeUnionParamsList;
		}PParamsList;
		
	typedef struct{
		PParamsList data;

		bool (*insert)(PParamsList *data, SParam *param);
		void (*clear)(PParamsList* data);
		
		bool (*insertUnionParam)(PParamsList *data, SUnionParams unionParams);
		void (*clearUnionParams)(PParamsList* data);
		
		SParam (*getParam)(PParamsList* data, char acronim);
		SParam* (*getParamPtr)(PParamsList* data, char acronim);
		
		_Bool (*exists)(PParamsList* data, char acronim);
		
		void (*copyListOfParams)(PParamsList *data, const PParamsList *copyParams);

		int (*getParamValue)(PParamsList* data, char acronim);
		int (*getParamUpperLimit)(PParamsList* data, char acronim);
		int (*getParamLowerLimit)(PParamsList* data, char acronim);
		int (*getParamUnit)(PParamsList* data, char acronim);
		int (*getParamPrecision)(PParamsList* data, char acronim);
		
		double (*getParamRealValue)(PParamsList* data, char acronim);
		
		SValue* (*getParamValues)(PParamsList* data, SValue *valTab, int valTabSize);

		char* (*getParamsAcronims)(PParamsList* data, char *str, unsigned int strSize);
		char* (*getStringWithParam)(PParamsList* data, char acronim, char *str, unsigned int strSize);
		char* (*getStringWithParamDesc)(PParamsList* data, char acronim, char *str, unsigned int strSize);
		char* (*getStringWithParams)(PParamsList* data, char *str, unsigned int strSize);

		bool (*setParam)(PParamsList *data, SParam *param);
		bool (*setParamValue)(PParamsList *data, char acronim, int val);
		_Bool (*setParamRealValue)(PParamsList *data, char acronim, double val);
		_Bool (*setParamLowerLimit)(PParamsList *data, char acronim, int val);
		_Bool (*setParamUpperLimit)(PParamsList *data, char acronim, int val);
		_Bool (*setParamDefaultValue)(PParamsList *data, char acronim, int val);
		_Bool (*setParamPrecision)(PParamsList *data, char acronim, int val);
		_Bool (*setParamRealLowerLimit)(PParamsList *data, char acronim, double value);
		_Bool (*setParamName)(PParamsList *data, char acronim, char* name);
		
		void (*setParamsValueByDefaultValue)(PParamsList *data);
		void (*setParamsValue)(PParamsList *data, int value);
		void (*setParamsValueByCopy)(PParamsList *data, PParamsList *dataToCopy);
		
		void (*setParamsDefaultValue)(PParamsList *data, int value);
		void (*setParamsRealLowerLimit)(PParamsList *data, double value);
		
		void (*setParamsValuesByValTab)(PParamsList* data, SValue *valTab, int valTabSize);
		unsigned int (*areParamsInString)(PParamsList *data, const char *str);
		void (*setParamsBasedString)(PParamsList *data, const char *str);

		_Bool (*exacCompareParamsValue)(PParamsList *data, PParamsList *dataToComp);
		void (*addParamValue)(PParamsList *data, PParamsList *dataToAdd, char acronim);
		void (*addValue)(PParamsList *data, char acronim, int val);
		void (*addParamsValue)(PParamsList *data, PParamsList *dataToAdd);

		_Bool (*tryIncrementParamValue)(SParam *param);
		_Bool (*tryDecrementParamValue)(SParam *param);

		_Bool (*incrementParamValue)(SParam *param);
		_Bool (*decrementParamValue)(SParam *param);

		_Bool (*decrementValue)(SParam *param, int value);
		_Bool (*incrementValue)(SParam *param, int value);
		
		int (*correctData)(SParam *param, int data);
		
	}PConstParamsList;
	
	void PConstParamsListConstruct(PConstParamsList *list, SParam *tab, int maxSize);
	
	void copyListOfParams(PParamsList *data, const PParamsList *copyParams);
	
	
	_Bool insertPParamsList(PParamsList *data, SParam *param);
	void clearPParamsList(PParamsList* data);
	
	bool insertUnionParam(PParamsList *data, SUnionParams unionParams);
	void clearUnionParams(PParamsList* data);
	
	_Bool existsParam(PParamsList* data, char acronim);
	SParam getParam(PParamsList* data, char acronim);
	SParam* getParamPtr(PParamsList* data, char acronim);
	int getUnionParamsPtrTab(PParamsList* data, char acronim, SParam** unionParamsTab, int unionParTabSize);

	void setUnionsParamValue(PParamsList *data, SParam** unionParTab, int noOfUnions, int val);
	void setUnionsParamRealValue(PParamsList *data, SParam** unionParTab, int noOfUnions, int val);
	
	int getParamValue(PParamsList* data, char acronim);
	int getParamUpperLimit(PParamsList* data, char acronim);
	int getParamLowerLimit(PParamsList* data, char acronim);
	int getParamUnit(PParamsList* data, char acronim);
	int getParamPrecision(PParamsList* data, char acronim);
	
	double getParamRealValue(PParamsList* data, char acronim);
	
	SValue* getParamValues(PParamsList* data, SValue *valTab, int valTabSize);

	char* getParamsAcronims(PParamsList* data, char *str, unsigned int strSize);
	char* getStringWithParam(PParamsList* data, char acronim, char *str, unsigned int strSize);
	char* getStringWithParamDesc(PParamsList* data, char acronim, char *str, unsigned int strSize);
	char* getStringWithParams(PParamsList* data, char *str, unsigned int strSize);

	bool setParam(PParamsList *data, SParam *param);
	bool setParamValue(PParamsList *data, char acronim, int val);
	_Bool setParamRealValue(PParamsList *data, char acronim, double val);
	_Bool setParamLowerLimit(PParamsList *data, char acronim, int val);
	_Bool setParamUpperLimit(PParamsList *data, char acronim, int val);
	_Bool setParamDefaultValue(PParamsList *data, char acronim, int val);
	_Bool setParamPrecision(PParamsList *data, char acronim, int val);
	_Bool setParamRealLowerLimit(PParamsList *data, char acronim, double value);
	_Bool setParamName(PParamsList *data, char acronim, char* name);
	
	void setParamsValueByDefaultValue(PParamsList *data);
	void setParamsValue(PParamsList *data, int value);
	void setParamsValueByCopy(PParamsList *data, PParamsList *dataToCopy);
	
	void setParamsDefaultValue(PParamsList *data, int value);
	void setParamsRealLowerLimit(PParamsList *data, double value);
	
	void setParamsValuesByValTab(PParamsList* data, SValue *valTab, int valTabSize);
	unsigned int areParamsInString(PParamsList *data, const char *str);
	void setParamsBasedString(PParamsList *data, const char *str);

	_Bool exacCompareParamsValue(PParamsList *data, PParamsList *dataToComp);
	void addParamValue(PParamsList *data, PParamsList *dataToAdd, char acronim);
	void addValue(PParamsList *data, char acronim, int val);
	void addParamsValue(PParamsList *data, PParamsList *dataToAdd);
	
//	void trimIntToRange(int *value, int upperLimit, int lowerLimit);
//	void trimDoubleToRange(double *value, double upperLimit, double lowerLimit);

	_Bool tryIncrementParamValue(SParam *param);
	_Bool tryDecrementParamValue(SParam *param);

	_Bool incrementParamValue(SParam *param);
	_Bool decrementParamValue(SParam *param);

	_Bool decrementValue(SParam *param, int value);
	_Bool incrementValue(SParam *param, int value);
	
	int correctData(SParam *param, int data);
	
	
	
	char* getStringWithParamValueStatic(SParam* param, char *str);
	char* getStringWithParamStatic(SParam* param, char *str, unsigned int strSize);
	char* getStringWithParamDescStatic(SParam* param, char *str, unsigned int strSize);
	char* getStringWithParamValueDescStatic(SParam* param, char *str, unsigned int strSize);
	unsigned int getMaxLengthOfStringWithParamStatic(SParam* param);
	unsigned int getMaxLengthOfStringWithParamDescStatic(SParam* param);
	
	
	
	int indexOfLineInValTab(SValue *valTab, int sizeTab, char acronim);
	
	#ifdef __cplusplus
}
#endif
	
#endif
