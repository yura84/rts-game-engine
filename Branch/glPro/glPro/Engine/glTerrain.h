/*
 * openglWin.h
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#ifndef GLTERRAIN_H_
#define GLTERRAIN_H_
#include <Windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>

#define    MAP_SIZE  1024  
#define    STEP_SIZE  2      
#define    HEIGHT_RATIO  1.0f

class glTerrain {

	int left;
	int top;
	int width;
	int height;
	BYTE  pHeightMap[MAP_SIZE*MAP_SIZE];
	bool bRender;
public:
	glTerrain();
	virtual ~glTerrain();
	void init(BYTE pHeightMap[]);
	void renderTerrain();
	int Height(int X, int Y);
	void setVertexColor(int x, int y);

	
};

#endif /* GLTERRAIN_H_ */
