#ifndef CAMERA_H
#define CAMERA_H
#pragma once
#include <h/Vec3.h>
#include <cmath>
#include <vector>
#include <limits>
# define M_PI 3.14159265358979323846

namespace Camera {
	extern Vec3 Position;
	extern double MoveSpeed;

	extern double canvas_width;
	extern double canvas_height;

	extern double viewport_width;
	extern double viewport_height;
	extern double viewport_distance;

	extern std::vector<std::vector<double>> depth_buffer;

	extern Vec3 m_rotation;

	// plane normals
	extern Vec3 Near;
	extern Vec3 Left;
	extern Vec3 Right;
	extern Vec3 Bottom;
	extern Vec3 Top;

	extern Vec3 WorldPtToCameraPt(const Vec3& worldPt);
	extern Vec3 WorldPtToViewportPt(const Vec3& worldPt);
	extern Vec3 ViewportPtToCanvasPt(const Vec3& viewportPt);
	extern Vec3 CanvasPtToViewportPt(const Vec3& viewportPt);
	extern Vec3 CanvasPtToDevicePt(const Vec3& worldPt);
	extern Vec3 DevicePtToCanvasPt(const Vec3& worldPt);
	extern Vec3 WorldPtToDevicePt(const Vec3& worldPt);

	extern void MoveLeft();
	extern void MoveRight();
	extern void MoveForward();
	extern void MoveBackward();
	extern void MoveUp();
	extern void MoveDown();
}

#endif