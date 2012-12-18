#ifndef GLFPSMANAGER_H_
#define GLFPSMANAGER_H_

#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

class glFpsManager {
private:
	int prevtime;
	float dt;

public:
	glFpsManager();
	~glFpsManager();
	void update();
	float getDT();
};

#endif // end GLFPSMANAGER