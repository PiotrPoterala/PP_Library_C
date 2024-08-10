#ifndef _PP_EXTRAM_QUADSPI_H
	#define _PP_EXTRAM_QUADSPI_H

	#ifdef __cplusplus
	extern "C" {
	#endif

	#include <stdbool.h>
	#include "stm32.h"
	#include "pp_extram_defines.h"
	#include "pp_extram_quadspi_ft8xx.h"

	
	typedef struct{
		PExtRamData data;

		bool (*open)(PExtRamData *data, OpenMode mode);
		bool (*close)(PExtRamData *data);
		void (*reset)(PExtRamData *data);
		
		int (*pos)(PExtRamData *data);
		int (*size)(PExtRamData *data);
		bool (*atEnd)(PExtRamData *data);
		bool (*seek)(PExtRamData *data, int pos);
		int (*read)(PExtRamData *data);
		void (*readTab)(PExtRamData *data, int *dataToReceive, int dataSize);
		bool (*write)(PExtRamData *data, int dataToSend);
		bool (*writeTab)(PExtRamData *data, int *dataToSend, int dataSize);
		void (*writeHostComm)(PExtRamData *data, unsigned int command, unsigned int param);
		
		void (*portListen)(PExtRamData* data);
		
		void (*setSpiDataMode)(PExtRamData* data, QuadSpiDataMode dataMode);
//		bool (*waitForReadyRead)(PExtRamData *data);
	//	int (*readData)(PExtRamData* data, int *readDataTab, int maxSize);
	}PExtRam;
	
	void PExtRamConstruct(PExtRam *sram, TypeOfExtRam typeOfRam, unsigned int firstAdress, unsigned int areaSize, void *receiveQueue, void *sendQueue);
	
	int posExtRAM(PExtRamData *data);
	int sizeExtRAM(PExtRamData *data);
	bool atEndExtRAM(PExtRamData *data);
	bool seekExtRAM(PExtRamData *data, int pos);
	
//	int readDataExtRAM(PExtRamData* data, int *readDataTab, int maxSize);

#ifdef __cplusplus
}
#endif
	
#endif
