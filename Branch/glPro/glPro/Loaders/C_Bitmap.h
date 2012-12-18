#pragma once
#ifndef CBITMAP_H_
#define CBITMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#ifndef WIN32
typedef struct tagBITMAPFILEHEADER
{
  WORD    bfType;        // смещение 0 от начала файла
  DWORD   bfSize;        // смещение 2 от начала файла, длина 4
  WORD    bfReserved1;
  WORD    bfReserved2;
  DWORD   bfOffBits;     // смещение 10 от начала файла, длина 4
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
  DWORD  biSize;         	//0->4
  LONG   biWidth;			//4->8
  LONG   biHeight;			//8->12
  WORD   biPlanes;			//12->14
  WORD   biBitCount;		//14->16
  DWORD  biCompression;		//16->20
  DWORD  biSizeImage;		//20->24
  LONG   biXPelsPerMeter;	//24->28
  LONG   biYPelsPerMeter;	//28->32
  DWORD  biClrUsed;			//32->36
  DWORD  biClrImportant;	//36->40
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
#else
#include <Windows.h>
#endif

class C_Bitmap {
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;

	int width;
	int height;
	int size;
public:
	char *data;
	C_Bitmap(char *filename, bool isAlpha = false, int alpha = 0);
	virtual ~C_Bitmap();
	int getWidth() {return width;};
	int getHeight() {return height;};
	int getSize() {return size;};

};

#endif /* CBITMAP_H_ */
