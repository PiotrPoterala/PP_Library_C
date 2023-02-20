#include <string.h>
#include "pp_const_ports_masks_list.h"


void PConstPortsListConstruct(PConstPortsList *list, uPortMask *tab, int maxSize){

		list->data.portsMasks=tab;
		list->data.maxSize=maxSize;
		clearPConstPortsList(&list->data);
	
		list->create=createPConstPortsList;
		list->clear=clearPConstPortsList;
			
}


void createPConstPortsList(PPortsData *data, uPin *pins, int noOfPins){
	
		
		for(int i=0; i<noOfPins; i++){
			int j;
			for(j=0; j<data->size; j++){
				if(data->portsMasks[j].port==pins[i].port)break;
				
			}
			
			if(j>=data->size){
				if(data->size+1<data->maxSize){
					data->portsMasks[j].port=pins[i].port;
					data->portsMasks[j].mask=0;
					data->portsMasks[j].clrMask=(1<<pins[i].pin);
					data->size++;
				}
			}else{
				data->portsMasks[j].clrMask|= (1<<pins[i].pin);
			}
		}
	
}


void clearPConstPortsList(PPortsData *data){
			
		
		memset(data->portsMasks, 0, sizeof(uPortMask)*data->maxSize);
		data->size=0;
	
}
