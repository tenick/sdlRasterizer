#ifndef SPHERE_H
#define SPHERE_H
#pragma once
#include <h/Vec3.h>

struct Sphere {
	Vec3 center;
	double radius;

	Sphere();
	Sphere(Vec3 cPt, double r);
};
#endif
