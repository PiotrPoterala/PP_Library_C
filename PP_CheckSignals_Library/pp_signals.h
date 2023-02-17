#ifndef _PP_SIGNALS_H
	#define _PP_SIGNALS_H


#define KEY_SELECT(PORT, PIN) (((PORT & PIN)>0)?1:0)	

	typedef enum
	{ B_LOW=0,
		B_HIGH=1
	}inputStatus;

	typedef struct{

		unsigned int currCheckingSetSignals;
		unsigned int checkedSetSignals;
		
		unsigned int currCheckingResetSignals;
		unsigned int checkedResetSignals;
		
		unsigned int madeSignals;
		
	}CheckSignalsData;
	
	
	typedef struct{
		CheckSignalsData data;
		
		void (*checkSignal)(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask);
		void (*checkSetSignal)(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask);
		void (*checkResetSignal)(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask);
	}PCheckSignals;

	void PCheckSignalsConstruct(PCheckSignals *oCSignals);
	
		void checkSignal(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask);
		void checkSetSignal(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask);
		void checkResetSignal(CheckSignalsData *data, unsigned int portIDR, unsigned int pinMask, unsigned int checkSygMask);
#endif
