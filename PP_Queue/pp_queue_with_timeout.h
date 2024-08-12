#ifndef _PP_QUEUE_WITH_TIMEOUT_H
	#define _PP_QUEUE_WITH_TIMEOUT_H

	#ifdef __cplusplus
	extern "C" {
	#endif

		#include <stdbool.h>
		
		#include "pp_queue.h"
		
		#define osWaitForever         (-1)
		
		typedef struct{
			PQueueData data;
			
			int (*size)(PQueueData *data);
			_Bool (*dequeue)(PQueueData *data, int *getData, int timeout);
			_Bool (*enqueue)(PQueueData *data, int i, int timeout);
			int (*isEmpty)(PQueueData *data);
			
			void (*skip)(PQueueData *data, int noOfElem);
			
			int (*availableSpace)(PQueueData *data);
			_Bool (*enqueueTab)(PQueueData *data, int *tab, unsigned int tabSize, int timeout);
			_Bool (*dequeueTab)(PQueueData *data, int *tab, unsigned int tabSize, int timeout);
			_Bool (*dequeueValTab)(PQueueData *data, SValue *valTab, unsigned int tabSize, int timeout);
		}PQueueWithTimeout;
		
		void PQueueWithTimeoutConstruct(PQueueWithTimeout *queue, volatile int *tab, int maxSize);
		
		_Bool dequeueWithTimeout(PQueueData *data, int *getData, int timeout);
		_Bool enqueueWithTimeout(PQueueData *data, int i, int timeout);
		
		_Bool enqueueTabWithTimeout(PQueueData *data, int *tab, unsigned int tabSize, int timeout);
		_Bool dequeueTabWithTimeout(PQueueData *data, int *tab, unsigned int tabSize, int timeout);
		_Bool dequeueValTabWithTimeout(PQueueData *data, SValue *valTab, unsigned int tabSize, int timeout);
		
		
		_Bool enqueueTimeoutPermission(PQueueData *data, int noOfDataToEnqueue, int timeout);
		_Bool dequeueTimeoutPermission(PQueueData *data, int noOfDataToDequeue, int timeout);
		
#ifdef __cplusplus
}
#endif
		
#endif
