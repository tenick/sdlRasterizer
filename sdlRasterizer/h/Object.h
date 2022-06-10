#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include <array>
#include <vector>
#include <h/Vec3.h>
#include <h/Sphere.h>
#include <h/Triangle.h>

class Object {
protected:
	Object(Vec3 translation = Vec3{}, double scale = 1, Vec3 rotation = Vec3{})
		: m_translation(translation), m_scale(scale), m_rotation(rotation) {}
	
public:
	virtual std::vector<Vec3> GetVertices() const = 0;
	virtual std::vector<Triangle> GetTriangles() const = 0;

	virtual Sphere GetBoundingShpere() = 0;

	
	static void Translate(std::vector<Vec3> &vertices, Vec3 translation) {
		for (Vec3& vec : vertices) {
			vec = vec + translation;
		}
	}

	static void Scale(std::vector<Vec3>& vertices, double scale) {
		for (Vec3& vec : vertices) {
			vec = vec * scale;
		}
	}

	static void Rotate(std::vector<Vec3>& vertices, Vec3 rotation) {
		for (Vec3& vec : vertices) {
			Vec3::Rotate(vec, rotation);
		}
	}

	Vec3 m_translation;
	double m_scale;
	Vec3 m_rotation;
};

#endif
