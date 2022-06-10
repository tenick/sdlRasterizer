#ifndef CUBE_H
#define CUBE_H
#pragma once
#include <h/Object.h>

class Cube : public Object {
	static std::vector<Vec3> Vertices;
	static std::vector<Triangle> Triangles;
	static std::vector<Vec3> UV;

public:
	Cube(Vec3 translation = Vec3{}, double scale = 1, Vec3 rotation = Vec3{});
	std::vector<Vec3> GetVertices() const override;
	std::vector<Triangle> GetTriangles() const override;
	Sphere GetBoundingShpere() override;
};

#endif