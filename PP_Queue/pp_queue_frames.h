#ifndef _PP_QUEUE_FRAMES_H
	#define _PP_QUEUE_FRAMES_H

	#ifdef __cplusplus
	extern "C" {
	#endif

		#include "pp_paramlist.h"
		#include "pp_queue_with_mutex.h"

	void enqueueBasicFrame(PQueueWithMutex *queue, int tag, int source);
	void enqueueValTabFrame(PQueueWithMutex *queue, SValue *valTab, unsigned int tabSize, int tag, int source);
	void enqueueParamsListFrame(PQueueWithMutex *queue, PConstParamsList *list, int tag, int source);
	
	char* dequeueStringFrame(PQueueWithMutex *queue, char *string, int noOfSignToReceive);
	void enqueueStringFrame(PQueueWithMutex *queue, char *str, int tag, int source);
		
#ifdef __cplusplus
}
#endif
		
#endif
