#ifndef _PP_CONST_PORTS_LIST_H
	#define _PP_CONST_PORTS_LIST_H

	#ifdef __cplusplus
	extern "C" {
	#endif

		#include <stdbool.h>
		
		#if defined(UNIT_TESTS)
			#include "def_pins_mock.h"
		#else
			#include "def_pins_stm32f4.h"
		#endif

		typedef struct{
			uPortMask *portsMasks;
			int size;
			int maxSize;
		}PPortsData;
		
		
		typedef struct{
			PPortsData data;
			
			void (*create)(PPortsData *data, uPin *pins, int noOfPins);
			void (*clear)(PPortsData *data);
		}PConstPortsList;
		
		void PConstPortsListConstruct(PConstPortsList *list, uPortMask *tab, int maxSize);
		
		void createPConstPortsList(PPortsData *data, uPin *pins, int noOfPins);
		void clearPConstPortsList(PPortsData *data);
		
#ifdef __cplusplus
}
#endif
		
#endif
