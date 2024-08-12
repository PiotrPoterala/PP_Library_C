#ifndef _PP_QUEUE_H
	#define _PP_QUEUE_H

	#ifdef __cplusplus
	extern "C" {
	#endif

		#include <stdbool.h>
		#include <sparam.h>


		typedef struct{
			volatile int *queue;
			int maxSize;
			volatile unsigned int head;
			volatile unsigned int tail;
		}PQueueData;
		
		typedef struct{
			PQueueData data;
			
			int (*size)(PQueueData *data);
			int (*dequeue)(PQueueData *data);
			_Bool (*enqueue)(PQueueData *data, int i);
			int (*isEmpty)(PQueueData *data);
			
			void (*skip)(PQueueData *data, int noOfElem);
			
			int (*availableSpace)(PQueueData *data);
			void (*enqueueTab)(PQueueData *data, int *tab, unsigned int tabSize);
			void (*dequeueTab)(PQueueData *data, int *tab, unsigned int tabSize);
			void (*dequeueValTab)(PQueueData *data, SValue *valTab, unsigned int tabSize);
		}PQueue;
		
		void PQueueConstruct(PQueue *queue, volatile int *tab, int maxSize);
		
		int sizeQueue(PQueueData *data);
		int dequeue(PQueueData *data);
		_Bool enqueue(PQueueData *data, int i);
		_Bool enqueueWithTimeout(PQueueData *data, int i, int timeout);
		int isEmpty(PQueueData *data);
		
		void skipPartOfQueue(PQueueData *data, int noOfElem);
		
		int availableSpace(PQueueData *data);
		void enqueueTab(PQueueData *data, int *tab, unsigned int tabSize);
		void dequeueTab(PQueueData *data, int *tab, unsigned int tabSize);
		void dequeueValTab(PQueueData *data, SValue *valTab, unsigned int tabSize);
		
#ifdef __cplusplus
}
#endif
		
#endif
