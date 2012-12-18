/*
 * glFirstPersonCamera.cpp
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#include "glFirstPersonCamera.h"
#include <math.h>
#include <iostream>

glFirstPersonCamera::glFirstPersonCamera()
{
	// TODO Auto-generated constructor stub
	
}

glFirstPersonCamera::~glFirstPersonCamera()
{
	// TODO Auto-generated destructor stub
}

void glFirstPersonCamera::Update(float _dt)
{
	//gluLookAt(x, y, z,  x+lx,  y+viewy,  z+lz,  anglex, angley,  anglez);
	gluLookAt(position.x, position.y, position.z,  position.x + l.x,  position.y + view.y,  position.z + l.z,  angle.x, angle.y,  angle.z);

	moveTo();
	dt = _dt;
	/*if ((_jump)&&(y<2)) y+=speedy;
	else 
	{
		if (y>1)
		{
			_jump = false;
			y-=speedy;
		}

	}
	*/
}

void glFirstPersonCamera::computePos(float deltaMove)
{
	position.x += deltaMove * l.x * 0.2f*dt;
	position.z += deltaMove * l.z * 0.2f*dt;
	//std::cout << "x=" << x << "z= " << z << std::endl;
}

void glFirstPersonCamera::computePosL(float deltaMove)
{
	computeDirL(90.0);
	position.x += deltaMove * l1.x * 0.2f*dt;
	position.z += deltaMove * l1.z * 0.2f*dt;
}

void glFirstPersonCamera::computeDir(float deltaAngle) {

	angleX += deltaAngle;
	l.x = sin(angleX);
	l.z = -cos(angleX);
}

void glFirstPersonCamera::computeDirL(float deltaAngle)
{
	l1.x = sin(angleX+deltaAngle);
	l1.z = -cos(angleX+deltaAngle);

}


void glFirstPersonCamera::moveForward()
{
	computePos(speed.x);
}

void glFirstPersonCamera::moveBackward()
{
	computePos(-speed.x);
}

void glFirstPersonCamera::moveLeft()
{
	computePosL(speed.x);
}

void glFirstPersonCamera::moveRight()
{
	computePosL(-speed.x);
}

void glFirstPersonCamera::setMove(char type, bool value)
{
	moving[type] = value;
}

void glFirstPersonCamera::moveTo()
{	
	if (moving[0]) moveForward();
	if (moving[1]) moveBackward();
	if (moving[3]) moveLeft();
	if (moving[2]) moveRight();	
}

void glFirstPersonCamera::jump()
{
	_jump = true;
}

void glFirstPersonCamera::mouseNavigate(int x, int y)
{
	if (y!=(HEIGHT/2))
	{
		view.y += ((HEIGHT/2)-y)*speed.y;
	}
		
	if (x!=(WIDTH/2))
	{
		// update deltaAngle
		deltaAngle = (x - (WIDTH/2)) * speed.z;
		computeDir(deltaAngle);  
	}
	if ((x!=(WIDTH/2)) || (y!=(HEIGHT/2))) glutWarpPointer((WIDTH/2), (HEIGHT/2));

//	std::cout << viewy << " ";

}

Vector3f glFirstPersonCamera::GetPosition(void)
{
	return position;
}

Vector3f glFirstPersonCamera::GetAngle(void)
{
	return angle;
}

Vector3f glFirstPersonCamera::GetView(void)
{
	return view;
}