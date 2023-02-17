#include <stdio.h>
#include "pp_signals.h"


void PCheckSignalsConstruct(PCheckSignals *oCSignals){

	oCSignals->data.currCheckingSetSignals=0;
	oCSignals->data.checkedSetSignals=0;
	oCSignals->data.currCheckingResetSignals=0;
	oCSignals->data.checkedResetSignals=0;
	oCSignals->data.madeSignals=0;

	oCSignals->checkSignal=checkSignal;
	oCSignals->checkSetSignal=checkSetSignal;
	oCSignals->checkResetSignal=checkResetSignal;
}

void checkSignal(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask){
	
	checkSetSignal(data, portIDR, pinMask, checkSygMask);
	checkResetSignal(data, portIDR, pinMask, checkSygMask);
	
}


void checkSetSignal(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask){
			
			
		if(!((data->currCheckingSetSignals) & checkSygMask)){
			if(KEY_SELECT(portIDR, pinMask)==B_HIGH)(data->currCheckingSetSignals)|=checkSygMask; 
		}else{
			if(KEY_SELECT(portIDR, pinMask)==B_HIGH)(data->checkedSetSignals)|=checkSygMask;
			else{
				(data->currCheckingSetSignals)&=~checkSygMask;
				(data->checkedSetSignals)&=~checkSygMask;
			}
		}

}

void checkResetSignal(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask){
			
			
		if(!((data->currCheckingResetSignals) & checkSygMask)){
			if(KEY_SELECT(portIDR, pinMask)==B_HIGH)(data->currCheckingResetSignals)|=checkSygMask; 
		}else{
			if(KEY_SELECT(portIDR, pinMask)==B_HIGH)(data->checkedResetSignals)|=checkSygMask;
			else{
				(data->currCheckingResetSignals)&=~checkSygMask;
				(data->checkedResetSignals)&=~checkSygMask;
			}
		}

}


