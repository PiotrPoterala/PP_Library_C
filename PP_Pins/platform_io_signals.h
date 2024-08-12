#ifndef _PLATFORM_IO_SIGNALS_H
	#define _PLATFORM_IO_SIGNALS_H

#include "def_pins_stm32.h"

#if defined(PP1_PP2_PLATFORM)
	#include "pp1_pp2_io_signals.h"
#elif defined(PP1_PP2_PLATFORMrev25_10_18)
  #include "pp1_pp2_io_signals_rev_25_10_18.h"
#elif defined(PP16_PLATFORM)
	#if defined(WEDM)
		#include "pp16_wedm_io_signals.h"
	#else
		#include "pp16_io_signals.h"
	#endif
#endif
	
	enum{
		mZSA=0,
		mOWE,
		mZWARCIE
	};
	
#endif
