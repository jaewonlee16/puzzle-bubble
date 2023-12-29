#include "SolidSphere.h"
#include <math.h>

SolidSphere::SolidSphere(float r, int sl, int st) {
	setRadius(r);
	setSlice(sl);
	setStack(st);
	state = NEXT;
	removeDetection = NOT_DETECTED;
	dropDetection = false;
	afterCollisionHandling = false;
}

void SolidSphere::setRadius(float r)
{
	radius = r;
}

float SolidSphere::getRadius() const
{
	return radius;
}

void SolidSphere::setSlice(float sl)
{
	slice = sl;
}

void SolidSphere::setStack(float st)
{
	stack = st;
}

void SolidSphere::setColor(Color& c)
{
	color = c;
}

int SolidSphere::getColor() const
{
	return color;
}


void SolidSphere::initialize()
{
	float x = 100 * cos(angle * PI / 180);
	float y = -305 + 100 * sin(angle * PI / 180);

	switch (state){
	case NEXT:
		setVelocity(Vector3f(0, 0, 0));
		setCenter(Vector3f(-200, -400 + radius, 0));
		break;
	case SHOOTER:
		setVelocity(Vector3f(0, 0, 0));
		setCenter(Vector3f(x,  y, 0));
	case MOVE:
		break;
	case CEIL:
		break;
	case DROP:
		setVelocity(Vector3f(0, -10, 0));
		break;
		}
}

void SolidSphere::draw() const
{
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());


	glLoadIdentity();
	
	

	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(radius, slice, stack);
	glPopMatrix();

}

