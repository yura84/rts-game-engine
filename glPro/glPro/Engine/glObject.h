/*
 * openglWin.h
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#ifndef GLOBJECT_H_
#define GLOBJECT_H_
#include <Windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
typedef struct Vertex {
	float x;
	float y;
	float z;
};

typedef struct ModelHader {
	int filesize;
	int numberOfVertex;
	int reserved;
	int reserved1;
	int reserved2;
};

class glObject {
public:
	float x;
	float y;
	float z;

	float dx;
	float dy;
	float dz;

	float lx;
	float ly;
	float lz;

	int width;
	int height;
	int numberOfVertex;
	Vertex *vertex;

public:
	glObject();
	virtual ~glObject();	
	virtual void load(char *filename);
};

#endif /* GLOBJECT_H_ */
