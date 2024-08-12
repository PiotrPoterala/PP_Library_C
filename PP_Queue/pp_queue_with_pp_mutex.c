#include <string.h>
#include "pp_queue_with_pp_mutex.h"


int sizeQueueWithMutex(PQueueWithMutexData *data){
	
	return sizeQueue(&data->queue->data);
	
}


void skipPartOfQueueWithMutex(PQueueWithMutexData *data, int noOfElem){
	
	skipPartOfQueue(&data->queue->data, noOfElem);
	
}


int isEmptyQueueWithMutex(PQueueWithMutexData *data){
	
	return isEmpty(&data->queue->data);
	

}

int availableSpaceQueueWithMutex(PQueueWithMutexData *data){
	
	return availableSpace(&data->queue->data);
	
}




_Bool dequeueWithMutex(PQueueWithMutexData *data, int *getData){
	_Bool ans=false;
	
	if(sizeQueue(&data->queue->data)>=1){
		if(data->mutex->tryTake(data->mutex->available)){
			data->mutex->take(&data->mutex->available);
			*getData=dequeue(&data->queue->data);
			ans=true;
			data->mutex->give(&data->mutex->available);
		}
	}
	
	return ans;
}

_Bool enqueueWithMutex(PQueueWithMutexData *data, int i){
	_Bool ans=false;
	if(availableSpace(&data->queue->data)>=1){
		if(data->mutex->tryTake(data->mutex->available)){
			data->mutex->take(&data->mutex->available);
			ans=enqueue(&data->queue->data, i);
			data->mutex->give(&data->mutex->available);
		}
	}
	return ans;
}


_Bool enqueueTabWithMutex(PQueueWithMutexData *data, int *tab, unsigned int tabSize){
	
	_Bool ans=false;
	if(availableSpace(&data->queue->data)>=tabSize){
		if(data->mutex->tryTake(data->mutex->available)){
			data->mutex->take(&data->mutex->available);
			enqueueTab(&data->queue->data, tab, tabSize);
			ans=true;
			data->mutex->give(&data->mutex->available);
		}
	}
	return ans;
}

_Bool dequeueTabWithMutex(PQueueWithMutexData *data, int *tab, unsigned int tabSize){
	
	_Bool ans=false;
	
	if(sizeQueue(&data->queue->data)>=tabSize){
		if(data->mutex->tryTake(data->mutex->available)){
			data->mutex->take(&data->mutex->available);
			dequeueTab(&data->queue->data, tab, tabSize);
			ans=true;
			data->mutex->give(&data->mutex->available);
		}
	}
	return ans;
}

_Bool dequeueValTabWithMutex(PQueueWithMutexData *data, SValue *valTab, unsigned int tabSize){
	
	_Bool ans=false;
	
	if(sizeQueue(&data->queue->data)>=(2*tabSize)){
		if(data->mutex->tryTake(data->mutex->available)){
			data->mutex->take(&data->mutex->available);
			dequeueValTab(&data->queue->data, valTab, tabSize);
			ans=true;
			data->mutex->give(&data->mutex->available);
		}
	}
	return ans;
}
