#ifndef _PP_TFT_GRAPH_FT8XX_H
	#define _PP_TFT_GRAPH_FT8XX_H
	
	#include "pp_extram_quadspi.h"
	#include "FT_Gpu.h"
	#include "pp_pointXY.h"
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
#define FT_DispWidth  		800
#define  FT_DispHeight  	480
#define  FT_DispHCycle  	1056
#define  FT_DispHOffset  	46
#define  FT_DispHSync0  	0
#define  FT_DispHSync1  	10
#define  FT_DispVCycle  	525
#define  FT_DispVOffset  	23
#define  FT_DispVSync0  	0
#define  FT_DispVSync1  	10
#define FT_DispPCLK 			2
#define FT_DispSwizzle 		0
#define FT_DispPCLKPol 		1

typedef enum {
	FT_CLKINT = 0x48, //default
	FT_CLKEXT = 0x44,
	FT_CLKSEL = 0x62,
	FT_RST_PULSE = 0x68,
}FT_CLK_RST;


typedef enum {
	FT_GPU_ACTIVE_M =  0x00,  
	FT_GPU_STANDBY_M = 0x41,//default
	FT_GPU_SLEEP_M =   0x42,
	FT_GPU_POWERDOWN_M = 0x50,
}FT_GPU_POWER_MODE_T;


typedef enum {
	FT_GPU_SYSCLK_DEFAULT = 0x00,  //default 60mhz
//	FT_GPU_SYSCLK_72M = 0x06,
	FT_GPU_SYSCLK_60M = 0x45,
	FT_GPU_SYSCLK_48M = 0x44,
	FT_GPU_SYSCLK_36M = 0x03,
	FT_GPU_SYSCLK_24M = 0x02,
}FT_GPU_81X_PLL_FREQ_T;
		
typedef struct{
		PExtRam *extram;
//		unsigned int focusCMDadress;
		bool init;
}PTFTgraphFT8XXData;

typedef struct
{
	unsigned int Format;
	unsigned int Width;
	unsigned int Height;
	unsigned int Stride;
	unsigned int fileSize;
	const char *compressedBitmap;
	unsigned int adressToDecompressBitmap;
}sBitmapHeader;


		typedef struct{
			PTFTgraphFT8XXData data;

			void (*drawLogo)(PTFTgraphFT8XXData *data);
			
			void (*init)(PTFTgraphFT8XXData *data);
			int (*touchTag)(PTFTgraphFT8XXData *data);
			int (*fontHeight)(PTFTgraphFT8XXData *data, unsigned int font);
			int (*charWidth)(PTFTgraphFT8XXData *data, unsigned int font, char sign);
			void (*writePrimitive)(PTFTgraphFT8XXData *data, unsigned int value);
			void (*drawRectangular)(PTFTgraphFT8XXData *data, PXY startPoint, PXY endPoint, unsigned int color, unsigned int lineWidth);
			void (*drawBitmap)(PTFTgraphFT8XXData *data, PXY position, sBitmapHeader *bitmapDesc, unsigned int color);
			void (*drawLine)(PTFTgraphFT8XXData *data, PXY startPoint, PXY endPoint, unsigned int color, unsigned int lineWidth);
			void (*drawPoint)(PTFTgraphFT8XXData *data, PXY position, unsigned int color, unsigned int size);
			void (*writeString)(PTFTgraphFT8XXData *data, PXY startPoint, unsigned int font, unsigned int options, const char* str, unsigned int color);
			void (*writeFromString)(PTFTgraphFT8XXData *data, PXY startPoint, unsigned int font, unsigned int options, const char* str, unsigned int num, unsigned int color);
			void (*writeChar)(PTFTgraphFT8XXData *data, PXY startPoint, unsigned int font, unsigned int options, char c, unsigned int color);
			void (*writeNumber)(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, int n, unsigned int color);
			void (*drawClock)(PTFTgraphFT8XXData *data, PXY position, unsigned int r, unsigned int options, unsigned int h, unsigned int m, unsigned int s, unsigned int ms, unsigned int color, unsigned int bgColor);
			void (*drawButton)(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int font, unsigned int options, const char* str, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int gradColor);
			void (*drawProgress)(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, unsigned int val, unsigned int range, unsigned int color, unsigned int bgColor);
			void (*drawScrollbar)(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, unsigned int val, unsigned int size, unsigned int range, unsigned int tag, unsigned int fgColor, unsigned int bgColor);
			void (*drawIconButton)(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, sBitmapHeader *bitmapHeader, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int gradColor);
			void (*drawKeys)(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int font, unsigned int options, const char* strr, unsigned int color, unsigned int fgColor, unsigned int gradColor);
			void (*drawCircleIconButton)(PTFTgraphFT8XXData *data, PXY position, unsigned int size, sBitmapHeader *bitmapHeader, unsigned int tag, unsigned int color, unsigned int bitmapColor);
			void (*drawToggle)(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int font, unsigned int options, unsigned int state, const char* str, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int bgColor);
			void (*drawSpinner)(PTFTgraphFT8XXData *data, PXY position, unsigned int style, unsigned int scale, unsigned int color);
			void (*drawLineEdit)(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, const char* str, unsigned int maxSignsToDisplay, unsigned int cursor, bool cursorVisible, unsigned int tag);
			void (*drawTextEdit)(PTFTgraphFT8XXData *data, PXY position, unsigned int font, const char (*str)[64], unsigned int strRows, unsigned int maxRows, unsigned int maxSignsInLine, PXY cursor, bool cursorVisible, unsigned int tag);

			void (*drawSpinBox)(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, const char* str, unsigned int maxSignsToDisplay, unsigned int tagPlus, unsigned int tagMinus, unsigned int color, unsigned int fgColor, unsigned int gradColor);

			void (*waitToCMDbuffEmpty)(PTFTgraphFT8XXData *data);
			unsigned int (*loadIcon)(PTFTgraphFT8XXData *data, sBitmapHeader *bitmapHeader, unsigned int address);
			unsigned int (*loadIcons)(PTFTgraphFT8XXData *data, sBitmapHeader *bitmapHeader, unsigned int nrOfBitmaps, unsigned int address);
		}PTFTgraph;

		void PTFTgraphFT8XXConstruct(PTFTgraph *tft, PExtRam *extram);
		
		void initTFTgraphFT8XX(PTFTgraphFT8XXData *data);
		
		void ftWritePrimitiveToCMDbuff(PTFTgraphFT8XXData *data, unsigned int value);
		int ftTouchTag(PTFTgraphFT8XXData *data);
		int ftFontHeight(PTFTgraphFT8XXData *data, unsigned int font);
		int ftCharWidth(PTFTgraphFT8XXData *data, unsigned int font, char sign);
		int ftFreeSpaceInCMDbuff(PTFTgraphFT8XXData *data);
		void ftWaitToCMDbuffEmpty(PTFTgraphFT8XXData *data);
		unsigned int ftWriteStringToCMDbuff(PTFTgraphFT8XXData *data, const char* str);
		void ftWriteDataBuffToCMDbuff(PTFTgraphFT8XXData *data, const char* dataBuff, unsigned int sizeBuff);
		
		void inflate(PTFTgraphFT8XXData *data, sBitmapHeader *bitmapHeader);
		void getPtr(PTFTgraphFT8XXData *data,unsigned int result);
		void calibrate(PTFTgraphFT8XXData *data, unsigned int fgColor, unsigned int bgColor);
		void setFgColor(PTFTgraphFT8XXData *data, unsigned int color);
		void setBgColor(PTFTgraphFT8XXData *data, unsigned int color);
		void setGradColor(PTFTgraphFT8XXData *data, unsigned int color);
		unsigned int setFont(PTFTgraphFT8XXData *data, unsigned int font);
		void drawRectangular(PTFTgraphFT8XXData *data, PXY startPoint, PXY endPoint, unsigned int color, unsigned int lineWidth);
		void drawLine(PTFTgraphFT8XXData *data, PXY startPoint, PXY endPoint, unsigned int color, unsigned int lineWidth);
		void drawPoint(PTFTgraphFT8XXData *data, PXY position, unsigned int color, unsigned int size);
		void drawBitmap(PTFTgraphFT8XXData *data, PXY position, sBitmapHeader *bitmapDesc, unsigned int color);
		void writeString(PTFTgraphFT8XXData *data, PXY startPoint, unsigned int font, unsigned int options, const char* str, unsigned int color);
		void writeFromString(PTFTgraphFT8XXData *data, PXY startPoint, unsigned int font, unsigned int options, const char* str, unsigned int num, unsigned int color);
		void writeChar(PTFTgraphFT8XXData *data, PXY startPoint, unsigned int font, unsigned int options, char c, unsigned int color);
		void writeNumber(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, int n, unsigned int color);
		void drawClock(PTFTgraphFT8XXData *data, PXY position, unsigned int r, unsigned int options, unsigned int h, unsigned int m, unsigned int s, unsigned int ms, unsigned int color, unsigned int bgColor);
		void drawButton(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int font, unsigned int options, const char* str, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int gradColor);
		void drawProgress(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, unsigned int val, unsigned int range, unsigned int color, unsigned int bgColor);
		void drawScrollbar(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, unsigned int val, unsigned int size, unsigned int range, unsigned int tag, unsigned int fgColor, unsigned int bgColor);
		void drawIconButton(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int options, sBitmapHeader *bitmapHeader, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int gradColor);
		void drawCircleIconButton(PTFTgraphFT8XXData *data, PXY position, unsigned int size, sBitmapHeader *bitmapHeader, unsigned int tag, unsigned int color, unsigned int bitmapColor);
		void drawKeys(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int h, unsigned int font, unsigned int options, const char* strr, unsigned int color, unsigned int fgColor, unsigned int gradColor);
		void drawToggle(PTFTgraphFT8XXData *data, PXY position, unsigned int w, unsigned int font, unsigned int options, unsigned int state, const char* str, unsigned int tag, unsigned int color, unsigned int fgColor, unsigned int bgColor);
		void drawSpinner(PTFTgraphFT8XXData *data, PXY position, unsigned int style, unsigned int scale, unsigned int color);
		void drawLineEdit(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, const char* str, unsigned int maxSignsToDisplay, unsigned int cursor, bool cursorVisible, unsigned int tag);
		void drawTextEdit(PTFTgraphFT8XXData *data, PXY position, unsigned int font, const char (*str)[64], unsigned int strRows, unsigned int maxRows, unsigned int maxSignsInLine, PXY cursor, bool cursorVisible, unsigned int tag);

		void drawSpinBox(PTFTgraphFT8XXData *data, PXY position, unsigned int font, unsigned int options, const char* str, unsigned int maxSignsToDisplay, unsigned int tagPlus, unsigned int tagMinus, unsigned int color, unsigned int fgColor, unsigned int gradColor);


		unsigned int loadIcon(PTFTgraphFT8XXData *data, sBitmapHeader *bitmapHeader, unsigned int address);
		unsigned int loadIcons(PTFTgraphFT8XXData *data, sBitmapHeader *bitmapHeader, unsigned int nrOfBitmaps, unsigned int address);
		
		void drawLogo(PTFTgraphFT8XXData *data);
		
#ifdef __cplusplus
}
#endif
	
#endif
