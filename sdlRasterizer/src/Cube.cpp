#pragma once
#include <h/Cube.h>

std::vector<Vec3> Cube::Vertices {
	Vec3 { 1,  1,  1 },
	Vec3 { -1,  1,  1 },
	Vec3 { -1, -1,  1 },
	Vec3 { 1, -1,  1 },
	Vec3 { 1,  1, -1 },
	Vec3 { -1,  1, -1 },
	Vec3 { -1, -1, -1 },
	Vec3 { 1, -1, -1 }
};

std::vector<Triangle> Cube::Triangles {
	{ 0, 1, 2, {255, 0, 0, 255}, {1, 0}, {0, 0}, {0, 1} },
	{ 0, 2, 3, {255, 0, 0, 255}, {1, 0}, {0, 1}, {1, 1} },
	{ 4, 0, 3, {0, 255, 0, 255}, {1, 0}, {0, 0}, {0, 1} },
	{ 4, 3, 7, {0, 255, 0, 255}, {1, 0}, {0, 1}, {1, 1} },
	{ 5, 4, 7, {0, 0, 255, 255}, {1, 0}, {0, 0}, {0, 1} },
	{ 5, 7, 6, {0, 0, 255, 255}, {1, 0}, {0, 1}, {1, 1} },
	{ 1, 5, 6, {255, 255, 0, 255}, {1, 0}, {0, 0}, {0, 1} },
	{ 1, 6, 2, {255, 255, 0, 255}, {1, 0}, {0, 1}, {1, 1} },
	{ 4, 5, 1, {255, 0, 255, 255}, {1, 0}, {0, 0}, {0, 1} },
	{ 4, 1, 0, {255, 0, 255, 255}, {1, 0}, {0, 1}, {1, 1} },
	{ 2, 6, 7, {0, 255, 255, 255}, {1, 0}, {0, 0}, {0, 1} },
	{ 2, 7, 3, {0, 255, 255, 255}, {1, 0}, {0, 1}, {1, 1} }
};



Cube::Cube(Vec3 translation, double scale, Vec3 rotation) 
	: Object(translation, scale, rotation) {}

std::vector<Triangle> Cube::GetTriangles() const { 
	return Triangles; 
}

std::vector<Vec3> Cube::GetVertices() const {
	// scale
	std::vector<Vec3> verts = Vertices;
	Scale(verts, m_scale);
	Rotate(verts, m_rotation);
	Translate(verts, m_translation);
	return verts;
}

Sphere Cube::GetBoundingShpere() {
	int xSum = 0;
	int ySum = 0;
	int zSum = 0;
	std::vector<Vec3> verts = GetVertices();
	int size = verts.size();
	for (Vec3& vec : verts) {
		xSum += vec.x;
		ySum += vec.y;
		zSum += vec.z;
	}

	Vec3 center = Vec3( xSum, ySum, zSum ) / size;

	double radius = -1;
	for (Vec3& vec : verts) {
		double currDist = Vec3::Distance(center, vec);
		if (currDist > radius)
			radius = currDist;
	}

	return Sphere(center, radius);
}

