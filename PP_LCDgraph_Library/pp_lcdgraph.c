#include "pp_lcdgraph.h"


void PLCDgraphConstruct(PLCDgraph *lcd){
	
			lcd->data.posX=0;
			lcd->data.posY=0;
			lcd->data.posGraphX=0;
			lcd->data.posGraphX=0;
	
			lcd->data.typeOfFont=BASE_FONT;
			lcd->data.bold=false;
			lcd->data.blink=false;
			lcd->data.reverse=false;
			lcd->data.textAtribiuteModeEnable=false;
			lcd->data.cursorEnable=false;
	
			lcd->setTextAtribiuteModeEnable=LCDsetTextAtribiuteModeEnable;
			lcd->setTextAtribiuteOnTheArea=LCDsetTextAtribiuteOnTheArea;
			lcd->clearTextAtribiuteOnTheArea=LCDclearTextAtribiuteOnTheArea;
			lcd->setCursorEnable=LCDsetCursorEnable;
			lcd->seekCursor=LCDseekCursor;
	
			lcd->intro=LCDintro;
			lcd->reset=LCDreset;
	
			lcd->seek=LCDgoto;
			lcd->seekPage=LCDgotoPage;
			lcd->clear=LCDclearFont;
			lcd->clearPages=LCDclearPages;
			
			lcd->write=LCDwrite;
			lcd->writeChar=LCDwriteChar;
			lcd->writeFromString=LCDwriteFromString;
	//		lcd->writeWrap=LCDwriteWrap;
	
	
			lcd->drawIcon=send_icon_ram;
}

void LCDreset(LCDdata *data, unsigned int noOfPageToClear){
	
		LCDclearPages(data, 0, noOfPageToClear);
		LCDgotoPage(data, 0);
		LCDsetTextAtribiuteModeEnable(data, false);
		LCDseekCursor(data, L_KOLUMN_LCD, 0);
		LCDsetCursorEnable(data, false);
	
}

void LCDclearFont(LCDdata *data, unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height){
	
	if(data->typeOfFont==BASE_FONT){
		LCDclear(data, x_start, y_start, width, height);
	}else{
		LCDclearFontGraph(data, x_start, y_start, width, height);
	}
	
}


void LCDwriteChar(LCDdata* data, char s) {

	if(data->typeOfFont==BASE_FONT){
		LCDputchar(data, s);
	}else{
		LCDputcharGraph(data, s);
	}

}



void LCDwrite(LCDdata* data, const char *s) {

	if(data->typeOfFont==BASE_FONT){
		while(*s){ 
			LCDputchar(data, *(s++));
		}
	}else{
		while(*s){ 
			LCDputcharGraph(data, *(s++));
		}
	}

}

void LCDwriteFromString(LCDdata* data, const char *s, unsigned int num) {

	int numOfWriteChars=0;
	
	while(*s){ 
		if(numOfWriteChars>=num)break;
		if(data->typeOfFont==BASE_FONT){
			LCDputchar(data, *(s++));
		}else{
			LCDputcharGraph(data, *(s++));
		}
		numOfWriteChars++;
	}

}

//unsigned int LCDwriteWrap(LCDdata* data, const char *s) {
//		unsigned int noOfWrap=0;

//	if(data->typeOfFont==BASE_FONT){
//		while(*s){ 
//			if(LCDputcharWrap(data, *(s++)))noOfWrap++;
//		}
//	}else{
//		while(*s){ 
//			if(LCDputcharGraphWrap(data, *(s++)))noOfWrap++;
//		}
//	}
//	return noOfWrap;
//}

