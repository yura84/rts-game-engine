#include "glObjectBot.h"
#include <iostream>

glObjectBot::glObjectBot(void)
{
	x = 0.0f;
	y = 1.0f;
	z = 0.0f;
	fx = 5.0f;
	fy = 1.0f;
	fz = 5.0f;
	life = 100;
	std::cout << "RESTART" << std::endl;
}


glObjectBot::~glObjectBot(void)
{
}
void glObjectBot::move() {
	float speed[3] = {0.001,0.001,0.001};
	if (((x-fx)>1)||((x-fx)<-1)) lx= fx-x;
	else lx = 0.0f;

	if (((y-fy)>1)||((y-fy)<-1)) ly= fy-y;
	else ly = 0.0f;

	if (((z-fz)>1)||((z-fz)<-1)) lz= fz-z;
	else lz = 0.0f;

	x = x + lx*speed[0];
	y = y + ly*speed[1];
	z = z + lz*speed[2];
}

void glObjectBot::update(float dt) {
	if ((lx==0)&&(lz==0)) {
		//fx = -30 + rand()%60;
		//fz = -30 + rand()%60;
	}
//	move();
}

void glObjectBot::render() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1.0f,0,0);
	glTranslatef(x , y, z);
	glutSolidSphere(0.5f,20,55);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

bool glObjectBot::restart() {
	static int wait;

	if (life<=0) {
		wait++;
		if (wait>120) {
			x = -10+rand()%10;
			y = 1.0f;
			z = -10+rand()%10; 
			fx = x;
			fy = y;
			fz = z;
			life = 100;
			wait = 0;
			return true;
		}
	}
	return false;
}