#pragma once
#include "globject.h"
class glObjectBot :
	public glObject
{
public:
	float fx;
	float fy;
	float fz;
	int life;
	int killed;
public:
	glObjectBot(void);
	virtual ~glObjectBot(void);
	void update(float dt);
	void render();
	void move();
	//void restart() {static int wait; if (wait>2000) {wait=0; };
	int getLife() {return life;};
	void setLife(int _life) {life=_life;};
	void setPosition(float position[3]) {x=position[0]; y=position[1]; z=position[2];};
	void getShot(){life-=50; };
	void addKill() {killed++;};
	int getKill() {return killed;};

	bool restart();
};

