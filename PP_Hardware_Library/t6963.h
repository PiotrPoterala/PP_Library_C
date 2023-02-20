#ifndef _T6963_H
	#define _T6963_H

	#include <stdbool.h>
	#include "delay.h"
	#include "pp_const_ports_masks_list.h"

		#define LCD_PINS_SIZE 13 
		#define LCD_DATA_PINS_SIZE 8 

		typedef enum {DB0=0, DB1, DB2, DB3, DB4, DB5, DB6, DB7, CD, RD, WR, CE, RES}LCDpinsIndexes;

		typedef enum {BASE_FONT, FONT_1}FontType;

				
		typedef struct{
			
			uPin *ioPins;
			PPortsData *ioPorts;
			
			
			volatile unsigned int posX;
			volatile unsigned int posY;
			volatile unsigned int posGraphX;
			volatile unsigned int posGraphY;
			
			FontType typeOfFont;
			volatile _Bool textAtribiuteModeEnable;
			volatile _Bool bold;
			volatile _Bool blink;
			volatile _Bool reverse;
			volatile _Bool independentWriteTextAtribiutes;
			
			volatile _Bool cursorEnable;
			
			
		}LCDdata;
		
		typedef struct{
			unsigned int height;
			unsigned int width;			
		}SFont;

		
	void LCDsetIO(LCDdata *data, uPin *ioPins, PPortsData *ioPorts);
		
	//for font 8x8 and number of dots 240x128
	#define LCD_ROWS 16 
	#define LCD_ROWS_GRAPH 128 
	#define LCD_COLUMNS 30

	#define LCD_PAGES	6		
	#define LCD_PAGES_GRAPH	2
	#define LCD_MAX_ROWS (LCD_PAGES*LCD_ROWS)
	#define LCD_MAX_ROWS_GRAPH (LCD_PAGES_GRAPH*LCD_ROWS_GRAPH)

	void LCDsetFont(LCDdata* data, FontType typeOfFont);
	void LCDsetTextAtribiuteModeEnable(LCDdata* data, _Bool enable);
	void LCDsetReverse(LCDdata* data, _Bool reverse);
	void LCDsetBlink(LCDdata* data, _Bool blink);
	void LCDsetCursorEnable(LCDdata* data, _Bool enable);
	void LCDseekCursor(LCDdata *data, unsigned int cursorX, unsigned int cursorY);
		
	void LCDintro(LCDdata* data);
		
	void LCDclear(LCDdata *data, unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height);
	void LCDclearPages(LCDdata *data, unsigned int firstPage, unsigned int lastPage);
		
	void LCDclearGraph(LCDdata *data, unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height); 
	void LCDclearPagesGraph(LCDdata *data, unsigned int firstPage, unsigned int lastPage);
	
	void LCDgoto(LCDdata *data, unsigned int lcd_X, unsigned int lcd_Y); 
	void LCDgotoPage(LCDdata *data, unsigned int page);
	
	void LCDgotoFontGraph(LCDdata *data, unsigned int lcd_X, unsigned int lcd_Y);

	void LCDwriteTextAtribiutesOnTheArea(LCDdata *data, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);
	void LCDsetIndependentWriteTextAtribiutes(LCDdata* data, _Bool indWrite);
	void LCDclearTextAtribiuteOnTheArea(LCDdata *data, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);

	void LCDgotoGraph(LCDdata *data, unsigned int lcd_X, unsigned int lcd_Y);
	void LCDgotoGraphPage(LCDdata *data, unsigned int page);
	
	void LCDputchar(LCDdata *data, unsigned char c);

	
	#define CG_RAM 0x7800 
	#define GA 0x0800 //graphic home adress
	#define TA 0x2000 //text home adress
	
	
	void lcd_init(LCDdata *lcdData);
	void init_text_ram(LCDdata *lcdData, unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height); 
	void init_graph_ram(LCDdata *lcdData, unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height); 
	void init_CGRAM(LCDdata *lcdData, const unsigned int *sign, unsigned int size, unsigned int id);
	
	void send_icon_ram(LCDdata *data, const unsigned char *buffer);

	void lcd_write_0cmd(LCDdata *lcdData, unsigned char cmd);
	void lcd_write_1cmd(LCDdata *lcdData, unsigned char arg, unsigned char cmd);
	void lcd_write_2cmd(LCDdata *lcdData, unsigned char arg1, unsigned char arg2, unsigned char cmd);
	
	void lcd_hwd_init(LCDdata *lcdData);
	void wr_lcd_bus(LCDdata *lcdData, unsigned char data);
	unsigned char rd_lcd_bus(LCDdata *lcdData);
	void lcd_write_data(LCDdata *lcdData, unsigned char data);
	unsigned char lcd_read_data(LCDdata *lcdData);
	void lcd_write_cmd(LCDdata *lcdData, unsigned char cmd);
	unsigned char lcd_read_status(LCDdata *lcdData);
	static void DataLinesIn(LCDdata *lcdData);
	static void DataLinesOut(LCDdata *lcdData);
	
#endif
