#include "CollisionHandling.h"


void CollisionHandling::operator()(SolidSphere& sph1, SolidSphere& sph2)
{
	CollisionDetection cldetection;
	if (cldetection(sph1, sph2)) {
		sph1.setVelocity(Vector3f(0, 0, 0));
		sph2.setVelocity(Vector3f(0, 0, 0));
		SolidSphere curr(40, 100, 100);

		if (sph1.state == MOVE) {
			float curr_x = sph1.getCenter()[0];
			float curr_y = sph1.getCenter()[1];
			int stop_x = sph2.getCenter()[0];
			int stop_y = sph2.getCenter()[1];
			int radius = sph2.getRadius();

			// if ¿·¿¡
			if (stop_y - curr_y < radius * ROOT3 / 2)
				curr_x > stop_x ? sph1.setCenter(Vector3f(stop_x + 2 * radius, stop_y, 0))
								: sph1.setCenter(Vector3f(stop_x - 2 * radius, stop_y, 0));
			// ºñ½ºµëÈ÷
			else {
				curr_x > stop_x ? sph1.setCenter(Vector3f(stop_x + radius, stop_y - ROOT3 * radius, 0))
								: sph1.setCenter(Vector3f(stop_x - radius, stop_y - ROOT3 * radius, 0));
			}
			//------------------------------------------------------------------------
			// sph1.state = CEIL;
			sph1.afterCollisionHandling = true;
		}

		else {
			float curr_x = sph2.getCenter()[0];
			float curr_y = sph2.getCenter()[1];
			int stop_x = sph1.getCenter()[0];
			int stop_y = sph1.getCenter()[1];
			int radius = sph1.getRadius();

			// if ¿·¿¡
			if (stop_y - curr_y < radius * ROOT3 / 2)
				curr_x > stop_x ? sph2.setCenter(Vector3f(stop_x + 2 * radius, stop_y, 0))
								: sph2.setCenter(Vector3f(stop_x - 2 * radius, stop_y, 0));
			// ºñ½ºµëÈ÷
			else {
				curr_x > stop_x ? sph2.setCenter(Vector3f(stop_x + radius, stop_y - ROOT3 * radius, 0))
								: sph2.setCenter(Vector3f(stop_x - radius, stop_y - ROOT3 * radius, 0));
			}
		}

		// ------------------------------------------------------------------------ 
		//sph2.state = CEIL;
		sph2.afterCollisionHandling = true;
	}
	

}
