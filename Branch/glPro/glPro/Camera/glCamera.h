/*
 * glCamera.h
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#ifndef GLCAMERA_H_
#define GLCAMERA_H_

#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

struct Vector3f
{
	Vector3f()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float x;
	float y;
	float z;
};

class glCamera {
public:
	
	Vector3f angle;
	Vector3f position;
	Vector3f view;
	Vector3f speed;
	Vector3f origin;
	Vector3f l;
	Vector3f l1;

	/*
	float anglex;
	float angley;
	float anglez;
	*/

	// actual vector representing the camera's direction
	/*float lx;
	float ly;
	float lz;
	float lx1;
	float ly1;
	float lz1;*/

	// XZ position of the camera
	/*float x;
	float y;
	float z;*/

	// the key states. These variables will be zero
	//when no key is being presses
	float deltaAngle;
	float deltaMove;
	float deltaMoveSide;
	/*float viewx;
	float viewy;
	float viewz;*/

	/*int xOrigin;
	int yOrigin;
	int zOrigin;*/
	/*float speedx;
	float speedy;
	float speedz;*/

public:
	glCamera();
	virtual ~glCamera();
	virtual void Update();

	virtual void moveForward();
	virtual void moveBackward();
	virtual void moveLeft();
	virtual void moveRight();

};

#endif /* GLCAMERA_H_ */
