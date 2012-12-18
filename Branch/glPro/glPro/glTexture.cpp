#include "glTexture.h"

glTexture::glTexture(void)
{
}

glTexture::glTexture(char *fileName)
{
	//LoadImage(fileName);
	CreateTexture(fileName);
}

glTexture::~glTexture(void)
{
}

C_Bitmap * glTexture::LoadImage(char *fileName)
{
	cbitmap = new C_Bitmap(fileName);
	return cbitmap;
}

bool glTexture::CreateTexture(char *fileName)
{
	//cbitmap = new C_Bitmap(fileName);
	// Load file and decode image.
	std::vector<unsigned char> image;
	 unsigned width, height;
	 unsigned error = lodepng::decode(image, width, height, fileName);

	// If there's an error, display it.
	if(error != 0)
	{
	  //std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
	return 1;
	}
	//if (cbitmap)
	if (image.size())
	{
		glGenTextures(1, &texture[0]);					// Create The Texture
		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cbitmap->getWidth(), cbitmap->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, cbitmap->data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		return true;
	}
	return false;
}

void glTexture::BindTexture(void)
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
}