#include "glFpsManager.h"


glFpsManager::glFpsManager() {

}

glFpsManager::~glFpsManager() {

}

void glFpsManager::update() {
	dt = glutGet(GLUT_ELAPSED_TIME)-prevtime;
	prevtime=glutGet(GLUT_ELAPSED_TIME);
}

float glFpsManager::getDT() {
	return dt;
}