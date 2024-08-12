#ifndef _PP_IODEVICE_H
	#define _PP_IODEVICE_H

	#ifdef __cplusplus
	extern "C" {
	#endif

	#define qMARK_SCREEN_TAG (1<<28)
	#define qMARK_KEY (2<<28)
	#define qMARK_PRESS_KEY (3<<28)
	#define qMARK_ATC (4<<28)


			typedef enum {ReadOnly=1, WriteOnly, ReadWrite} OpenMode;
			typedef enum {Baud1200=1200, Baud2400=2400, Baud4800=4800, Baud9600=9600, Baud19200=19200, Baud115200=115200} BaudRate;
			typedef enum {Data8=8, Data9} DataBits;
			typedef enum {Stop1=1, Stop2} StopBits;
			typedef enum {NoParity, EvenParity, OddParity} Parity;	

#ifdef __cplusplus
}
#endif
	
#endif
