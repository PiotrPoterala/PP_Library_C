#ifndef _PP_QUEUE_WITH_PP_MUTEX_H
	#define _PP_QUEUE_WITH_PP_MUTEX_H

	#ifdef __cplusplus
	extern "C" {
	#endif

		#include <stdbool.h>
		
		#include "pp_queue.h"
		#include "pp_mutex.h"

		typedef struct{
			PQueue *queue;
			PMutex *mutex;
		}PQueueWithMutexData;
		
		
		void skipPartOfQueueWithMutex(PQueueWithMutexData *data, int noOfElem);
		int isEmptyQueueWithMutex(PQueueWithMutexData *data);
		int availableSpaceQueueWithMutex(PQueueWithMutexData *data);
		
		int sizeQueueWithMutex(PQueueWithMutexData *data);
		bool dequeueWithMutex(PQueueWithMutexData *data, int *getData);
		bool enqueueWithMutex(PQueueWithMutexData *data, int i);
		
		bool enqueueTabWithMutex(PQueueWithMutexData *data, int *tab, unsigned int tabSize);
		bool dequeueTabWithMutex(PQueueWithMutexData *data, int *tab, unsigned int tabSize);
		bool dequeueValTabWithMutex(PQueueWithMutexData *data, SValue *valTab, unsigned int tabSize);
		
#ifdef __cplusplus
}
#endif
		
#endif
