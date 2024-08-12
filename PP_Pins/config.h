#ifndef _CONFIG_H
	#define _CONFIG_H
	
	#if defined(PP1_PP2_PLATFORM)
		#include "pp1_pp2_config.h"
	#elif defined(PP16_PLATFORM)
		#include "pp16_config.h"
	#endif

#endif
