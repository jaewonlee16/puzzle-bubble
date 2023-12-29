#pragma once
#include "SolidSphere.h"
#include "CollisionDetection.h"
#define ROOT3 1.732

class CollisionHandling
{
public:
	void operator()(SolidSphere& sph1, SolidSphere& sph2);
};

