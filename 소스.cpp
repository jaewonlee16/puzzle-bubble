#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <math.h>
#include <FreeImage.h>
#include <time.h>


#include "CollisionHandling.h"
#include "SolidSphere.h"
#include "Shooter.h"
#include "Light.h"
#include "SearchDetection.h"
#include "Timer.h"

using namespace std;

#define WIDTH 640
#define HEIGHT 800

#define boundaryX WIDTH/2
#define boundaryY HEIGHT/2

#define velocityNORM 5

static GLuint textureID;
GLubyte* textureData;
int imageWidth, imageHeight;

clock_t start = clock();
clock_t endT;
clock_t startShoot = clock();
clock_t shootT;

vector<SolidSphere> spheres;
vector<Material> sphereColors;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
Shooter bubbleShooter;

CollisionHandling clHandling;

Timer timer(8);

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis(0, 5);

bool isEndProgram = false;


void draw_characters(void* font, const char* c, float x, float y) {
	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(c); i++)
		glutBitmapCharacter(font, c[i]);
}


FIBITMAP* createBitMap(char const* filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);

	if (format == -1) {
		cout << "Could not find image: " << filename << " - Aborting." << endl;
		exit(-1);
	}

	if (format == FIF_UNKNOWN) {
		cout << "Couldn't determine file format - attempting to get from file extension..." << endl;
		format = FreeImage_GetFIFFromFilename(filename);

		if (!FreeImage_FIFSupportsReading(format)) {
			cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}

	FIBITMAP* bitmap = FreeImage_Load(format, filename);

	int bitsPerPixel = FreeImage_GetBPP(bitmap);

	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << endl;
		bitmap32 = bitmap;
	}
	else {
		cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 32-bit colour." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}

	return bitmap32;
}

void generateTexture() {
	/* Implement */
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
		0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}

void initTexture() {
	/* Implement */
	FIBITMAP* bitmap32 = createBitMap("Bubble.jpg");
	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);
	generateTexture();
}

void removeDetect(const vector<SolidSphere>::iterator& it) {
	SearchDetection search;

	for (auto iterator = spheres.begin(); iterator != spheres.end(); iterator++) {
		if (search(*it, *iterator)) {
			if (iterator->removeDetection == DETECTED)
				continue;
			else if (iterator->removeDetection == DETECTED_TRUE)
				continue;
			else if (iterator->removeDetection == NOT_DETECTED) {
				if (it->getColor() == iterator->getColor()) {

					iterator->removeDetection = DETECTED_TRUE;
					removeDetect(iterator);
				}
				else {
					iterator->removeDetection = DETECTED;
				}
			}
		}
	}
	// --------------------------
}

void searchDropSpheres(const vector<SolidSphere>::iterator& it) {
	SearchDetection search;

	for (auto nextIt = spheres.begin(); nextIt != spheres.end(); nextIt++) {
		if (search(*it, *nextIt)) {
			if (nextIt->dropDetection)
				continue;
			else {
				nextIt->dropDetection = true;
				searchDropSpheres(nextIt);
			}
		}
	}
}

void processSpecialKeys(int key, int x, int y) {
	auto it = spheres.begin();
	if (spheres.size() >= 2)
		it = spheres.end() - 2;
	float a = bubbleShooter.getAngle();
	it->setAngle(a);
	if (!isEndProgram) {
		switch (key) {
		case GLUT_KEY_RIGHT:
			bubbleShooter.rotate(ROTATE_RIGHT);
			it->rotate(ROTATE_RIGHT);
			break;
		case GLUT_KEY_LEFT:
			bubbleShooter.rotate(ROTATE_LEFT);
			it->rotate(ROTATE_LEFT);
			break;
		case GLUT_KEY_UP:
			if (spheres.size() > 1) {
				it->state = MOVE;
				it->setVelocity(velocityNORM * Vector3f(cos(it->getAngle() * PI / 180), sin(it->getAngle() * PI / 180), 0));
				it->state = MOVE;
				startShoot = shootT;
			}
			

		}
	}
	
}

void init() {
	initTexture();
	light.setAmbient(0.5, 0.5, 0.5, 1.0);
	light.setDiffuse(0.7, 0.7, 0.7, 1.0);
	light.setSpecular(1.0, 1.0, 1.0, 1.0);

	Material mtl1;
	mtl1.setEmission(0.1, 0.1, 0.1, 1);
	mtl1.setAmbient(1, 0.1, 0.1, 1);
	mtl1.setDiffuse(0.5, 0.5, 0.5, 1);
	mtl1.setSpecular(1.0, 1.0, 1.0, 1);
	mtl1.setShininess(10);

	Material mtl2(mtl1), mtl3(mtl1), mtl4(mtl1), mtl5(mtl1), mtl6(mtl1);
	mtl2.setAmbient(0.1, 1, 0.1, 1);
	mtl3.setAmbient(0.1, 0.1, 1, 1);
	mtl4.setAmbient(1, 1, 0.1, 1);
	mtl5.setAmbient(1, 0.1, 1, 1);
	mtl6.setAmbient(0.1, 1, 1, 1);

	sphereColors = { mtl1, mtl2, mtl3, mtl4, mtl5, mtl6 };

	SolidSphere sphere1(40, 100, 100);
	Color c1 = (Color)dis(gen);
	sphere1.setMTL(sphereColors[c1]);
	sphere1.setColor(c1);
	sphere1.state = SHOOTER;
	spheres.push_back(sphere1);

	SolidSphere sphere2(sphere1);
	Color c2 = (Color)dis(gen);
	sphere2.setMTL(sphereColors[c2]);
	sphere2.setColor(c2);
	sphere2.state = NEXT;
	spheres.push_back(sphere2);

	/*for (auto& sp : spheres)
		sp.initialize();*/

	timer.setMtl(sphereColors[0]);

}

void idle() {
	endT = clock();
	for (auto sp : spheres) {
		if (sp.getVelocity()[0] == 0 && sp.getVelocity()[1] == 0) {
			if (sp.getCenter()[1] < -190 && sp.state == CEIL) {
				isEndProgram = true;
				break;
			}
		}
	}


	if (endT - start > 1) {
		auto it = spheres.begin();
		if (spheres.size() >= 2)
			it = spheres.end() - 2;
		int drop_cnt = 0;

		// collision handling
		for (int i = 0; i < spheres.size(); i++)
			for (int j = i + 1; j < spheres.size(); j++)
				clHandling(spheres[i], spheres[j]);


		// BOUNDARY
		for (auto& sph : spheres) {
			if (sph.getCenter()[0] + sph.getRadius() >= boundaryX ||
				sph.getCenter()[0] - sph.getRadius() <= -boundaryX)
				sph.setVelocity(Vector3f(-sph.getVelocity()[0], sph.getVelocity()[1], sph.getVelocity()[2]));

			if (sph.getCenter()[1] + sph.getRadius() >= boundaryY) {
				sph.setVelocity(Vector3f(0, 0, 0));
				int xTmp = (80 * (int)(sph.getCenter()[0] / 80));
				sph.setCenter(Vector3f(sph.getCenter()[0] >= 0 ? xTmp + 40 : xTmp - 40, 360, 0));
				// sph.state = CEIL;
				sph.afterCollisionHandling = true;
			}
			sph.move();
		}


		// REMOVE
		if (it->state == MOVE && it->afterCollisionHandling == true) {
			if (it->getVelocity()[0] == 0 && it->getVelocity()[1] == 0) {

				// ------------------------------------------------------
				// ¼öÁ¤
				it->removeDetection = DETECTED_TRUE;
				removeDetect(it);
				int remove_cnt = 0;
				for (auto& sp : spheres) {
					if (sp.removeDetection == DETECTED_TRUE)
						remove_cnt++;
				}
					// ----------------------------------------------------------
				if (remove_cnt >= 3) {
					auto remove_it = spheres.begin();
					while (remove_it != spheres.end()) {
						if (remove_it->removeDetection == DETECTED_TRUE)
							remove_it = spheres.erase(remove_it);
						else
							++remove_it;
					}

					//   -------------------- DROP ---------------------
					for (auto dropIt = spheres.begin(); dropIt != spheres.end(); dropIt++) {
						if (dropIt->getCenter()[1] >= 340) {
							dropIt->dropDetection = true;
							searchDropSpheres(dropIt);
						}
					}

					for (auto& sph : spheres) {
						if (sph.state == CEIL) {
							if (!sph.dropDetection) {
								drop_cnt++;
								sph.state = DROP;
							}

						}

					}

					for (auto& sp : spheres) {
						sp.initialize();
					}
				}
				else
					it->state = CEIL;


				for (auto iterator = spheres.begin(); iterator != spheres.end(); iterator++) {
						iterator->removeDetection = NOT_DETECTED;
				}
			}
		}

		// DROP Erase ----------------------------------------------------

		auto dropIt = spheres.begin();
		while (dropIt != spheres.end()) {
			if (dropIt->state == DROP && dropIt->getCenter()[1] < -200)
				dropIt = spheres.erase(dropIt);
			else
				dropIt++;
		}

		for (auto& sp : spheres) {
			sp.dropDetection = false;
		}
		


		start = endT;
	}

	shootT = clock();

	// TIME shoot
	if (shootT - startShoot > 7000) {
		processSpecialKeys(GLUT_KEY_UP, 0, 0);
	}
	auto it = spheres.begin();
	if (spheres.size() >= 2)
		it = spheres.end() - 2;

	if (spheres.size() != 1) {
		if (it->state != MOVE && !isEndProgram) {
			if (shootT - startShoot >= 6950) {
				timer.setWidth(0);
			}
			else if (shootT - startShoot > 6000) {
				timer.setWidth(1);
			}
			else if (shootT - startShoot > 5000) {
				timer.setWidth(2);
			}
			else if (shootT - startShoot > 4000) {
				timer.setWidth(3);
			}
			else if (shootT - startShoot > 3000) {
				timer.setWidth(4);
			}
			else if (shootT - startShoot > 2000) {
				timer.setWidth(5);
			}
			else if (shootT - startShoot > 1000) {
				timer.setWidth(6);
			}
			else if (shootT - startShoot > 0) {
				timer.setWidth(7);
			}
		}
	}
	glutPostRedisplay();
}

void drawSquareWithTexture() {
	/* Implement */
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-boundaryX, -boundaryY * 188 / 268 + 110, 0.0);
	glTexCoord2f(0, 1); glVertex3f(-boundaryX, boundaryY , 0.0);
	glTexCoord2f(1, 1); glVertex3f(boundaryX, boundaryY, 0.0);
	glTexCoord2f(1, 0); glVertex3f(boundaryX, -boundaryY * 188 / 268 + 110, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void renderScene() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw 2D
	drawSquareWithTexture();

	// Draw 3D
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(light.getID());
	light.draw();


	auto itEnd = spheres.end();
	if (isEndProgram)
		draw_characters(GLUT_BITMAP_TIMES_ROMAN_24, "FAILED", -50, -360);

	if (spheres.size() == 1) {
		/*spheres[0].state = SHOOTER;
		SolidSphere tmp(40, 100, 100);
		Color c = (Color)dis(gen);
		tmp.setMTL(sphereColors[c]);
		tmp.setColor(c);
		spheres.push_back(tmp);*/

		draw_characters(GLUT_BITMAP_TIMES_ROMAN_24, "COMPLETE", -50, -360);
	}
	else if ((itEnd - 2)->state == CEIL && isEndProgram == false) {
		(itEnd - 1)->state = SHOOTER;
		SolidSphere tmp(40, 100, 100);
		Color c = (Color)dis(gen);
		tmp.setMTL(sphereColors[c]);
		tmp.setColor(c);
		spheres.push_back(tmp);
		startShoot = shootT;

	}
	bubbleShooter.draw();
	float a = bubbleShooter.getAngle();

	for (auto& sp : spheres) {
		sp.initialize();                          //--------------------------------------------------------------------
		if (sp.state == SHOOTER)
			sp.setAngle(a);
		sp.draw();
	}
	
	// Timer ------------------------
	timer.draw();
	draw_characters(GLUT_BITMAP_TIMES_ROMAN_24, "TIME", 130, -315);


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(light.getID());

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(1000, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Collision handling & Texturing");
	init();

	// register callbacks
	glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
