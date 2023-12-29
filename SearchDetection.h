#pragma once
#include "SolidSphere.h"

class SearchDetection
{
public:
	bool operator() (const SolidSphere& sph1, const SolidSphere& sph2) const;
};

