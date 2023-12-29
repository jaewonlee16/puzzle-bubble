#include "CollisionDetection.h"

bool CollisionDetection::operator()(const SolidSphere& sph1, const SolidSphere& sph2) const
{
	if (sph1.state == MOVE || sph2.state == MOVE) {
		float distance = dotProduct(sph1.getCenter() - sph2.getCenter(), sph1.getCenter() - sph2.getCenter());
		if (distance <= (sph1.getRadius() + sph2.getRadius()) * (sph1.getRadius() + sph2.getRadius()) - 10)
			return true;
		else
			return false;
	}
	return false;
}
