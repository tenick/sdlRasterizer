#include "h\Vec3.h"
#include <iostream>

Vec3 Vec3::operator+(const Vec3& vec1) const {
	double x = this->x + vec1.x;
	double y = this->y + vec1.y;
	double z = this->z + vec1.z;
	return Vec3{ x, y, z };
}

Vec3 Vec3::operator-(const Vec3& vec1) const {
	double x = this->x - vec1.x;
	double y = this->y - vec1.y;
	double z = this->z - vec1.z;
	return Vec3{ x, y, z };
}

Vec3 Vec3::operator-() const {
	Vec3 vec{};
	vec.x = -this->x;
	vec.y = -this->y;
	return vec;
}

Vec3 Vec3::operator*(double i) const {
	return Vec3{ this->x * i, this->y * i, this->z * i };
}

Vec3 Vec3::operator/(double i) const {
	return Vec3{ this->x / i, this->y / i, this->z / i };
}

void Vec3::Swap(Vec3& v0, Vec3& v1) {
	Vec3 temp = v0;
	v0 = v1;
	v1 = temp;
}

double Vec3::Dot(const Vec3& vec1, const Vec3& vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
Vec3 Vec3::Cross(const Vec3& vec1, const Vec3& vec2) {
	return {
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	};
}
double Vec3::Length(const Vec3& vec) {
	return sqrt(Vec3::Dot(vec, vec));
}

double Vec3::Distance(const Vec3& from, const Vec3& to) {
	return sqrt(pow(from.y - to.y, 2) + pow(from.x - to.x, 2));
}

void Vec3::Rotate(Vec3& vec, const Vec3& rotationVec) {
	// y-rotation
	vec = {
		vec.x * cos(rotationVec.y) + vec.z * sin(rotationVec.y),
		vec.y,
		-sin(rotationVec.y) * vec.x + cos(rotationVec.y) * vec.z
	};
	// x-rotation
	vec = {
		vec.x,
		vec.y * cos(rotationVec.x) - sin(rotationVec.x) * vec.z,
		sin(rotationVec.x) * vec.y + cos(rotationVec.x) * vec.z
	};
	// z-rotation
}


