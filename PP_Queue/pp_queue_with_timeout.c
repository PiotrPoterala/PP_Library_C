#include <string.h>
#include "pp_queue_with_timeout.h"

void PQueueWithTimeoutConstruct(PQueueWithTimeout *queue, volatile int *tab, int maxSize){
	
		queue->data.head=0;
		queue->data.tail=0;
		queue->data.maxSize=maxSize;
		queue->data.queue=tab;
	
		queue->size=sizeQueue;
		queue->dequeue=dequeueWithTimeout;
		queue->enqueue=enqueueWithTimeout;
		queue->isEmpty=isEmpty;
	
		queue->skip=skipPartOfQueue;
	
		queue->availableSpace=availableSpace;
		queue->enqueueTab=enqueueTabWithTimeout;
		queue->dequeueTab=dequeueTabWithTimeout;
		queue->dequeueValTab=dequeueValTabWithTimeout;
	
	
	
}

_Bool dequeueWithTimeout(PQueueData *data, int *getData, int timeout){
	_Bool ans=false;
	
	if(dequeueTimeoutPermission(data, 1, timeout)){
		*getData=dequeue(data);
		ans=true;
	}
		
	return ans;
}




_Bool enqueueWithTimeout(PQueueData *data, int i, int timeout){
	_Bool ans=false;
	
	if(enqueueTimeoutPermission(data, 1, timeout)){
		ans=enqueue(data, i);
	}
	return ans;
}
	


_Bool enqueueTabWithTimeout(PQueueData *data, int *tab, unsigned int tabSize, int timeout){
	
	_Bool ans=false;
	
	if(enqueueTimeoutPermission(data, tabSize, timeout)){
		enqueueTab(data, tab, tabSize);
		ans=true;
	}
	
	return ans;
}

_Bool dequeueTabWithTimeout(PQueueData *data, int *tab, unsigned int tabSize, int timeout){
	
	_Bool ans=false;
	
	if(dequeueTimeoutPermission(data, tabSize, timeout)){
		dequeueTab(data, tab, tabSize);
		ans=true;
	}
	
	return ans;
}

_Bool dequeueValTabWithTimeout(PQueueData *data, SValue *valTab, unsigned int tabSize, int timeout){
	
	_Bool ans=false;
	
	if(dequeueTimeoutPermission(data, 2*tabSize, timeout)){
		dequeueValTab(data, valTab, tabSize);
		ans=true;
	}
	
	return ans;
}


_Bool enqueueTimeoutPermission(PQueueData *data, int noOfDataToEnqueue, int timeout){
	_Bool permition=true;
		
	if(timeout==osWaitForever){
		while(availableSpace(data)<noOfDataToEnqueue)
		;
	}else if(timeout==0){
		if(availableSpace(data)<noOfDataToEnqueue)permition=false;
	}else{
		int count;
		for(count=0; count<timeout && availableSpace(data)<noOfDataToEnqueue; count++);
		
		if(count>=timeout)permition=false;
	}
	
	return permition;
}

_Bool dequeueTimeoutPermission(PQueueData *data, int noOfDataToDequeue, int timeout){
	_Bool permition=true;
		
	if(timeout==osWaitForever){
		while(sizeQueue(data)<noOfDataToDequeue)
		;
	}else if(timeout==0){
		if(sizeQueue(data)<noOfDataToDequeue)permition=false;
	}else{
		int count;
		for(count=0; count<timeout && sizeQueue(data)<noOfDataToDequeue; count++);
		
		if(count>=timeout)permition=false;
	}
	
	return permition;
}
