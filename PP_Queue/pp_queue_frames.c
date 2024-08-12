#include <string.h>
#include "pp_queue_frames.h"
#include "pstring.h"


void enqueueBasicFrame(PQueueWithMutex *queue, int tag, int source){
		int auxTag[3];
		
		auxTag[0]=source;
		auxTag[1]=tag;
		auxTag[2]=0;
	
		queue->enqueueTab(&queue->data, auxTag, 3);
}

void enqueueValTabFrame(PQueueWithMutex *queue, SValue *valTab, unsigned int tabSize, int tag, int source){
		int auxTag[32];
		int freeSpace=(sizeof(auxTag)/sizeof(int))-3;
		
		auxTag[0]=source;
		auxTag[1]=tag;
		auxTag[2]=(tabSize<freeSpace)?tabSize:freeSpace;
	
		for(int i=0; i<auxTag[2]; i++){
			
			auxTag[2*i+3]=valTab[i].acronim;
			auxTag[2*i+4]=valTab[i].value;
			
		}
	
		queue->enqueueTab(&queue->data, auxTag, 3+(2*auxTag[2]));
}


void enqueueParamsListFrame(PQueueWithMutex *queue, PConstParamsList *list, int tag, int source){
		int auxTag[32];
		int freeSpace=(sizeof(auxTag)/sizeof(int))-3;
		
		auxTag[0]=source;
		auxTag[1]=tag;
		auxTag[2]=(list->data.size<freeSpace)?list->data.size:freeSpace;
		
		for(int i=0; i<auxTag[2]; i++){
			
			auxTag[2*i+3]=list->data.par[i].acronim;
			auxTag[2*i+4]=list->data.par[i].value;
			
		}
		queue->enqueueTab(&queue->data, auxTag, 3+(2*auxTag[2]));
}

char* dequeueStringFrame(PQueueWithMutex *queue, char *string, int noOfSignToReceive){
	
		PString str;
		PStringConstruct(&str);

		SValue receiveValTab[noOfSignToReceive];
		if(queue->dequeueValTab(&queue->data, receiveValTab, noOfSignToReceive)){	
			for(int i=0; i<noOfSignToReceive; i++){
				str.pushBack(string, noOfSignToReceive, receiveValTab[i].value);
			}	
		}	
		
		return string;
}

void enqueueStringFrame(PQueueWithMutex *queue, char *str, int tag, int source){
		int auxTag[512];
		int freeSpace=((sizeof(auxTag)/sizeof(int))-3)/2;
		
		auxTag[0]=source;
		auxTag[1]=tag;
		auxTag[2]=(strlen(str)<freeSpace)?strlen(str):freeSpace;
		
		for(int i=0; i<auxTag[2]; i++){
			
			auxTag[2*i+3]=0;
			auxTag[2*i+4]=str[i];
			
		}
		queue->enqueueTab(&queue->data, auxTag, 3+(2*auxTag[2]));
}
