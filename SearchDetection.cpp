#include "SearchDetection.h"

bool SearchDetection::operator()(const SolidSphere& sph1, const SolidSphere& sph2) const
{
	float distance = dotProduct(sph1.getCenter() - sph2.getCenter(), sph1.getCenter() - sph2.getCenter());
	if (distance <= (sph1.getRadius() + sph2.getRadius()) * (sph1.getRadius() + sph2.getRadius()) + 1000)
		return true;
	else
		return false;
}
