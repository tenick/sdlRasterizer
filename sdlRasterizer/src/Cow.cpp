#pragma once
#include <h/Cow.h>
#include <h/OBJParser.h>


Cow::Cow(Vec3 translation, double scale, Vec3 rotation)
	: Object(translation, scale, rotation) {}

std::vector<Triangle> Cow::GetTriangles() const {
	return Triangles;
}

std::vector<Vec3> Cow::GetVertices() const {
	// scale
	std::vector<Vec3> verts = Vertices;
	Scale(verts, m_scale);
	Rotate(verts, m_rotation);
	Translate(verts, m_translation);
	return verts;
}


Sphere Cow::GetBoundingShpere() {
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

	Vec3 center = Vec3(xSum, ySum, zSum) / size;

	double radius = -1;
	for (Vec3& vec : verts) {
		double currDist = Vec3::Distance(center, vec);
		if (currDist > radius)
			radius = currDist;
	}

	return Sphere(center, radius);
}


std::vector<Vec3> Cow::Vertices;

std::vector<Triangle> Cow::Triangles;

void Cow::LoadModel(const char* fileName) {
	OBJParser::Parse(fileName);

	Vertices = OBJParser::GetVertices();
	Triangles = OBJParser::GetTriangles();
}

