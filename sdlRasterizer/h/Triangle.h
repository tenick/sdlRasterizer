#ifndef TRIANGLE_H
#define TRIANGLE_H
#pragma once
#include <h/Vec3.h>
#include <h/RGBA.h>

struct Triangle {
	int V0;
	int V1;
	int V2;
	Vec3 UV0;
	Vec3 UV1;
	Vec3 UV2;
	RGBA Color;
	double H0;
	double H1;
	double H2;
	
	Triangle(int v0, int v1, int v2, RGBA color, Vec3 uv0={}, Vec3 uv1={}, Vec3 uv2 = {}, double h0 = 1, double h1 = 1, double h2 = 1);
};

#endif
