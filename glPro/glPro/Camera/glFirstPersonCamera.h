/*
 * glFirstPersonCamera.h
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#ifndef GLFIRSTPERSONCAMERA_H_
#define GLFIRSTPERSONCAMERA_H_
#include  "glCamera.h"
#define WIDTH 800
#define HEIGHT 600

class glFirstPersonCamera : public glCamera{

private:
	float angleX;
	bool  moving[4];
	bool  _jump;
	float dt;
	
private:
	void computePos(float deltaMove);
	void computePosL(float deltaMove);
	void computeDir(float deltaAngle);
	void computeDirL(float deltaAngle);


public:
	glFirstPersonCamera();
	virtual ~glFirstPersonCamera();

	virtual void Update(float dt);
	virtual void moveForward();
	virtual void moveBackward();
	virtual void moveLeft();
	virtual void moveRight();

	void setMove(char type, bool value);
	void moveTo();
	void jump();
	void mouseNavigate(int x, int y);

	Vector3f GetPosition(void);
	Vector3f GetAngle(void);
	Vector3f GetView(void);


};

#endif /* GLFIRSTPERSONCAMERA_H_ */
