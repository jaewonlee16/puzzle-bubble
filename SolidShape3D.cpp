#include "SolidShape3D.h"

SolidShape3D::SolidShape3D() {
	angle = 90;
	center.setPos(0, 0, 0);
	velocity.setPos(cos(angle), sin(angle), 0);

	mtl.setEmission(0.1, 0.1, 0.1, 1);
	mtl.setAmbient(0.3, 0.3, 0.3, 1);
	mtl.setDiffuse(0.5, 0.5, 0.5, 1);
	mtl.setSpecular(1.0, 1.0, 1.0, 1);
	mtl.setShininess(10);
}

void SolidShape3D::setCenter(const Vector3f& c)
{
	center.setPos(c[0], c[1], c[2]);
}

Vector3f SolidShape3D::getCenter() const
{
	return center;
}

void SolidShape3D::setVelocity(const Vector3f& v)
{
	velocity.setPos(v[0], v[1], v[2]);
}

Vector3f SolidShape3D::getVelocity() const
{
	return velocity;
}

float SolidShape3D::getAngle() const
{
	return angle;
}

void SolidShape3D::setAngle(float& an)
{
	angle = an;
}



void SolidShape3D::move()
{
	center = center + velocity;
}

void SolidShape3D::rotate(int direction)
{
	if (angle >= 154)
		angle = 154;
	else if (angle <= 26)
		angle = 26;

	if (direction == ROTATE_RIGHT)
		angle -= 8;
	if (direction == ROTATE_LEFT)
		angle += 8;
}

void SolidShape3D::setMTL(const Material& m)
{
	mtl.setEmission(m.getEmission()[0], m.getEmission()[1], m.getEmission()[2], m.getEmission()[3]);
	mtl.setAmbient(m.getAmbient()[0], m.getAmbient()[1], m.getAmbient()[2], m.getAmbient()[3]);
	mtl.setDiffuse(m.getDiffuse()[0], m.getDiffuse()[1], m.getDiffuse()[2], m.getDiffuse()[3]);
	mtl.setSpecular(m.getSpecular()[0], m.getSpecular()[1], m.getSpecular()[2], m.getSpecular()[3]);
	mtl.setShininess(m.getShininess()[0]);
}

/* Implement member functions */