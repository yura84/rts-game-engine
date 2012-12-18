#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "Loaders\C_Bitmap.h"
#include <windows.h>
#include <gl/GL.h>
#include "Loaders/lodepng.h"

class glTexture
{
private:
	

	C_Bitmap * LoadImage(char *fileName);
public:
	C_Bitmap * cbitmap;
	GLuint texture[1];
	glTexture(void);
	glTexture(char *fileName);

	virtual ~glTexture(void);
	bool CreateTexture(char *fileName);
	void BindTexture(void);

};

#endif //GLTEXTURE_H
