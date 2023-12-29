#pragma once

#include "Material.h"
#include "Vector3f.h"
#include <math.h>

enum direction{ROTATE_LEFT, ROTATE_RIGHT};

class SolidShape3D
{
public:
	SolidShape3D();

	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;
	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;
	float getAngle() const;
	void setAngle(float& an);
	void move();
	void rotate(int direction);
	void setMTL(const Material& m);
	virtual void draw() const = 0;
	

protected:
	Vector3f center;
	Vector3f velocity;
	Material mtl;
	float angle;


};

