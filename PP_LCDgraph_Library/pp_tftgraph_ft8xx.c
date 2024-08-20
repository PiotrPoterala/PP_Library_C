#include <string.h>
#include "pp_tftgraph_ft8xx.h"
#include "delay.h"
#include "pp_math.h"

void PTFTgraphFT8XXConstruct(PTFTgraph *tft, PExtRam *extram){
	
	tft->data.extram=extram;
	tft->data.init=false;
	
	tft->drawLogo=drawLogo;
	
	tft->init=initTFTgraphFT8XX;
	
	tft->touchTag=ftTouchTag;
	tft->fontHeight=ftFontHeight;
	tft->charWidth=ftCharWidth;
	tft->writePrimitive=ftWritePrimitiveToCMDbuff;
	tft->drawRectangular=drawRectangular;
	tft->drawLine=drawLine;
	tft->drawLineStrip=drawLineStrip;
	tft->drawPoint=drawPoint;
	tft->drawBitmap=drawBitmap;
	tft->writeString=writeString;
	tft->writeFromString=writeFromString;
	tft->writeChar=writeChar;
	tft->writeNumber=writeNumber;
	tft->drawClock=drawClock;
	tft->drawGauge=drawGauge;
	tft->drawButton=drawButton;
	tft->drawProgress=drawProgress;
	tft->drawScrollbar=drawScrollbar;
	tft->drawSlider=drawSlider;
	tft->drawDial=drawDial;
	tft->drawIconButton=drawIconButton;
	tft->drawKeys=drawKeys;
	tft->drawToggle=drawToggle;
	tft->animateSpinner=animateSpinner;
	tft->stopAnimateSpinner=stopAnimateSpinner;
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
			
			
			calibrate(data, 0x666666, 0x222222);
		}
		
}

int ftTouchTag(PTFTgraphFT8XXData *data){
	
		data->extram->seek(&data->extram->data, REG_TOUCH_TAG_pos);
		unsigned int curTag=data->extram->read(&data->extram->data);
	
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
	
		
		while(ftFreeSpaceInCMDbuff(data)!=4092)
			;
		
}

void ftWritePrimitiveToCMDbuff(PTFTgraphFT8XXData *data, unsigned int value){
	
			data->extram->seek(&data->extram->data, REG_CMDB_WRITE_pos);
			data->extram->write(&data->extram->data, value);
		
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
		getPtr(data, RAM_G);

		data->extram->seek(&data->extram->data, RAM_CMD_pos+(x/4)+1);
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
		const char touchScreen[] ={120,156,237,210,65,22,2,33,12,3,208,163,123,116,93,184,243,13,133,206,52,105,192,52,75,148,230,43,239,215,219,113,84,243,157,238,22,21,134,125,37,209,116,119,171,48,236,99,89,159,238,166,21,6,101,201,157,233,238,92,163,208,147,172,180,212,151,100,250,41,75,114,205,84,29,249,94,154,146,59,157,244,29,72,61,79,145,233,163,236,224,124,83,217,209,45,153,53,137,78,247,113,172,159,246,58,102,77,226,115,59,176,146,83,28,217,166,103,56,148,20,167,58,214,187,198,223,235,150,196,202,245,179,78,199,204,120,245,9,29,197,183,205,204,24,181,213,113,68,66,173,183,99,135,29,74,177,67,43,118,104,197,14,173,216,161,21,59,180,18,59,238,205,41,142,14,11,202,193,182,32,29,76,137,29,90,18,180,131,37,169,223,137,112,204,111,68,252,118,213,146,149,127,25,243,6,42,111,29,207,78,142,217,48,29,79,238,93,153,29,28,107,146,202,125,118,212,75,52,29,121,137,170,35,43,209,117,228,36,123,57,198,58,101,71,70,162,237,24,73,120,251,170,238,29,75,94,144,125,56,71,124,247,206,142,223,219,119,113,204,37,184,77,232,251,81,18,252,22,142,196,14,45,73,207,235,173,223,195,113,224,37,28,197,149,228,20,71,229,54,214,171,66,75,184,14,148,132,173,192,72,144,239,149,183,183,75,113,181,249,206,246,241,176,28,81,135,231,195,83,32,37,92,5,74,194,87,32,36,61,138,106,73,159,162,202,210,45,120,230,233,238,235,56,142,227,252,101,62,117,128,254,116};
		sBitmapHeader touchScreenBitmapHeader ={ARGB1555, 100, 100, 200, 364,	touchScreen, 0};

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
	
		ftWritePrimitiveToCMDbuff(data, VERTEX_FORMAT(0));
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, LINE_WIDTH(lineWidth));
		ftWritePrimitiveToCMDbuff(data, BEGIN(RECTS) );
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(startPoint.x,startPoint.y));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(endPoint.x,endPoint.y));
		ftWritePrimitiveToCMDbuff(data, END());
	
}


void drawLine(PTFTgraphFT8XXData *data, PXY startPoint, PXY endPoint, unsigned int color, unsigned int lineWidth){
	
		ftWritePrimitiveToCMDbuff(data, VERTEX_FORMAT(0));
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, LINE_WIDTH(lineWidth));
		ftWritePrimitiveToCMDbuff(data, BEGIN(LINES));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(startPoint.x,startPoint.y));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(endPoint.x,endPoint.y));
		ftWritePrimitiveToCMDbuff(data, END());
	
}

void drawLineStrip(PTFTgraphFT8XXData *data, PXY *pointTab, unsigned int pointTabSize, unsigned int color, unsigned int stripType, unsigned int lineWidth){
	
		ftWritePrimitiveToCMDbuff(data, VERTEX_FORMAT(0));
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, LINE_WIDTH(lineWidth));
		ftWritePrimitiveToCMDbuff(data, BEGIN(stripType));
		for(int i=0; i<pointTabSize; i++){
			ftWritePrimitiveToCMDbuff(data, VERTEX2F(pointTab[i].x, pointTab[i].y));
		}
		ftWritePrimitiveToCMDbuff(data, END());
	
}

void drawPoint(PTFTgraphFT8XXData *data, PXY position, unsigned int color, unsigned int size){
	
		ftWritePrimitiveToCMDbuff(data, VERTEX_FORMAT(0));
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
		ftWritePrimitiveToCMDbuff(data, POINT_SIZE(size*16));
		ftWritePrimitiveToCMDbuff(data, BEGIN(FTPOINTS));
		ftWritePrimitiveToCMDbuff(data, VERTEX2F(position.x,position.y));
		ftWritePrimitiveToCMDbuff(data, END());
	
}



void drawBitmap(PTFTgraphFT8XXData *data, PXY position, sBitmapHeader *bitmapDesc, unsigned int color){
         
		ftWritePrimitiveToCMDbuff(data, VERTEX_FORMAT(0));
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

void drawGauge(PTFTgraphFT8XXData *data, PXY position, unsigned int r, unsigned int options, unsigned int major, unsigned int minor, unsigned int val, unsigned int range, unsigned int color, unsigned int bgColor){
    
		ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color)); 
		if(options!=OPT_NOBACK)setBgColor(data, bgColor);
		ftWritePrimitiveToCMDbuff(data, CMD_GAUGE);
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)options<<16)|(r&0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)minor<<16)|(major&0xffff)));
		ftWritePrimitiveToCMDbuff(data, (((unsigned int)range<<16)|(val&0xffff)));
     
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

void drawSlider(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, unsigned int val, unsigned int range, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int bgColor){
     
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));
	ftWritePrimitiveToCMDbuff(data, TAG(tag));	
	ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
	setFgColor(data, fgColor);
	setBgColor(data, bgColor);
  ftWritePrimitiveToCMDbuff(data, CMD_SLIDER);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)h<<16)|(w&0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)val<<16)|(options&0xffff)));
	ftWritePrimitiveToCMDbuff(data, range);
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(0));
  
}

void drawDial(PTFTgraphFT8XXData *data, PXY position, unsigned int r, unsigned int options, unsigned int val, unsigned int tag, unsigned int color, unsigned int fgColor){
     
	ftWritePrimitiveToCMDbuff(data, TAG_MASK(1));
	ftWritePrimitiveToCMDbuff(data, TAG(tag));	
	ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color));
	setFgColor(data, fgColor);
  ftWritePrimitiveToCMDbuff(data, CMD_DIAL);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)options<<16)|(r&0xffff)));
	ftWritePrimitiveToCMDbuff(data, val);
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

void animateSpinner(PTFTgraphFT8XXData *data, PXY position, unsigned int style, unsigned int scale, unsigned int color){    
	ftWritePrimitiveToCMDbuff(data, VERTEX_FORMAT(4));
	ftWritePrimitiveToCMDbuff(data, COLOR_HEX(color)); 	
  ftWritePrimitiveToCMDbuff(data, CMD_SPINNER);
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)position.y<<16)|(position.x & 0xffff)));
  ftWritePrimitiveToCMDbuff(data, (((unsigned int)scale<<16)|(style&0xffff))); 
}

void stopAnimateSpinner(PTFTgraphFT8XXData *data){    
	
  ftWritePrimitiveToCMDbuff(data, CMD_STOP);
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
	const char logoIcon[] ={120,156,237,156,89,146,36,55,14,68,235,230,202,155,75,86,173,173,35,130,216,29,32,43,211,31,62,70,25,36,1,7,72,239,25,153,73,243,231,31,127,50,24,12,6,131,193,96,48,24,140,31,19,95,132,144,183,227,8,159,191,46,65,8,1,179,197,231,175,80,16,66,138,140,250,60,230,111,250,157,16,16,67,62,175,57,156,126,39,164,68,187,207,145,14,167,215,9,73,209,232,243,186,87,233,118,66,32,52,249,28,237,77,122,157,144,2,13,62,239,116,36,189,78,72,2,176,207,253,62,172,252,125,56,189,78,72,8,168,207,109,247,249,220,237,241,49,189,78,136,27,152,207,45,215,229,29,30,201,73,8,89,0,242,185,230,55,140,195,253,217,9,33,55,0,62,159,245,184,167,10,33,228,66,217,231,178,199,250,60,110,123,157,16,242,27,69,159,239,243,184,93,147,16,242,15,5,159,251,29,183,203,235,132,144,95,164,125,126,138,199,233,116,66,76,146,62,63,203,229,87,21,116,58,33,55,82,62,247,248,139,78,39,228,24,18,62,63,213,229,116,58,33,2,97,159,159,236,114,89,19,33,31,77,201,231,207,47,103,132,172,149,144,143,36,232,243,159,224,242,181,211,9,249,96,66,62,255,41,46,95,235,235,98,166,147,9,213,221,156,209,249,71,18,240,185,238,162,243,66,82,141,102,166,143,25,205,157,156,57,137,15,193,237,243,213,188,187,95,56,230,93,116,191,148,153,46,102,52,247,114,242,68,222,156,132,207,159,95,78,141,149,82,60,83,93,204,40,238,228,236,169,188,53,78,159,207,206,55,82,201,247,26,232,115,175,226,78,206,159,204,219,226,242,249,252,108,51,149,180,183,208,217,193,79,243,249,62,247,156,63,155,183,37,232,243,41,242,213,108,167,163,161,207,81,149,79,152,206,155,226,240,249,142,153,214,234,205,58,253,103,249,124,167,119,126,194,124,222,148,67,125,254,85,172,184,122,9,93,111,163,211,227,248,169,239,116,206,207,152,208,91,98,250,252,57,205,153,91,170,223,240,115,95,207,203,232,122,189,29,111,120,71,205,104,245,253,83,122,67,12,159,107,94,233,190,163,122,14,77,253,73,204,189,223,189,190,201,215,218,165,248,109,112,251,252,254,27,21,50,136,92,178,254,115,152,124,187,245,91,65,87,175,158,63,239,62,143,68,245,249,115,138,53,79,91,183,115,255,82,207,248,236,225,180,151,49,249,114,43,115,236,170,95,207,112,214,125,30,74,200,231,25,223,249,111,230,249,13,151,117,213,195,25,76,190,91,169,202,148,107,48,117,230,230,245,70,184,124,126,253,133,138,59,171,239,136,204,247,239,39,189,12,255,116,186,106,233,43,253,10,48,89,78,185,207,99,81,124,46,251,3,19,87,214,223,17,185,229,62,118,51,251,98,181,58,51,26,80,85,144,83,179,206,79,222,81,163,150,109,62,215,58,240,245,150,201,126,253,189,151,201,23,36,85,243,173,118,106,192,101,202,229,210,206,199,95,90,141,70,45,162,207,37,111,96,66,239,33,218,159,85,65,238,101,31,51,47,71,175,103,169,153,213,80,205,148,203,133,120,119,40,26,181,108,241,185,220,93,181,75,43,195,250,247,60,225,123,106,169,23,219,209,163,2,151,41,151,107,117,190,250,222,178,52,106,49,125,158,175,230,85,97,237,65,212,185,127,69,222,78,134,208,29,53,213,243,40,154,86,81,201,148,203,245,60,143,120,111,245,174,192,90,4,159,163,234,217,26,236,61,136,58,114,63,59,8,220,79,99,61,207,174,126,29,184,76,185,108,247,211,190,172,61,183,215,168,101,220,231,30,141,247,125,245,74,242,4,231,241,206,166,187,98,110,23,90,7,46,83,46,219,245,116,36,31,126,90,141,90,12,159,203,89,114,97,171,91,237,172,215,122,126,199,220,76,28,239,108,186,107,86,246,117,235,200,101,202,101,171,221,7,118,94,141,90,70,125,238,237,234,185,187,90,237,249,29,115,51,81,106,55,137,172,89,219,137,83,130,203,148,203,85,191,15,220,188,26,181,44,125,46,123,162,18,222,174,86,251,171,245,158,223,17,247,18,199,63,157,222,154,17,117,59,148,100,50,229,114,33,50,161,230,213,168,101,155,207,163,39,106,245,158,43,136,123,137,226,157,77,127,77,204,110,132,22,92,166,92,46,76,30,204,188,26,181,56,124,238,119,150,22,118,71,250,153,90,197,213,74,245,86,162,120,103,211,95,53,170,113,143,150,168,74,84,174,122,150,44,141,90,84,159,75,213,227,97,245,227,57,87,169,185,90,169,222,74,12,239,108,38,170,98,79,212,212,160,242,160,114,101,65,100,105,212,50,226,115,189,27,239,73,92,205,251,183,126,188,58,103,234,98,79,212,212,96,178,228,53,226,58,61,90,203,194,231,178,31,114,97,117,227,63,141,58,119,255,218,141,127,54,19,117,123,78,101,245,32,114,84,20,226,186,172,103,106,212,50,238,243,202,105,220,185,235,215,110,188,179,153,169,219,115,42,171,167,158,161,166,16,215,101,61,19,114,226,183,76,166,207,35,222,178,167,95,59,143,171,122,253,218,139,87,229,76,229,220,41,207,185,46,61,186,174,170,62,100,151,213,76,141,90,154,125,174,245,145,201,129,58,115,93,233,196,59,155,169,202,189,39,59,242,198,223,89,86,83,149,106,174,70,45,173,62,151,43,103,179,160,234,94,87,250,240,106,156,170,157,63,233,61,27,207,139,8,140,38,100,127,135,105,81,124,254,220,95,155,61,38,83,180,174,182,7,53,83,9,255,108,166,106,207,156,142,101,173,7,74,19,182,191,163,180,140,249,28,117,143,209,27,215,246,161,102,186,38,162,114,170,250,204,233,88,214,106,224,52,97,251,219,171,229,150,173,205,231,114,205,106,182,200,141,235,59,113,51,93,17,209,57,83,187,122,62,146,33,146,21,245,50,170,154,234,212,178,53,106,105,242,185,92,177,158,207,127,219,86,62,220,76,227,181,123,169,79,188,67,251,105,122,238,154,118,103,107,212,210,226,115,185,222,228,141,218,217,112,51,245,215,158,0,51,113,188,254,115,148,172,53,33,115,101,178,97,187,187,100,107,240,185,86,111,234,86,125,217,176,47,198,83,125,6,204,196,241,29,156,161,66,214,132,204,149,201,214,168,165,221,231,94,229,200,187,245,230,194,191,26,189,250,12,241,27,171,220,239,180,50,52,200,220,213,92,141,90,224,62,151,171,249,180,87,111,56,162,178,227,237,76,190,209,184,2,68,236,81,214,5,178,70,53,87,163,22,240,63,39,35,215,138,105,207,220,116,92,103,199,27,154,127,169,126,5,152,64,43,219,11,82,75,53,83,163,22,168,207,53,213,113,237,158,211,149,183,218,241,210,188,179,233,35,59,145,252,61,215,180,237,6,167,166,158,169,81,11,244,223,87,211,106,101,244,107,39,235,47,21,255,214,188,147,233,164,54,151,204,61,215,180,237,6,167,166,158,169,81,11,208,231,90,165,236,203,209,246,85,223,41,250,173,197,187,195,131,86,128,205,183,119,54,62,77,152,76,199,105,129,253,255,201,232,138,189,97,245,142,168,241,236,11,65,164,167,62,240,10,144,25,119,79,199,163,9,147,7,163,5,147,231,23,32,159,91,122,35,225,80,93,172,115,61,141,193,223,79,31,29,245,145,93,237,157,142,87,83,61,203,129,90,32,62,183,212,70,67,83,142,168,116,61,141,192,223,75,39,61,10,112,89,119,207,167,79,19,166,167,70,45,170,207,95,98,117,77,75,204,115,190,87,36,173,85,178,227,94,90,164,147,62,186,20,224,242,238,157,143,95,83,84,21,170,163,70,45,14,159,91,110,242,104,141,135,156,181,90,237,126,178,10,170,99,239,44,98,58,16,160,50,119,233,171,80,155,249,234,252,145,90,202,62,247,41,205,132,148,185,90,81,207,23,5,217,177,111,18,49,29,8,80,185,187,244,85,168,205,29,219,15,250,5,252,198,210,231,95,183,157,222,250,213,247,172,101,247,124,143,100,69,220,75,71,207,246,148,35,58,80,96,178,119,42,204,114,213,18,81,135,239,166,81,139,225,243,151,152,229,89,185,246,150,173,252,158,239,145,172,152,155,233,232,218,154,115,68,7,10,76,246,78,133,89,238,90,60,26,43,247,180,73,139,203,231,190,123,142,190,94,59,244,41,228,234,174,251,203,131,239,218,154,131,95,5,142,188,50,43,203,110,180,183,129,190,165,141,90,4,159,127,57,234,201,26,113,161,79,33,83,249,126,166,74,79,223,218,164,253,42,144,32,42,116,107,204,176,210,210,113,67,115,90,150,106,76,159,191,132,122,178,66,100,200,53,178,213,175,39,234,116,117,46,207,218,175,1,9,162,70,183,198,12,184,55,117,180,150,164,207,123,208,85,123,87,236,41,32,251,136,220,65,54,114,26,208,84,171,100,187,235,69,83,130,184,155,67,180,136,62,255,186,157,158,186,27,185,142,214,85,204,49,200,62,188,149,43,145,83,128,166,94,103,66,101,20,91,203,212,124,91,181,56,124,254,122,252,118,228,45,32,213,209,122,139,248,229,156,55,70,246,243,179,254,204,73,115,160,207,37,39,234,127,138,209,231,36,3,125,174,57,189,151,30,159,207,246,64,126,6,244,185,254,223,232,51,33,77,97,53,11,250,156,196,161,207,175,149,159,74,246,251,220,94,167,203,137,14,125,126,173,252,84,114,154,207,117,117,235,126,16,104,138,158,59,244,60,207,111,89,45,246,158,152,18,121,125,189,91,191,41,171,138,175,15,249,215,42,151,85,73,171,53,67,163,22,195,231,207,137,87,92,27,13,121,10,235,61,86,166,158,41,90,239,217,243,230,255,223,165,127,153,83,98,213,209,119,91,119,169,87,201,76,75,174,225,159,200,110,26,181,132,125,174,185,9,29,210,12,162,123,94,143,117,36,118,190,231,244,164,93,47,227,139,85,69,223,189,186,71,105,159,149,199,183,59,179,246,188,49,121,215,235,242,91,175,161,231,65,191,138,12,141,90,76,159,63,221,129,112,176,39,228,25,200,251,180,29,93,51,180,51,62,125,177,58,177,122,185,17,181,81,29,186,18,127,30,109,119,124,237,174,201,154,214,235,183,223,177,250,247,60,214,206,126,26,181,132,124,254,90,124,233,10,89,131,182,83,94,239,155,161,239,45,217,39,36,189,17,29,250,254,245,92,61,251,180,117,109,119,124,45,162,241,62,47,121,151,76,223,187,136,211,168,197,225,243,213,155,171,251,216,10,121,2,250,94,105,173,239,54,53,221,255,239,208,126,255,254,245,223,181,235,175,184,18,143,14,93,137,94,199,183,59,190,22,213,120,255,207,213,62,107,38,93,47,35,74,163,22,151,207,159,46,201,186,215,23,90,255,214,254,245,90,231,109,218,57,87,26,229,93,191,235,204,232,149,251,140,122,72,171,224,219,29,95,139,106,244,221,172,62,147,174,151,17,165,81,75,216,231,175,197,23,108,104,181,61,103,116,173,120,236,172,79,95,172,78,220,95,174,47,119,68,211,122,82,222,211,210,186,182,59,190,182,190,79,237,180,247,110,181,122,93,111,35,70,163,22,167,207,45,247,160,194,170,236,57,247,252,218,123,147,177,23,166,247,41,255,149,71,135,165,105,53,21,93,137,84,233,254,10,180,157,209,181,167,74,235,180,124,187,175,203,95,175,119,244,190,142,8,141,90,220,62,215,253,83,15,187,170,255,180,164,178,7,187,19,95,175,171,149,136,106,79,21,191,146,72,30,93,83,124,205,219,201,253,68,70,167,175,143,25,26,181,164,124,14,87,225,168,24,113,250,218,229,93,170,81,111,105,237,243,156,146,218,174,216,159,5,86,173,236,154,173,209,147,205,223,135,92,107,138,51,124,62,61,147,136,203,37,61,39,221,34,33,219,8,249,124,206,55,49,143,75,122,232,114,66,126,17,244,249,132,119,50,30,95,169,161,203,9,249,135,176,207,59,253,147,117,248,74,13,93,78,200,127,36,124,46,121,168,234,210,122,88,10,9,249,80,82,62,63,211,233,150,58,66,62,150,164,207,239,158,94,127,165,203,9,57,130,180,207,37,167,239,240,186,173,137,144,143,166,224,243,83,156,110,235,33,228,195,41,249,252,233,104,121,101,214,227,175,47,66,200,127,20,125,254,141,236,175,41,143,211,229,132,168,0,124,174,187,140,30,39,100,59,16,159,175,220,108,173,35,28,110,215,37,132,124,193,124,254,141,237,57,164,195,233,113,66,220,0,125,190,246,177,111,87,204,225,222,74,132,144,95,64,125,254,141,215,169,218,238,248,9,66,136,2,220,231,223,68,189,187,51,43,33,31,64,139,207,191,137,253,239,240,153,76,132,124,40,109,62,255,38,247,119,224,153,51,132,16,133,86,159,255,141,223,237,116,56,33,45,12,248,252,111,232,112,66,182,49,230,243,127,161,191,9,25,103,220,231,191,67,119,19,50,194,86,159,19,66,70,184,251,156,193,96,48,24,12,6,131,193,96,48,24,12,198,174,248,11,4,85,191,178};
	sBitmapHeader logoBitmapHeader ={ARGB1555, 500, 130, 1000, 2964,	logoIcon, 0};

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
