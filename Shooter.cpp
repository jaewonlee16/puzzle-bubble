#include "Shooter.h"

Shooter::Shooter()
{
	slice = 100;
	stack = 100;
	height = 40;
	base = 20;
	size = 30;
}

void Shooter::draw() const
{
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	
	glTranslatef(0, -320 + size/2, 0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(angle, 0, 0, 1);
	glutSolidCube(size);

	glPushMatrix();
		glTranslatef(0, size / 2, 0);
		glPushMatrix();
			glRotatef(90, -1, 0, 0);
			glutSolidCone(base, height, slice, stack);

		glPopMatrix();
	glPopMatrix();

	glPopMatrix();

}
