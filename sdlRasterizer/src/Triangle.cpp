#include <h/Triangle.h>

Triangle::Triangle(int v0, int v1, int v2, RGBA color, Vec3 uv0, Vec3 uv1, Vec3 uv2, double h0, double h1, double h2) :
	V0(v0), V1(v1), V2(v2), Color(color), UV0(uv0), UV1(uv1), UV2(uv2), H0(h0), H1(h1), H2(h2) {}