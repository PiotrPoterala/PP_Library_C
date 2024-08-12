#include <string.h>
#include "pp_queue.h"


void PQueueConstruct(PQueue *queue, volatile int *tab, int maxSize){
	
		queue->data.head=0;
		queue->data.tail=0;
		queue->data.maxSize=maxSize;
		queue->data.queue=tab;
	
		queue->size=sizeQueue;
		queue->dequeue=dequeue;
		queue->enqueue=enqueue;
		queue->isEmpty=isEmpty;
	
		queue->skip=skipPartOfQueue;
	
		queue->availableSpace=availableSpace;
		queue->enqueueTab=enqueueTab;
		queue->dequeueTab=dequeueTab;
		queue->dequeueValTab=dequeueValTab;
	
}

int sizeQueue(PQueueData *data){
	int usedSpace=0;
	
	if(data->head<=data->tail)usedSpace=data->tail-data->head;
	else usedSpace=data->tail+(data->maxSize-data->head);
	
	return usedSpace;
}


int dequeue(PQueueData *data){
	int dataToReturn=data->queue[data->head];
	
	if(data->head+1<data->maxSize)data->head++;
	else data->head=0;
	
	return dataToReturn;
}

void skipPartOfQueue(PQueueData *data, int noOfElem){
	int newHead=data->head;
	
	if(data->head+noOfElem<data->maxSize)newHead+=noOfElem;
	else newHead=noOfElem-(data->maxSize-data->head);
	
	if(newHead<=data->tail)data->head=newHead;
}


_Bool enqueue(PQueueData *data, int i){
	
	int nextPos=data->tail+1;
	
	if(nextPos>=data->maxSize)nextPos=0;
	
	if(nextPos!=data->head){
		data->queue[data->tail]=i;
		data->tail=nextPos;
		return true;
	}
	
	return false;
	
}

	
int isEmpty(PQueueData *data){
	
	if(data->head==data->tail)return true;
	return false;
	
}

int availableSpace(PQueueData *data){
	
	
	return ((data->maxSize-1)-sizeQueue(data));
	
}


void enqueueTab(PQueueData *data, int *tab, unsigned int tabSize){
	
			for(int i=0; i<tabSize; i++){
				enqueue(data, tab[i]);
			}

}

void dequeueTab(PQueueData *data, int *tab, unsigned int tabSize){
	
			for(int i=0; i<tabSize; i++){
				tab[i]=dequeue(data);
			}

}

void dequeueValTab(PQueueData *data, SValue *valTab, unsigned int tabSize){
	
			for(int i=0; i<tabSize; i++){
				valTab[i].acronim=dequeue(data);
				valTab[i].value=dequeue(data);
			}

}
