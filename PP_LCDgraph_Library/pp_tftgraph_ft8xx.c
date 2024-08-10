#include <string.h>
#include "pp_tftgraph_ft8xx.h"
#include "delay.h"
#include "pp_math.h"

void PTFTgraphFT8XXConstruct(PTFTgraph *tft, PExtRam *extram){
	
	tft->data.extram=extram;
//	tft->data.focusCMDadress=0;
	tft->data.init=false;
	
	tft->drawLogo=drawLogo;
	
	tft->init=initTFTgraphFT8XX;
	
	tft->touchTag=ftTouchTag;
	tft->fontHeight=ftFontHeight;
	tft->charWidth=ftCharWidth;
	tft->writePrimitive=ftWritePrimitiveToCMDbuff;
	tft->drawRectangular=drawRectangular;
	tft->drawLine=drawLine;
	tft->drawPoint=drawPoint;
	tft->drawBitmap=drawBitmap;
	tft->writeString=writeString;
	tft->writeChar=writeChar;
	tft->writeNumber=writeNumber;
	tft->drawClock=drawClock;
	tft->drawButton=drawButton;
	tft->drawProgress=drawProgress;
	tft->drawScrollbar=drawScrollbar;
	tft->drawIconButton=drawIconButton;
	tft->drawKeys=drawKeys;
	tft->drawToggle=drawToggle;
	tft->drawSpinner=drawSpinner;
	tft->drawCircleIconButton=drawCircleIconButton;
	tft->drawTextEdit=drawTextEdit;
	tft->drawLineEdit=drawLineEdit;
	tft->drawSpinBox=drawSpinBox;
	
	tft->waitToCMDbuffEmpty=ftWaitToCMDbuffEmpty;
	tft->loadIcon=loadIcon;
	tft->loadIcons=loadIcons;
}

void initTFTgraphFT8XX(PTFTgraphFT8XXData *data){
	
		data->extram->reset(&data->extram->data);
	
	
		/* Set the clk to external clock */
	
//		data->extram->writeHostComm(&data->extram->data, FT_CLKINT, 0);
//		delay_ms(1);
//		data->extram->writeHostComm(&data->extram->data, FT_GPU_SLEEP_M, 0);
//		delay_ms(1);
//		data->extram->writeHostComm(&data->extram->data, FT_CLKSEL, FT_GPU_SYSCLK_48M);
//		delay_ms(1);
		data->extram->writeHostComm(&data->extram->data, FT_GPU_ACTIVE_M, 0);
	

		for(int i=0; i<2000; i++){
			data->extram->seek(&data->extram->data, REG_ID_pos);
			if((data->extram->read(&data->extram->data) & 0xFF)==0x7C){
				data->init=true;
				break;
			}
			delay_ms(1);
		}
		
		if(data->init==true){
			while(1){
				data->extram->seek(&data->extram->data, REG_CPURESET_pos);
				if((data->extram->read(&data->extram->data) & 0xFFFF)==0x0)break;
				delay_ms(1);
			}
			
			/*Set requested registers*/
			data->extram->seek(&data->extram->data, REG_HCYCLE_pos);
			data->extram->write(&data->extram->data, FT_DispHCycle);
			
			data->extram->seek(&data->extram->data, REG_HOFFSET_pos);
			data->extram->write(&data->extram->data, FT_DispHOffset);
			
			data->extram->seek(&data->extram->data, REG_HSYNC0_pos);
			data->extram->write(&data->extram->data, FT_DispHSync0);
			
			data->extram->seek(&data->extram->data, REG_HSYNC1_pos);
			data->extram->write(&data->extram->data, FT_DispHSync1);
			
			data->extram->seek(&data->extram->data, REG_VCYCLE_pos);
			data->extram->write(&data->extram->data, FT_DispVCycle);
			
			data->extram->seek(&data->extram->data, REG_VOFFSET_pos);
			data->extram->write(&data->extram->data, FT_DispVOffset);
			
			data->extram->seek(&data->extram->data, REG_VSYNC0_pos);
			data->extram->write(&data->extram->data, FT_DispVSync0);
			
			data->extram->seek(&data->extram->data, REG_VSYNC1_pos);
			data->extram->write(&data->extram->data, FT_DispVSync1);
			
			data->extram->seek(&data->extram->data, REG_SWIZZLE_pos);
			data->extram->write(&data->extram->data, FT_DispSwizzle);
			
			data->extram->seek(&data->extram->data, REG_CSPREAD_pos);
			data->extram->write(&data->extram->data, 0);
			
			data->extram->seek(&data->extram->data, REG_PCLK_POL_pos);
			data->extram->write(&data->extram->data, FT_DispPCLKPol);
			
			data->extram->seek(&data->extram->data, REG_HSIZE_pos);
			data->extram->write(&data->extram->data, FT_DispWidth);
			
			data->extram->seek(&data->extram->data, REG_VSIZE_pos);
			data->extram->write(&data->extram->data, FT_DispHeight);

			data->extram->seek(&data->extram->data, REG_GPIO_DIR_pos);
			int gpioDir=data->extram->read(&data->extram->data);
			data->extram->seek(&data->extram->data, REG_GPIO_DIR_pos);
			data->extram->write(&data->extram->data, 0x83 | gpioDir);

			data->extram->seek(&data->extram->data, REG_GPIO_pos);
			int gpio=data->extram->read(&data->extram->data);
			data->extram->seek(&data->extram->data, REG_GPIO_pos);
			data->extram->write(&data->extram->data, 0x83 | gpio);

			data->extram->seek(&data->extram->data, REG_TOUCH_RZTHRESH_pos);
			data->extram->write(&data->extram->data, 1200);
			
			data->extram->seek(&data->extram->data, REG_PCLK_pos);
			data->extram->write(&data->extram->data, FT_DispPCLK);
			
			data->extram->seek(&data->extram->data, REG_SPI_WIDTH_pos);
			data->extram->write(&data->extram->data, 2);								//wprowadzenie quad spi

			data->extram->setSpiDataMode(&data->extram->data, QUAD_LINE);


			delay_ms(200);
			
			

	//		data->extram->data.focusAdress=RAM_CMD;
	//		data->extram->write(&data->extram->data, 0xffff);
	//		
	//		data->extram->data.focusAdress=RAM_CMD+2;
	//		data->extram->write(&data->extram->data, 0x5555);
			
	//		data->extram->seek(&data->extram->data, RAM_CMD_pos);
	//		data->extram->write(&data->extram->data, 0x5555ffff);
	//		
	//		while(1){
	//			data->extram->seek(&data->extram->data, REG_FREQUENCY_pos);
	//			if(data->extram->read(&data->extram->data)==0x3938700)break;
	//			delay_ms(1);
	//		}
			
			calibrate(data, 0x666666, 0x222222);
		}
		
}

int ftTouchTag(PTFTgraphFT8XXData *data){
	
		data->extram->seek(&data->extram->data, REG_TOUCH_TAG_pos);
		unsigned int curTag=data->extram->read(&data->extram->data);	//pobranie numeru (tagu) elementu aktualnie dotykanego
	
		return curTag;
}

int ftFontHeight(PTFTgraphFT8XXData *data, unsigned int font){
	
		font=trim_pp(font, 34, 16);
	
		data->extram->seek(&data->extram->data, ROM_FONTROOT_PTR_pos);
		unsigned int fontAdress=data->extram->read(&data->extram->data);
		
		data->extram->seek(&data->extram->data, (fontAdress/4)+(37*(font-16))+35);
		unsigned int fontHeight=data->extram->read(&data->extram->data);
	
		return fontHeight;
}

int ftCharWidth(PTFTgraphFT8XXData *data, unsigned int font, char sign){
		unsigned int wordPos=0, bajtPos=0;
	
		font=trim_pp(font, 34, 16);
	
		data->extram->seek(&data->extram->data, ROM_FONTROOT_PTR_pos);
		unsigned int fontAdress=data->extram->read(&data->extram->data);
		
		wordPos=sign/4;
		bajtPos=sign%4;
		
		data->extram->seek(&data->extram->data, (fontAdress/4)+(37*(font-16))+wordPos);
		unsigned int signWidth=data->extram->read(&data->extram->data);
		
		signWidth>>=(8*bajtPos);
		signWidth&= 0xFF;

		return signWidth;
}

int ftFreeSpaceInCMDbuff(PTFTgraphFT8XXData *data){
			data->extram->seek(&data->extram->data, REG_CMDB_SPACE_pos);
			return data->extram->read(&data->extram->data);
}

void ftWaitToCMDbuffEmpty(PTFTgraphFT8XXData *data){
	
//		while(1){
//			data->extram->seek(&data->extram->data, REG_CMD_READ_pos);
//			int regRead=data->extram->read(&data->extram->data);
//			data->extram->seek(&data->extram->data, REG_CMD_WRITE_pos);
//			int regWrite=data->extram->read(&data->extram->data);
//			if(regRead==regWrite){
//				data->focusCMDadress=regWrite;
//				break;
//			}
//		}
		
		
		while(ftFreeSpaceInCMDbuff(data)!=4092)
			;
		
}

void ftWritePrimitiveToCMDbuff(PTFTgraphFT8XXData *data, unsigned int value){
	
//	if(ftFreeSpaceInCMDbuff(data)>=sizeof(unsigned int)){
		
			data->extram->seek(&data->extram->data, REG_CMDB_WRITE_pos);
			data->extram->write(&data->extram->data, value);
		
//		data->extram->seek(&data->extram->data, RAM_CMD_pos+(data->focusCMDadress/sizeof(int)));
//		data->extram->write(&data->extram->data, value);
//		data->focusCMDadress+=sizeof(value);
//		data->focusCMDadress&=0xFFF;
//		data->focusCMDadress = (data->focusCMDadress + 3) & 0xffc;
//		
//		data->extram->seek(&data->extram->data, REG_CMD_WRITE_pos);
//		data->extram->write(&data->extram->data, data->focusCMDadress);
//	}
		
}

unsigned int ftWriteStringToCMDbuff(PTFTgraphFT8XXData *data, const char* str){
	
		unsigned int i=0, word=0;
		while(*str){ 
			
			word|=(*(str++))<<(8*(i%4));

			if((i%4)==3){
				ftWritePrimitiveToCMDbuff(data, word);
				word=0;
			}
			
			i++;
		}
		ftWritePrimitiveToCMDbuff(data, word);
		return i;
}

void ftWriteDataBuffToCMDbuff(PTFTgraphFT8XXData *data, const char* dataBuff, unsigned int sizeBuff){
	
		unsigned int word=0;
		for(unsigned int i=0; i<sizeBuff; i++){ 
			
			word|=(dataBuff[i])<<(8*(i%4));
			if((i%4)==3){
				ftWritePrimitiveToCMDbuff(data, word);
				word=0;
			}
		}
		ftWritePrimitiveToCMDbuff(data, word);
}

unsigned int loadIcon(PTFTgraphFT8XXData *data, sBitmapHeader *bitmapHeader, unsigned int address){
		unsigned int x=0; 

		bitmapHeader->adressToDecompressBitmap=address;

		inflate(data, bitmapHeader);

		ftWaitToCMDbuffEmpty(data);
	
		data->extram->seek(&data->extram->data, REG_CMD_WRITE_pos);
		x=data->extram->read(&data->extram->data);
//		x=data->focusCMDadress;
		getPtr(data, RAM_G);

		data->extram->seek(&data->extram->data, RAM_CMD_pos+(x/4)+1);
//		data->extram->seek(&data->extram->data, RAM_CMD_pos+1);
		address=data->extram->read(&data->extram->data);
		return address;
}

unsigned int loadIcons(PTFTgraphFT8XXData *data, sBitmapHeader *bitmapHeader, unsigned int nrOfBitmaps, unsigned int address){

		for(unsigned int i=0; i<nrOfBitmaps; i++){
			address=loadIcon(data, &bitmapHeader[i], address);

		}			
		return address;
}


void getPtr(PTFTgraphFT8XXData *data, unsigned int result){
         
  ftWritePrimitiveToCMDbuff(data, CMD_GETPTR);
  ftWritePrimitiveToCMDbuff(data, result);
     
}

void inflate(PTFTgraphFT8XXData *data, sBitmapHeader *bitmapHeader){
 
	ftWritePrimitiveToCMDbuff(data, CMD_INFLATE);
  ftWritePrimitiveToCMDbuff(data, bitmapHeader->adressToDecompressBitmap);
	ftWriteDataBuffToCMDbuff(data, bitmapHeader->compressedBitmap, bitmapHeader->fileSize);

}

void calibrate(PTFTgraphFT8XXData *data, unsigned int fgColor, unsigned int bgColor){
		extern sBitmapHeader touchScreenBitmapHeader;
	
		loadIcon(data, &touchScreenBitmapHeader, RAM_G);
	
		ftWritePrimitiveToCMDbuff(data, CMD_DLSTART);
		ftWritePrimitiveToCMDbuff(data, CLEAR_COLOR_HEX(0xFFFFFF));
		ftWritePrimitiveToCMDbuff(data, CLEAR(1,1,1));
		ftWritePrimitiveToCMDbuff(data, VERTEX_FORMAT(0));
		
		
		drawBitmap(data, (PXY){(FT_DispWidth-touchScreenBitmapHeader.Width)/2, (FT_DispHeight-touchScreenBitmapHeader.Height)/2}, &touchScreenBitmapHeader, 0x000000);
		setFgColor(data, fgColor);
		setBgColor(data, bgColor);
		ftWritePrimitiveToCMDbuff(data, CMD_CALIBRATE);
		ftWritePrimitiveToCMDbuff(data, 0);
		
		ftWaitToCMDbuffEmpty(data);
	
}

void setFgColor(PTFTgraphFT8XXData *data, unsigned int color){
	
		ftWritePrimitiveToCMDbuff(data, CMD_FGCOLOR);
		ftWritePrimitiveToCMDbuff(data, color);
	
}

void setBgColor(PTFTgraphFT8XXData *data, unsigned int color){
	
		ftWritePrimitiveToCMDbuff(data, CMD_BGCOLOR);
		ftWritePrimitiveToCMDbuff(data, color);
	
}

void setGradColor(PTFTgraphFT8XXData *data, unsigned int color){
	
		ftWritePrimitiveToCMDbuff(data, CMD_GRADCOLOR);
		ftWritePrimitiveToCMDbuff(data, color);
	
}

unsigned int setFont(PTFTgraphFT8XXData *data, unsigned int font){
		unsigned int newFont=0;
		
		trim_pp(font, 34, 16);
		newFont=font;
	
		if(newFont>=32){
			newFont-=32;
			ftWritePrimitiveToCMDbuff(data, CMD_ROMFONT);
			ftWritePrimitiveToCMDbuff(data, newFont);
			ftWritePrimitiveToCMDbuff(data, font);
		}
	
		return newFont;
}


void drawRectangular(PTFTgraphFT8XXData *data, PXY startPoint, PXY endPoint, unsigned int color, unsigned int lineWidth){
	
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, LINE_WIDTH(lineWidth));
		ftWritePrimitiveToCMDbuff(data, BEGIN(RECTS) );
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(startPoint.x,startPoint.y));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(endPoint.x,endPoint.y));
		ftWritePrimitiveToCMDbuff(data, END());
	
}


void drawLine(PTFTgraphFT8XXData *data, PXY startPoint, PXY endPoint, unsigned int color, unsigned int lineWidth){
	
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, LINE_WIDTH(lineWidth));
		ftWritePrimitiveToCMDbuff(data, BEGIN(LINES));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(startPoint.x,startPoint.y));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(endPoint.x,endPoint.y));
		ftWritePrimitiveToCMDbuff(data, END());
	
}

void drawPoint(PTFTgraphFT8XXData *data, PXY position, unsigned int color, unsigned int size){
	
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, POINT_SIZE(size*16));
		ftWritePrimitiveToCMDbuff(data, BEGIN(FTPOINTS));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(position.x,position.y));
		ftWritePrimitiveToCMDbuff(data, END());
	
}

void drawBitmap(PTFTgraphFT8XXData *data, PXY position, sBitmapHeader *bitmapDesc, unsigned int color){
         
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, BITMAP_SOURCE(bitmapDesc->adressToDecompressBitmap));
		ftWritePrimitiveToCMDbuff(data, BITMAP_LAYOUT(bitmapDesc->Format, bitmapDesc->Stride, bitmapDesc->Height));
		ftWritePrimitiveToCMDbuff(data, BITMAP_SIZE(NEAREST, BORDER, BORDER, bitmapDesc->Width, bitmapDesc->Height));
		ftWritePrimitiveToCMDbuff(data, BEGIN(BITMAPS));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(position.x, position.y));
		ftWritePrimitiveToCMDbuff(data, END());
     
}


void writeString(PTFTgraphFT8XXData *data, PXY startPoint, unsigned int font, unsigned int options, const char* str, unsigned int color){	//str 91
	
		font=setFont(data, font);
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, CMD_TEXT);
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)startPoint.y<<16)|(startPoint.x & 0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)options<<16)|(font&0xffff)));
		ftWriteStringToCMDbuff(data, str);
}

void writeFromString(PTFTgraphFT8XXData *data, PXY startPoint, unsigned int font, unsigned int options, const char* str, unsigned int num, unsigned int color){

	char strToDisplay[num+1];

	for(unsigned int i=0; i<num+1; i++){	
		strToDisplay[i]=0;
	}
	
	strncpy(strToDisplay, str, num);
	
	writeString(data, startPoint, font, options, strToDisplay, color);
	
}


void writeChar(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, char c, unsigned int color){
	
		font=setFont(data, font);
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, CMD_TEXT);
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)options<<16)|(font&0xffff)));
		ftWritePrimitiveToCMDbuff(data, c);
	
}

void writeNumber(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, int n, unsigned int color){

		font=setFont(data, font);
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, CMD_NUMBER);
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)options<<16)|(font&0xffff)));
		ftWritePrimitiveToCMDbuff(data, n);
}

void drawClock(PTFTgraphFT8XXData *data, PXY position, unsigned int r, unsigned int options, unsigned int h, unsigned int m, unsigned int s, unsigned int ms, unsigned int color, unsigned int bgColor){
    
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color)); 
		if(options!=OPT_NOBACK)setBgColor(data, bgColor);
		ftWritePrimitiveToCMDbuff(data, CMD_CLOCK);
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)options<<16)|(r&0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)m<<16)|(h&0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)ms<<16)|(s&0xffff)));
     
}

void drawButton(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int font, unsigned int options, const char* str, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int gradColor){
      
	font=setFont(data, font);
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));	
	ftWritePrimitiveToCMDbuff(data, TAG(tag));	
	ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color)); 
	setFgColor(data, fgColor);	
	setGradColor(data, gradColor);	
  ftWritePrimitiveToCMDbuff(data, CMD_BUTTON);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
	ftWritePrimitiveToCMDbuff(data, (((unsigned int)h<<16)|(w&0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)options<<16)|(font&0xffff)));
	ftWriteStringToCMDbuff(data, str);
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(0));
     
}

void drawProgress(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, unsigned int val, unsigned int range, unsigned int color, unsigned int bgColor){
        
	ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color)); 
	setBgColor(data, bgColor);
  ftWritePrimitiveToCMDbuff(data, CMD_PROGRESS);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)h<<16)|(w&0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)val<<16)|(options&0xffff)));
  ftWritePrimitiveToCMDbuff(data, range);
     
}

void drawScrollbar(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, unsigned int val, unsigned int size, unsigned int range, unsigned int tag, unsigned int fgColor, unsigned int bgColor){
     
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));
	ftWritePrimitiveToCMDbuff(data, TAG(tag));	
	setFgColor(data, fgColor);
	setBgColor(data, bgColor);
  ftWritePrimitiveToCMDbuff(data, CMD_SCROLLBAR);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)h<<16)|(w&0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)val<<16)|(options&0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)range<<16)|(size&0xffff)));
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(0));
  
}

void drawIconButton(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, sBitmapHeader *bitmapHeader, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int gradColor){

		drawButton(data, position, w, h, 30, options, "", tag, color, fgColor, gradColor);
		drawBitmap(data, (PXY){position.x+((w-bitmapHeader->Width)/2), (position.y+(h-bitmapHeader->Height)/2)}, bitmapHeader, color);

}

void drawCircleIconButton(PTFTgraphFT8XXData *data, PXY position, unsigned int size, sBitmapHeader *bitmapHeader, unsigned int tag, unsigned int color, unsigned int bitmapColor){

		ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));
		ftWritePrimitiveToCMDbuff(data, TAG(tag));	
		drawPoint(data, position, color, size);
		drawBitmap(data, (PXY){position.x-(bitmapHeader->Width/2), position.y-(bitmapHeader->Height/2)}, bitmapHeader, bitmapColor);
		ftWritePrimitiveToCMDbuff(data, TAG_MASK(0));

}

void drawKeys(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int font, unsigned int options, const char* str, unsigned int color, unsigned int fgColor, unsigned int gradColor){
	
	font=setFont(data, font);
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));
	ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color)); 
	setFgColor(data, fgColor);	
	setGradColor(data, gradColor);	
	ftWritePrimitiveToCMDbuff(data, CMD_KEYS);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
	ftWritePrimitiveToCMDbuff(data, (((unsigned int)h<<16)|(w&0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)options<<16)|(font&0xffff)));
  ftWriteStringToCMDbuff(data, str);
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(0));
     
}

void drawToggle(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int font, unsigned int options, unsigned int state, const char* str, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int bgColor){  

	font=setFont(data, font);
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));
	ftWritePrimitiveToCMDbuff(data, TAG(tag));	
	ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color)); 
	setFgColor(data, fgColor);	
	setBgColor(data, bgColor);	
  ftWritePrimitiveToCMDbuff(data, CMD_TOGGLE);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)font<<16)|(w&0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)state<<16)|options));
  ftWriteStringToCMDbuff(data, str);  
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(0));
}

void drawSpinner(PTFTgraphFT8XXData *data, PXY position, unsigned int style, unsigned int scale, unsigned int color){    
	ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color)); 	
  ftWritePrimitiveToCMDbuff(data, CMD_SPINNER);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)scale<<16)|(style&0xffff)));
    
}

void drawLineEdit(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, const char* str, unsigned int maxSignsToDisplay, unsigned int cursor, bool cursorVisible, unsigned int tag){   
	unsigned int fontHeight=ftFontHeight(data, font);
	unsigned int signWidth=ftCharWidth(data, font, '0');
	
	if(options==OPT_RIGHTX)position.x-=(maxSignsToDisplay*signWidth);

	
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));
	ftWritePrimitiveToCMDbuff(data, TAG(tag));	
	drawRectangular(data, position, (PXY){position.x+(maxSignsToDisplay*signWidth),position.y+fontHeight}, 0xFFFFFF, 64); 
	writeFromString(data, position, font, 0, str, maxSignsToDisplay, 0x000000);
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(0));
	
	
	if(cursorVisible){
		for(unsigned int i=0; str[i]!='\0' && i<cursor && i<maxSignsToDisplay; i++){
				
			position.x+=ftCharWidth(data, font, str[i]);
		}
		
		drawRectangular(data, position, (PXY){position.x+1, position.y+fontHeight}, 0x000000, 16);
	}
	
    
}

void drawTextEdit(PTFTgraphFT8XXData *data, PXY position, unsigned int font, const char (*str)[64], unsigned int strRows, unsigned int maxRows, unsigned int maxSignsInLine, PXY cursor, bool cursorVisible, unsigned int tag){   
	unsigned int fontHeight=ftFontHeight(data, font);
	unsigned int signWidth=ftCharWidth(data, font, '0');
	PXY pos=position;
	
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));
	ftWritePrimitiveToCMDbuff(data, TAG(tag));	
	drawRectangular(data, position, (PXY){position.x+(maxSignsInLine*signWidth),position.y+(fontHeight*maxRows)}, 0xFFFFFF, 64); 
	
	for(int i=0; i<strRows && i<maxRows; i++){
		writeFromString(data, pos, font, 0, &str[i][0], maxSignsInLine, 0x000000);
		pos.y+=fontHeight;
	}	
	
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(0));
	
	
	if(cursorVisible){
		for(unsigned int i=0; str[cursor.y][i]!='\0' && i<cursor.x; i++){
				
			position.x+=ftCharWidth(data, font, str[cursor.y][i]);
		}
		
		position.y+=(fontHeight*cursor.y);
		drawRectangular(data, position, (PXY){position.x+1, position.y+fontHeight}, 0x000000, 16);
	}
	
    
}

void drawSpinBox(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, const char* str, unsigned int maxSignsToDisplay, unsigned int tagPlus, unsigned int tagMinus, unsigned int color, unsigned int fgColor, unsigned int gradColor){   
	unsigned int fontHeight=ftFontHeight(data, font);
	unsigned int signWidth=ftCharWidth(data, font, '0');
	unsigned int curTag=ftTouchTag(data);
	
	unsigned int buttonWidthHeight=fontHeight+10;
	unsigned int buttonMargin=10;
	
	if(options==OPT_RIGHTX)position.x-=(2*buttonWidthHeight+2*buttonMargin+maxSignsToDisplay*signWidth);
	
	drawButton(data, position, buttonWidthHeight, buttonWidthHeight, font, (curTag==tagMinus)?OPT_FLAT:0, "-", tagMinus, color, fgColor, gradColor);
	
	position.x+=buttonWidthHeight+buttonMargin;
	drawRectangular(data, (PXY){position.x,position.y+5}, (PXY){position.x+(maxSignsToDisplay*signWidth),position.y+fontHeight+5}, 0xFFFFFF, 64); 
	writeString(data, (PXY){position.x,position.y+5}, font, 0, str, 0x000000);
	
	position.x+=(maxSignsToDisplay*signWidth)+buttonMargin;
	drawButton(data, position, buttonWidthHeight, buttonWidthHeight, font, (curTag==tagPlus)?OPT_FLAT:0, "+", tagPlus, color, fgColor, gradColor);
    
}


void drawLogo(PTFTgraphFT8XXData *data){   
	extern sBitmapHeader logoBitmapHeader;
	
	loadIcon(data, &logoBitmapHeader, RAM_G);	
	
	ftWritePrimitiveToCMDbuff(data, CMD_DLSTART);
	ftWritePrimitiveToCMDbuff(data, CLEAR_COLOR_HEX(0xFFFFFF));
	ftWritePrimitiveToCMDbuff(data, CLEAR(1,0,1));	
	ftWritePrimitiveToCMDbuff(data, VERTEX_FORMAT(0));
	
	drawBitmap(data, (PXY){(FT_DispWidth-logoBitmapHeader.Width)/2, (FT_DispHeight-logoBitmapHeader.Height)/2}, &logoBitmapHeader, 0x000000);

	ftWritePrimitiveToCMDbuff(data, DISPLAY());
	ftWritePrimitiveToCMDbuff(data, CMD_SWAP);

	ftWaitToCMDbuffEmpty(data);
	
	delay_ms(3000);
	
	ftWritePrimitiveToCMDbuff(data, CMD_DLSTART);
	ftWritePrimitiveToCMDbuff(data, CLEAR_COLOR_HEX(0xFFFFFF));
	ftWritePrimitiveToCMDbuff(data, CLEAR(1,0,1));	

	ftWritePrimitiveToCMDbuff(data, DISPLAY());
	ftWritePrimitiveToCMDbuff(data, CMD_SWAP);

	ftWaitToCMDbuffEmpty(data);
	
}