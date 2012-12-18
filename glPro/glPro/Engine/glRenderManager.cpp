/*
 * renderManager.cpp
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */
#include "glRenderManager.h"

glRenderManager::glRenderManager(int _winWidth, int winHeight): winWidth(_winWidth), winHeight(winHeight) 
{

}

glRenderManager::~glRenderManager() {

}

void glRenderManager::beginScene() {
	
	updateFPS();
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
}

void glRenderManager::endScene() {
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void glRenderManager::setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();
	GLint viewport [4];
	glGetIntegerv (GL_VIEWPORT, viewport);
	gluOrtho2D (0,viewport[2], viewport[3], 0);
	
	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void glRenderManager::restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void glRenderManager::renderPlane(int x, int y, float _size) {
	float sz=_size;
	glColor3f(1.0f, 0.1f, 0.1f);
	glPushMatrix();
	glTranslatef(x ,0.1f, y);
	glBegin(GL_QUADS);
		glVertex3f( -sz, 0.0f, -sz);
		glVertex3f( sz, 0.0f, -sz);			
		glVertex3f( sz, 0.0f, sz);			
		glVertex3f( -sz, 0.0f, sz);
	glEnd();
	glPopMatrix();
}

void glRenderManager::renderScene() {
	
	int i = 0;
	int j = 0;
	float scaleValue= 0.01;

	glColor3f(0.1f, 0.1f, 0.1f);
	//glPushMatrix();
		//glTranslatef(0.0f ,0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f( -100.0f, 0.0f, -100.0f);
			glVertex3f( 100.0f, 0.0f, -100.0f);			
			glVertex3f( 100.0f, 0.0f, 100.0f);			
			glVertex3f( -100.0f, 0.0f, 100.0f);
		glEnd();

		
		glColor3f(1.0f, 1.0f, 0.1f);
		drawXYZ();
	/*glPushMatrix();
	glTranslatef(0.0f ,1.5f, 0.0f);
	glutSolidSphere(0.5f,20,55);
	glPopMatrix();
	*/
}

void glRenderManager::drawAim() {
	int cx = 400;
	int cy = 300;
	int sizex = 10;
	int sizey = 10;
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glDepthFunc (GL_ALWAYS);
	glColor3f (1,1,1);
	//glRasterPos2f(400, 300);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(cx,cy);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(cx+100.0f,cy);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(cx+100.0f,cy+100.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(cx, cy+100.0f);

	/*glBegin(GL_LINES);
		glVertex2f(cx-2*sizex,cy);
		glVertex2f(cx-sizex,cy);

		glVertex2f(cx+sizex, cy);
		glVertex2f(cx+sizex*2,cy);

		glVertex2f(cx,cy-sizey*2);
		glVertex2f(cx,cy-sizey);
		
		glVertex2f(cx,cy+sizey);
		glVertex2f(cx,cy+sizey*2);

		glVertex2f(cx-1,cy);
		glVertex2f(cx+1,cy);
		glVertex2f(cx,cy-1);
		glVertex2f(cx,cy+1);*/

		glEnd();
		glPopMatrix();	
	
	restorePerspectiveProjection();
}

void glRenderManager::drawXYZ() {
	float size = 20.0f;
	//glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		glColor3f (0,0,1);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(size, 0.0f, 0.0f);
		glColor3f (0,1,0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, size, 0.0f);
		glColor3f (1,0,0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, size);
	glEnd();
	glRasterPos3f(size, 0.0f, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
	glRasterPos3f( 0.0f, size, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
	glRasterPos3f(0.0f, 0.0f, size);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');
//	glEnable(GL_LIGHTING);
	
}

void glRenderManager::drawText(int x, int y, std::string str) {

	glDisable(GL_LIGHTING);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glDepthFunc (GL_ALWAYS);
	glColor3f (0.9f,0.9f,0.5f);
	glRasterPos2f(x, y);
	
	for (int i = 0; i<str.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str.c_str()[i]);
	
	glPopMatrix();
/*	
glRasterPos2f(10.0f, 300.0f);
glPushMatrix();
	GLubyte A[14] = {
    0xFF,0xAA,
    0xFF,0xFF,
    0xFF,0xFF,
    0xFF,0xFF,
    0xFF,0xFF,
    0xFF,0xFF,
    0xFF,0xFF,
};

	glColor3f (0.1f,0.6f,1.0f);
	 glBitmap(14,1,0,0,0,0,A);
glPopMatrix();
*/
	restorePerspectiveProjection();
	//glEnable(GL_LIGHTING);
}

void glRenderManager::drawSkyBox() {
	 glBegin(GL_QUADS);
        // Assign the texture coordinates and vertices for the BACK Side
        //glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0, 0, 0);
        //glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(0 + winWidth, 0, 0);
        //glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(0 + winWidth, 0 + winHeight, 0);
        //glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(0, 0 + winHeight, 0);
     glEnd();
}

void glRenderManager::updateFPS()
{
	frame++;
	times=glutGet(GLUT_ELAPSED_TIME);

	if (times - timebase > 1000) {
		fps = frame*1000.0/(times-timebase);
	 	timebase = times;
		frame = 0;
	}
}