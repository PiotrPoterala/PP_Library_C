#ifndef _PP_EXTRAM_QUADSPI_FT8XX_H
	#define _PP_EXTRAM_QUADSPI_FT8XX_H

	#ifdef __cplusplus
	extern "C" {
	#endif

	#include <stdbool.h>
	#include "stm32.h"
	#include "pp_extram_defines.h"
	
	
	void setSpiDataModeExtRAMft8XX(PExtRamData *data, QuadSpiDataMode dataMode);

	bool openExtRAMft8XX(PExtRamData *data, OpenMode mode);
	bool closeExtRAMft8XX(PExtRamData *data);
	void resetExtRAMft8XX(PExtRamData *data);

	void readTabExtRAMft8XX(PExtRamData *data, int *dataToReceive, int dataSize);
	int readExtRAMft8XX(PExtRamData *data);
	bool writeExtRAMft8XX(PExtRamData *data, int dataToSend);
	bool writeTabExtRAMft8XX(PExtRamData *data, int *dataToSend, int dataSize);
	void writeHostCommExtRAMft8XX(PExtRamData *data, unsigned int command, unsigned int param);
	
	void portListenExtRAMft8XX(PExtRamData* data);
	void sendWord8FromSendQueueExtRAMft8XX(PExtRamData* data);
	void sendWord32FromSendQueueExtRAMft8XX(PExtRamData* data);
	void receiveAndWriteToReceiveQueueExtRAMft8XX(PExtRamData* data);
	
	bool waitForReadyReadExtRAMft8XX(PExtRamData *data);

#ifdef __cplusplus
}
#endif
	
#endif
