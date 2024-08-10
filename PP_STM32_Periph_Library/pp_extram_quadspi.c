#include "pp_extram_quadspi.h"
//#include "stdio.h"
#include <string.h>

void PExtRamConstruct(PExtRam *extram, TypeOfExtRam typeOfRam, unsigned int firstAdress, unsigned int areaSize, void *receiveQueue, void *sendQueue){
	
		extram->data.spiDataMode=SINGLE_LINE;
		extram->data.sendSingleBytes=false;
	
		extram->data.firstAdress=firstAdress;
		extram->data.areaSize=areaSize;
	//	extram->data.focusAdress=(unsigned int*)(extram->data.firstAdress);
		extram->data.focusAdress=extram->data.firstAdress;
	
		extram->data.sendQueue=sendQueue;
		extram->data.receiveQueue=receiveQueue;
	
		extram->data.rdWrInProgress=false;
	
		memset(extram->data.receiveData, 0, sizeof(extram->data.receiveData));
	
	
		extram->size=sizeExtRAM;
		extram->pos= posExtRAM;
		extram->atEnd=atEndExtRAM;
		extram->seek=seekExtRAM;
	
//		extram->readData=readDataExtRAM;
	
		if(typeOfRam==FT8XX){	
			extram->open=openExtRAMft8XX;
			extram->close=closeExtRAMft8XX;
			extram->reset=resetExtRAMft8XX;

			extram->read=readExtRAMft8XX;
			extram->readTab=readTabExtRAMft8XX;
			extram->write=writeExtRAMft8XX;
			extram->writeTab=writeTabExtRAMft8XX;
			extram->writeHostComm=writeHostCommExtRAMft8XX;
	
			extram->portListen=portListenExtRAMft8XX;
			extram->setSpiDataMode=setSpiDataModeExtRAMft8XX;
//			extram->waitForReadyRead=waitForReadyReadExtRAMft8XX;
		}
	
}


int sizeExtRAM(PExtRamData *data){
	

	return data->areaSize;
	
}


int posExtRAM(PExtRamData *data){
	
	return ((unsigned int)data->focusAdress-data->firstAdress)/sizeof(unsigned int);
	
}


bool atEndExtRAM(PExtRamData *data){
	
		if(data->areaSize<=posExtRAM(data))return true;
		
		return false;	
}



bool seekExtRAM(PExtRamData *data, int pos){
	
	if(pos<data->areaSize){
	//	data->focusAdress=(unsigned int*)(data->firstAdress);

		data->focusAdress=data->firstAdress+(pos*sizeof(unsigned int));
		
		return true;
	}
	
	return false;
	
}



//int readDataExtRAM(PExtRamData* data, int *readDataTab, int maxSize){
//	int readData=0;
//	
//	if(data->getDataFlag){
//		readData=(data->nbrOfDataToTransfer<maxSize)?data->nbrOfDataToTransfer:maxSize;
//		memcpy(readDataTab, data->receiveData, readData);
//		data->nbrOfDataToTransfer=0;
//		data->getDataFlag=false;
//	}
//	return readData;
//	
//}





