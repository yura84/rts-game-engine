/*
 * glCamera.cpp
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */
#include "glCamera.h"


glCamera::glCamera() {
	
	angle = Vector3f(0.0f, 1.0f, 0.0f);
	l = Vector3f(0.0f, 0.0f, -2.0f);
	l1 = Vector3f(0.0f, 0.0f, -2.0f);
	position = Vector3f(0.0f, 2.0f, 0.0f);
	view = Vector3f(0.0f, 0.1f, 0.0f);
	origin = Vector3f(1.0f, 0.0f, 0.0f);
	speed = Vector3f(0.1f, 0.002f, 0.003f);
	/*anglex = 0.0f;
	angley = 1.0f;
	anglez = 0.0f;

	lx = 0.0f;
	ly = 0.0f;
	lz = -2.0f;

	lx1 = 0.0f;
	ly1 = 0.0f;
	lz1 = -2.0f;

	x = 0.0f;
    y = 2.0f;
    z = 0.0f;*/

	deltaAngle = 0.0f;
	deltaMove = 0;
	deltaMoveSide = 0;

	/*viewx = 0.0f;
	viewy =  0.1f;
	viewx = 0.0f;

	xOrigin = 1.0f;
	yOrigin = 0.0f;
	zOrigin = 0.0f;

	speedx = 0.1;
	speedy = 0.002;
	speedz = 0.003;*/

}

glCamera::~glCamera() {
	// TODO Auto-generated destructor stub
}

void glCamera::Update()
{
	gluLookAt(position.x, position.y, position.z,  position.x + l.x,  position.y + view.y,  position.z + l.z,  angle.x, angle.y,  angle.z);
}

void glCamera::moveForward()
{

}

void glCamera::moveBackward()
{

}

void glCamera::moveLeft()
{

}

void glCamera::moveRight()
{

}
