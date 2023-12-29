#include "Vector3f.h"

Vector3f::Vector3f() {
	setPos(0, 0, 0);
}

Vector3f::Vector3f(float x, float y, float z) {
	setPos(x, y, z);
}

void Vector3f::setPos(float x, float y, float z) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

float& Vector3f::operator[](const int i) {
	return pos[i];
}

float Vector3f::operator[](const int i) const {
	return pos[i];
}


Vector3f operator+(const Vector3f& v1, const Vector3f& v2) {
	Vector3f tmp;
	for (int i = 0; i < 3; i++)
		tmp[i] = v1[i] + v2[i];

	return tmp;
}

Vector3f operator-(const Vector3f& v1, const Vector3f& v2) {
	Vector3f tmp;
	for (int i = 0; i < 3; i++)
		tmp[i] = v1[i] - v2[i];

	return tmp;
}

Vector3f operator*(const float s, const Vector3f& vec3) {
	Vector3f tmp;
	tmp.setPos(s * vec3[0], s * vec3[1], s * vec3[2]);

	return tmp;
}

float dotProduct(const Vector3f& v1, const Vector3f& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}