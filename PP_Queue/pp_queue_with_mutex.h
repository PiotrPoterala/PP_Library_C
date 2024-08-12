#ifndef _PP_QUEUE_WITH_MUTEX_H
	#define _PP_QUEUE_WITH_MUTEX_H

	#ifdef __cplusplus
	extern "C" {
	#endif

		#include <stdbool.h>
		
		#if defined(KEIL_RTX5) 
			#include "pp_queue_with_rtx_mutex.h"
		#else
			#include "pp_queue_with_pp_mutex.h"
		#endif

		
		typedef struct{
			PQueueWithMutexData data;
			
			int (*size)(PQueueWithMutexData *data);
			bool (*dequeue)(PQueueWithMutexData *data, int *getData);
			bool (*enqueue)(PQueueWithMutexData *data, int i);
			int (*isEmpty)(PQueueWithMutexData *data);
			
			void (*skip)(PQueueWithMutexData *data, int noOfElem);
			
			int (*availableSpace)(PQueueWithMutexData *data);
			bool (*enqueueTab)(PQueueWithMutexData *data, int *tab, unsigned int tabSize);
			bool (*dequeueTab)(PQueueWithMutexData *data, int *tab, unsigned int tabSize);
			bool (*dequeueValTab)(PQueueWithMutexData *data, SValue *valTab, unsigned int tabSize);
		}PQueueWithMutex;
		
		void PQueueWithMutexConstruct(PQueueWithMutex *queueWithMutex, void *queue, void *mutex);
		
		
#ifdef __cplusplus
}
#endif
		
#endif
