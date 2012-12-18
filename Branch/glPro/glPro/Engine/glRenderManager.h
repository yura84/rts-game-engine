/*
 * renderManager.h
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#ifndef RENDERMANAGER_H_
#define RENDERMANAGER_H_
#include <Windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <string>


class glRenderManager {
private: 
	int winWidth;
	int winHeight;
	int frame;
	int times;
	int timebase;
	float fps;

public:
	glRenderManager(int _winWidth, int winHeight);
	virtual ~glRenderManager();	

	void beginScene();
	void endScene();
	void setOrthographicProjection();
	void restorePerspectiveProjection();
	void renderScene();
	void drawXYZ();
	void drawAim();
	void drawText(int x, int y, std::string);
	void drawSkyBox();
	void renderPlane(int x, int y, float _size);
	void updateFPS();

};


#endif /* RENDERMANAGER_H_ */
