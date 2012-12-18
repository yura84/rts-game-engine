#include "C_Bitmap.h"
#include <iostream>

C_Bitmap::C_Bitmap(char *filename, bool isAlpha, int alpha) {

	int  n = 0;
	int t = 0;
	FILE *fd;
	char *buffer;
	int bitPerPixel = 4;
	// TODO Auto-generated constructor stub
	if ((fd = fopen(filename, "rb")) == NULL) {
		printf("Error open bitmap\n");
		exit(1);
	}

	fread(&bmpheader, 14,1,fd);//sizeof(BITMAPFILEHEADER));
	fread(&bmpinfo,sizeof(BITMAPINFOHEADER),1,fd);

	width = bmpinfo.biWidth;
	height = bmpinfo.biHeight;
	size = width*height*bitPerPixel;
	data = new char[width*height*bitPerPixel];
	buffer = new char[size];
	fread(buffer, size, 1, fd);

	for (int i = 0; i< size; i++)
	{
		data[i] = buffer[i];
	}
	/*for (int i = 3; i< size-4; i+=8)
	{
		data[i] = 0;
	}*/
	//for (int j=height-1; j>=0; j--) {
	//	for (int i = 0; i<width * bitPerPixel; i+=bitPerPixel) {
	//		t = j*width*3;
	//		data[n] = buffer[i+3+t];
	//		n++;
	//		data[n] = buffer[i+2+t];
	//		n++;
	//		data[n] = buffer[i+1+t];
	//		n++;
	//		//if (isAlpha)
	//		//{
	//		data[n] = 255;//buffer[i+t];
	//		//}
	//		n++;
	//	}
	//}

	delete[] buffer;
	fclose(fd);
}

C_Bitmap::~C_Bitmap() {
	// TODO Auto-generated destructor stub
	//delete[] data;
}
