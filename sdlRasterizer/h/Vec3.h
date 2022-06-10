#pragma once

struct Vec3 {
	double x{};
	double y{};
	double z{};

	Vec3 operator+(const Vec3& vec1) const;
	Vec3 operator-(const Vec3& vec1) const;
	Vec3 operator-() const;
	Vec3 operator*(double i) const;
	Vec3 operator/(double i) const;

	static void Swap(Vec3 &v0, Vec3 &v1);
	static double Dot(const Vec3& vec1, const Vec3& vec2);
	static Vec3 Cross(const Vec3& vec1, const Vec3& vec2);
	static double Length(const Vec3& vec);
	static void Rotate(Vec3& vec, const Vec3& rotationVec);
	static double Distance(const Vec3 &from, const Vec3 &to);
};