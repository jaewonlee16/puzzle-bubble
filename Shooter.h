#pragma once
#include "SolidSphere.h"
class Shooter : public SolidShape3D
{
public:
	Shooter();
	void draw() const;

private:
	int slice;
	int stack;
	float height;
	float base;
	float size;
};

