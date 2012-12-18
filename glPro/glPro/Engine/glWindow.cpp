/*
 * openglWin.cpp
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#include "glWindow.h"


glWindow::glWindow(int _left, int _top, int _width, int _height): left(_left), top(_top), width(_width), height(_height)
{
		// TODO Auto-generated constructor stub

}

glWindow::~glWindow() {
	// TODO Auto-generated destructor stub
}

void glWindow::init(int argc, char **argv, void (display)(), void (redraw)())
{
	glutInit(&argc, argv);
	glutInitWindowPosition(left, top);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Example of using OpenGL");
	//glutDisplayFunc(display);
//	glutIdleFunc(redraw);
	//glEnable(GL_DEPTH_TEST);
	//glutMainLoop();
}

void glWindow::changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
