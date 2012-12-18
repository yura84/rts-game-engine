/*
 * openglWin.h
 *
 *  Created on: Mar 6, 2012
 *      Author: iurii
 */

#ifndef GLOBJECTBASE_H_
#define GLOBJECTBASE_H_
#include "glObject.h"

class glObjectBase : public glObject {
public:
	float dist;
	int renderVertex;
	
public:
	glObjectBase();
	glObjectBase(float _x, float _y, float _z, float _dx, float _dy, float _dz);
	virtual ~glObjectBase();
	
	void init(float _x, float _y, float _z, float _dx, float _dy, float _dz);
	void update();
	void load(char *filename);
	void save(char *filename);
	void render();
	bool checkCollision(float _x, float _y, float _z, float size);
};

#endif /* GLOBJECTBASE_H_ */
