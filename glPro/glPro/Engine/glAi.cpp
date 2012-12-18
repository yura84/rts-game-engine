#include "glAi.h"


glAi::glAi(glObjectBot& _glBot): glBot(_glBot) {
	waypoints.push_back(std::pair<float,float>(_glBot.x+15, _glBot.y-13));
	waypoints.push_back(std::pair<float,float>(_glBot.x-13, _glBot.y+14));
	waypoints.push_back(std::pair<float,float>(_glBot.x+17, _glBot.y-13));
	waypoints.push_back(std::pair<float,float>(_glBot.x-15, _glBot.y+11));
	currentWaypoints = 0;
}

glAi::~glAi(void) {

}

void glAi::move(void) {
	float lx=0.05;
	float ly;
	float lz=0.05;
	if (glBot.x>waypoints[currentWaypoints].first) glBot.x-=lx;
	if (glBot.x<waypoints[currentWaypoints].first) glBot.x+=lx;
	if (glBot.z>waypoints[currentWaypoints].second) glBot.z-=lz;
	if (glBot.z<waypoints[currentWaypoints].second) glBot.z+=lz;

	if ((abs(glBot.x-waypoints[currentWaypoints].first)<1.0)&&(abs(glBot.z-waypoints[currentWaypoints].second)<1.0)) {
		currentWaypoints++;
		if (currentWaypoints>= waypoints.size()) currentWaypoints=0;
	}
}

void glAi::update(float dt) {
	std::cout << glBot.x << ":"<< glBot.z<< " : "<< currentWaypoints <<"\n";
	move();
}


