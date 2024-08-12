#include <string.h>
#include "pp_queue_with_rtx_mutex.h"


int sizeQueueWithMutex(PQueueWithMutexData *data){
	
	return osMessageQueueGetCount(data->queue);
	
}


void skipPartOfQueueWithMutex(PQueueWithMutexData *data, int noOfElem){
	
	if(osMessageQueueGetCount(data->queue)>=noOfElem){
		int sign=0;
		for(int i=0; i<noOfElem; i++){
			osMessageQueueGet(data->queue, &sign, NULL, 0);
		}

	}		
}


int isEmptyQueueWithMutex(PQueueWithMutexData *data){
	
	
	
	return (osMessageQueueGetCount(data->queue)==0)?true:false;	


}

int availableSpaceQueueWithMutex(PQueueWithMutexData *data){
	
	return osMessageQueueGetSpace	(data->queue);	

}




bool dequeueWithMutex(PQueueWithMutexData *data, int *getData){
	bool ans=false;
	
	if(osMutexAcquire(data->mutex, osWaitForever)==osOK){
		if(osMessageQueueGet(data->queue, getData, NULL, 0)==osOK) ans=true;
		osMutexRelease(data->mutex);
	}
	
	return ans;
}

bool enqueueWithMutex(PQueueWithMutexData *data, int i){
	bool ans=false;
	
	
	if(osMutexAcquire(data->mutex, osWaitForever)==osOK){
		if(osMessageQueuePut(data->queue, &i, 0, 0)==osOK) ans=true;
		osMutexRelease(data->mutex);
	}
	
	return ans;
}


bool enqueueTabWithMutex(PQueueWithMutexData *data, int *tab, unsigned int tabSize){
	
	bool ans=false;
	if(osMessageQueueGetSpace(data->queue)>=tabSize){
		if(osMutexAcquire(data->mutex, osWaitForever)==osOK){
			for(int i=0; i<tabSize; i++){
				osMessageQueuePut(data->queue, &tab[i], 0, 0);
			}
			ans=true;
		}
		
	}
	return ans;
}

bool dequeueTabWithMutex(PQueueWithMutexData *data, int *tab, unsigned int tabSize){
	bool ans=false;
	
	if(osMessageQueueGetCount(data->queue)>=tabSize){
		if(osMutexAcquire(data->mutex, osWaitForever)==osOK){
			for(int i=0; i<tabSize; i++){
				osMessageQueueGet(data->queue, &tab[i], NULL, 0);
			}
			ans=true;
		}
			
	}
	return ans;
}

bool dequeueValTabWithMutex(PQueueWithMutexData *data, SValue *valTab, unsigned int tabSize){
	
	bool ans=false;
	
	if(osMessageQueueGetCount(data->queue)>=(2*tabSize)){
		if(osMutexAcquire(data->mutex, osWaitForever)==osOK){
			for(int i=0; i<tabSize; i++){
				osMessageQueueGet(data->queue, &valTab[i].acronim, NULL, 0);
				osMessageQueueGet(data->queue, &valTab[i].value, NULL, 0);
			}
			ans=true;
		}
			
	}
	
	return ans;
}
