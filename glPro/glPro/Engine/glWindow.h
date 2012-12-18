/*
 * openglWin.h
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#ifndef GLWINDOW_H_
#define GLWINDOW_H_
#include <Windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
class glWindow {

	int left;
	int top;
	int width;
	int height;


public:
	glWindow(int _left, int _top, int _width, int _height);
	virtual ~glWindow();
	void init(int argc, char **argv, void (display)(), void (redraw)());
	void changeSize(int w, int h);
	//void Display(void);
	//void Redraw(void);
};

#endif /* GLWINDOW_H_ */
