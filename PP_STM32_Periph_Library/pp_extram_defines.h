#ifndef _PP_QUADSPI_DEFINES_H
	#define _PP_QUADSPI_DEFINES_H

	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include "pp_queue_with_timeout.h"
	#include "pp_iodevice.h"
	
		typedef enum {FT8XX=1} TypeOfExtRam;
		typedef enum {SINGLE_LINE=1, QUAD_LINE} QuadSpiDataMode;

		typedef struct{
			unsigned int firstAdress;
			unsigned int areaSize;
			
			unsigned int focusAdress;
			
			QuadSpiDataMode spiDataMode;
			bool sendSingleBytes;
			volatile bool rdWrInProgress;

			PQueueWithTimeout *receiveQueue;
			PQueueWithTimeout *sendQueue;
			
			bool isOpen;
			OpenMode openMode;	
			
			int nbrOfDataToRead;
			int nbrOfDataToTransfer;
			bool getDataFlag;
		
			int receiveData[256];
		}PExtRamData;



#ifdef __cplusplus
}
#endif
	
#endif
