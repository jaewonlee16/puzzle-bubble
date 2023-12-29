#include "Timer.h"
#include <GL/glut.h>

Timer::Timer(float _width) {
	width = _width;
	setVertices();
	
}

void Timer::setMtl(const Material& _mtl)
{
	mtl = _mtl;
}

void Timer::setWidth(float _width)
{
	width = _width;
}

void Timer::setVertices()
{
	v1.setPos(130, -330, 0);
	v2.setPos(130, -350, 0);
	v3.setPos(130 + width * 20, -350, 0);
	v4.setPos(130 + width * 20, -330, 0);
}

void Timer::draw()
{
	
	setVertices();
	
	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());
	
	glColor3f(0.8, 0.1, 0.1);
	glBegin(GL_QUADS);
		glVertex3f(v1[0], v1[1], v1[2]);
		glVertex3f(v2[0], v2[1], v2[2]);
		glVertex3f(v3[0], v3[1], v3[2]);
		glVertex3f(v4[0], v4[1], v4[2]);
	glEnd();
	glPopMatrix();
	
	
}
