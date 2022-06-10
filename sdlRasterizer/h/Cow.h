#ifndef COW_H
#define COW_H
#pragma once

#include <h/Object.h>

class Cow : public Object {
	static std::vector<Vec3> Vertices;
	static std::vector<Triangle> Triangles;

public:
	Cow(Vec3 translation = Vec3{}, double scale = 1, Vec3 rotation = Vec3{});
	std::vector<Vec3> GetVertices() const override;
	std::vector<Triangle> GetTriangles() const override;

	Sphere GetBoundingShpere() override;
	static void LoadModel(const char* fileName);
};

#endif COW_H
