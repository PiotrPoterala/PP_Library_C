#include <string.h>
#include "pp_queue_with_mutex.h"

void PQueueWithMutexConstruct(PQueueWithMutex *queueWithMutex, void *queue, void *mutex){
	
		queueWithMutex->data.queue=queue;
		queueWithMutex->data.mutex=mutex;
	
		queueWithMutex->size=sizeQueueWithMutex;
		queueWithMutex->dequeue=dequeueWithMutex;
		queueWithMutex->enqueue=enqueueWithMutex;
		queueWithMutex->isEmpty=isEmptyQueueWithMutex;
	
		queueWithMutex->skip=skipPartOfQueueWithMutex;
	
		queueWithMutex->availableSpace=availableSpaceQueueWithMutex;
		queueWithMutex->enqueueTab=enqueueTabWithMutex;
		queueWithMutex->dequeueTab=dequeueTabWithMutex;
		queueWithMutex->dequeueValTab=dequeueValTabWithMutex;
	
	

}
