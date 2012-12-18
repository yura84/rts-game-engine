#pragma once
#include "globjectBot.h"
#include <iostream>
#include <vector>

class glAi {
private:
	glObjectBot& glBot;
	std::vector<std::pair<float, float> > waypoints;
	int currentWaypoints;
public:
	glAi(glObjectBot& _glBot);
	virtual ~glAi(void);

	void move(void);
	void update(float dt);
};


