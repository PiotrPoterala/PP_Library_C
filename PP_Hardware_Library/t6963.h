#ifndef _T6963_H
	#define _T6963_H

	#include <stdbool.h>
	#include "delay.h"
	#include "input_signals.h"

		typedef enum {BASE_FONT, FONT_1}FontType;

		typedef struct{
			volatile unsigned int posX;
			volatile unsigned int posY;
			volatile unsigned int posGraphX;
			volatile unsigned int posGraphY;
			
			FontType typeOfFont;
			volatile _Bool textAtribiuteModeEnable;
			volatile _Bool bold;
			volatile _Bool blink;
			volatile _Bool reverse;
			volatile _Bool dependenceAtribiutesOnArea;
			
			volatile _Bool cursorEnable;
			
			
		}LCDdata;
		
		typedef struct{
			unsigned int height;
			unsigned int width;			
		}SFont;

	//for font 8x8 and number of dots 240x128
	#define LCD_ROWS 16 
	#define LCD_ROWS_GRAPH 128 
	#define LCD_COLUMNS 30

	#define LCD_PAGES	6		
	#define LCD_PAGES_GRAPH	2
	#define LCD_MAX_ROWS (LCD_PAGES*LCD_ROWS)
	#define LCD_MAX_ROWS_GRAPH (LCD_PAGES_GRAPH*LCD_ROWS_GRAPH)

	void LCDsetTextAtribiuteModeEnable(LCDdata* data, _Bool enable);
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
	void LCDclearFontGraph(LCDdata *data, unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height);

	void LCDsetTextAtribiuteOnTheArea(LCDdata *data, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);
	void LCDclearTextAtribiuteOnTheArea(LCDdata *data, unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);

	void LCDgotoGraph(LCDdata *data, unsigned int lcd_X, unsigned int lcd_Y);
	void LCDgotoGraphPage(LCDdata *data, unsigned int page);
	
	void LCDputchar(LCDdata *data, const unsigned char c);

	void LCDputcharGraph(LCDdata *data, const char c);



	#define GPIO_CRL_CLR 0x00000000	 
	#define LCD_DB 0x00FF

//	#define CG_RAM 0x0000 //adres poczatkowy obszaru grafiki
//	#define GA 0x0800 //adres poczatkowy obszaru grafiki
//	#define TA 0x2600 //adres poczatkowy obszaru tekstu
	
	#define CG_RAM 0x7800 
	#define GA 0x0800 //graphic home adress
	#define TA 0x2000 //text home adress
	
	
	void lcd_init(void);
	void init_text_ram(unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height); 
	void init_graph_ram(unsigned int x_start, unsigned int y_start, unsigned int width, unsigned int height); 
	
	void send_icon_ram(LCDdata *data, const unsigned char *buffer);

	void lcd_write_0cmd(unsigned char cmd);
	void lcd_write_1cmd(unsigned char arg, unsigned char cmd);
	void lcd_write_2cmd(unsigned char arg1, unsigned char arg2, unsigned char cmd);
	void lcd_hwd_init(void);
	void wr_lcd_bus(unsigned char data);
	unsigned char rd_lcd_bus(void);
	void lcd_write_data(unsigned char data);
	unsigned char lcd_read_data(void);
	void lcd_write_cmd(unsigned char cmd);
	unsigned char lcd_read_status(void);
	static void DataLinesIn(void);
	static void DataLinesOut(void);
	void init_CGRAM(const unsigned int *sign, unsigned int size, unsigned int id);
	
#endif
