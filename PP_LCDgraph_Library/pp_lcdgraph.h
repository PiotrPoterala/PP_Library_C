#ifndef _PP_LCD_GRAPH_H
	#define _PP_LCD_GRAPH_H 
	
	#include "t6963.h"
	
	#ifdef __cplusplus
	extern "C" {
	#endif

		
		typedef struct{
			LCDdata data;
			
			void (*intro)(LCDdata* data);
			void (*reset)(LCDdata *data, unsigned int noOfPageToClear);
			
			void (*setFont)(LCDdata* data, FontType typeOfFont);
			void (*setTextAtribiuteModeEnable)(LCDdata* data, _Bool enable);
			void (*setReverse)(LCDdata* data, _Bool reverse);
			void (*setBlink)(LCDdata* data, _Bool blink);
			
			void (*writeTextAtribiutesOnTheArea)(LCDdata *data, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);
			void (*setIndependentWriteTextAtribiutes)(LCDdata* data, _Bool indWrite);
			
			void (*clearTextAtribiuteOnTheArea)(LCDdata *data, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);
			
			void (*setCursorEnable)(LCDdata* data, _Bool enable);
			void (*seekCursor)(LCDdata *data, unsigned int cursorX, unsigned int cursorY);
			
			void (*seek)(LCDdata *data, unsigned int lcd_X, unsigned int lcd_Y);
			void (*seekPage)(LCDdata *data, unsigned int page);
			void (*clear)(LCDdata *data, unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height);
			void (*clearPages)(LCDdata *data, unsigned int firstPage, unsigned int lastPage);
			

			void (*write)(LCDdata* data, const char *s);
			void (*writeChar)(LCDdata* data, unsigned char s);
			void (*writeFromString)(LCDdata* data, const char *s, unsigned int num);
	//		unsigned int (*writeWrap)(LCDdata* data, const char *s);
			
			void (*drawIcon)(LCDdata *data, const unsigned char *buffer);
		}PLCDgraph;

		void PLCDgraphConstruct(PLCDgraph *lcd, uPin *ioPins, PPortsData *ioPorts);
		
		void LCDreset(LCDdata *data, unsigned int noOfPageToClear);

		void LCDclearFont(LCDdata *data, unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height);
		void LCDwrite(LCDdata* data, const char *s);
		void LCDwriteChar(LCDdata* data, char s); 
		void LCDwriteFromString(LCDdata* data, const char *s, unsigned int num);
	//	unsigned int LCDwriteWrap(LCDdata* data, const char *s);
		
		
#ifdef __cplusplus
}
#endif
	
#endif
