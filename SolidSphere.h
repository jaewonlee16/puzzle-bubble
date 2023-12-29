#pragma once

#include "SolidShape3D.h"
# define PI 3.14159265358979

enum Color{RED = 0, GREEN, BLUE, YELLOW, MAGENTA, CYAN};
enum State{NEXT = 11, SHOOTER, MOVE, CEIL, DROP};
enum Remove{NOT_DETECTED, DETECTED, DETECTED_TRUE};

class SolidSphere : public SolidShape3D
{
public:
	SolidSphere(float r, int sl, int st);


	void setRadius(float r);
	float getRadius() const;
	void setSlice(float sl);
	void setStack(float st);
	void setColor(Color& c);
	int getColor() const;

	void initialize();
	void draw() const;


	State state;
	Remove removeDetection;
	bool dropDetection;
	bool afterCollisionHandling;
private:
	float radius;
	int slice;
	int stack;
	Color color;
	
	
};

