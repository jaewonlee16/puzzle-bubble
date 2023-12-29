#pragma once
#include "Vector3f.h"
#include "Material.h"

class Timer
{
public:
	Timer(float _width);

	void setMtl(const Material& _mtl);
	void setWidth(float _width);
	void setVertices();
	void draw();

private:
	Material mtl;

	float width;

	Vector3f v1;
	Vector3f v2;
	Vector3f v3;
	Vector3f v4;
};

