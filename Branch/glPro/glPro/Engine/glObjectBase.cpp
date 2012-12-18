#include "glObjectBase.h"
#include <stdio.h>
#include <iostream>
glObjectBase::glObjectBase()
{
	dist=0;
	numberOfVertex = 99;
	vertex = new Vertex[numberOfVertex];
	renderVertex=0;
}

glObjectBase::glObjectBase(float _x, float _y, float _z, float _dx, float _dy, float _dz)
{
	x = _x;
	y = _y;
	z = _z;
	dx = _dx;
	dy = _dy;
	dz = _dz;
	dist = (rand()%10)+2;
}

glObjectBase::~glObjectBase()
{

}

void glObjectBase::init(float _x, float _y, float _z, float _dx, float _dy, float _dz)
{
	x = _x;
	y = _y;
	z = _z;
	dx = _dx;
	dy = _dy;
	dz = _dz;
	dist = 100;
}

void glObjectBase::update()
{
	float speed = 1.0f;
	if (dist>1)
	{
		x += dx*speed;
		y += dy*speed;
		z += dz*speed;
		glTranslatef(x, y, z);
		glutSolidSphere(0.01f,20,20);
	}
	else dist = 0;
}

void glObjectBase::save(char *filename) {
	
	FILE *fd;
	vertex = new Vertex[numberOfVertex];
	vertex[0].x = 0.0f;
	vertex[0].y = 0.2f;
	vertex[0].z = 0.0f;

	vertex[1].x = 2.0f;
	vertex[1].y = 0.2f;
	vertex[1].z = 0.0f;

	vertex[2].x = 2.0f;
	vertex[2].y = 0.2f;
	vertex[2].z = 2.0f;

	vertex[3].x = 0.0f;
	vertex[3].y = 0.2f;
	vertex[3].z = 0.0f;

	vertex[4].x = 2.0f;
	vertex[4].y = 0.2f;
	vertex[4].z = 0.0f;

	vertex[5].x = 2.0f;
	vertex[5].y = 2.0f;
	vertex[5].z = 0.0f;


	ModelHader mh;
	mh.filesize = sizeof(mh)+(sizeof(vertex)*numberOfVertex);
	mh.numberOfVertex = numberOfVertex;
	mh.reserved = 0;
	mh.reserved1 = 0;
	mh.reserved2 = 0;

	fd = fopen(filename, "wb");
	if (fd==NULL) return;
	fwrite(&mh, sizeof(mh), 1, fd);
	fwrite(&vertex, sizeof(Vertex), numberOfVertex, fd);

	//std::cout << fr << " - " <<buffer;
	

	fclose(fd);
}

void glObjectBase::load(char *filename)
{
	FILE *fd;
	ModelHader mh;
	fd = fopen(filename, "rb");
	if (fd==NULL) return;
	fread(&mh, sizeof(mh), 1, fd);
	numberOfVertex = mh.numberOfVertex;
	vertex = new Vertex[numberOfVertex];
	fread(&vertex, sizeof(vertex), numberOfVertex, fd);

	for (int i=0; i<numberOfVertex; i++)
	{
	//	std::cout << vertex[i].x << "; " << vertex[i].y << "; " << vertex[i].z << std::endl;
	}
	//std::cout << mh.filesize<< ":" << mh.numberOfVertex <<" : "<< mh.reserved << " : " << mh.reserved1 << " : "<< mh.reserved2 << std::endl;
	
	fclose(fd);
}

void glObjectBase::render() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(1.0f,0.5f,0.5f);
	glTranslatef(x , y, z);
	glutSolidSphere(0.05f,20,55);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

bool glObjectBase::checkCollision(float _x, float _y, float _z, float size) {

	float px,py, pz;
	px = abs(x - _x);
	py = abs(y - _y);
	pz = abs(z - _z);
	if (((px<size)&&(py<size))&&(pz<size)) {
		dist = 0.0f;
		return true;
	}
	return false;
}