#include <h/Camera.h>

namespace Camera {
	Vec3 Position{ 0, 0, 0 }; // means camera hasn't been moved yet (usually via keyboard WASD or arrow keys)
	Vec3 m_rotation{ 0, 0, 0 }; // means camera hasn't been rotated yet (usually via mouse movements)
	
	double MoveSpeed{.1};

	double canvas_width = 600;
	double canvas_height = 600;

	double viewport_width = 1;
	double viewport_height = 1;
	double viewport_distance = 1;

	std::vector<std::vector<double>> depth_buffer = std::vector<std::vector<double>>(
		canvas_height,
		std::vector<double>(canvas_width, 0)
	);

	
	// plane normals
	Vec3 Near{ 0, 0, 1 };
	Vec3 Left{ 1/sqrt(2), 0, 1/sqrt(2) };
	Vec3 Right{ -1/sqrt(2), 0, 1/sqrt(2) };
	Vec3 Bottom{ 0, 1/sqrt(2), 1/sqrt(2) };
	Vec3 Top{ 0, -1/sqrt(2), 1/sqrt(2) };
	
	Vec3 WorldPtToCameraPt(const Vec3& worldPt) {
		Vec3 newVec = worldPt - Position;
		Vec3::Rotate(newVec, -m_rotation);
		return newVec;
	}

	Vec3 WorldPtToViewportPt(const Vec3& worldPt) {
		Vec3 newVec = WorldPtToCameraPt(worldPt);
		return {
			newVec.x * viewport_distance / newVec.z,
			newVec.y * viewport_distance / newVec.z,
			newVec.z
		};
	}

	Vec3 ViewportPtToCanvasPt(const Vec3& viewportPt) {
		return {
			viewportPt.x * canvas_width / viewport_width,
			viewportPt.y * canvas_height / viewport_height,
			viewportPt.z
		};
	}
	Vec3 CanvasPtToViewportPt(const Vec3& canvasPt) {
		return {
			canvasPt.x * viewport_width / canvas_width,
			canvasPt.y * viewport_height / canvas_height,
			canvasPt.z
		};
	}

	Vec3 CanvasPtToDevicePt(const Vec3& canvasPt) {
		return { canvas_width / 2 + canvasPt.x, canvas_height / 2 - canvasPt.y, canvasPt.z };
	}
	Vec3 DevicePtToCanvasPt(const Vec3& devicePt) {
		return { devicePt.x - canvas_width / 2, canvas_height / 2 - devicePt.y, devicePt.z };
	}


	Vec3 WorldPtToDevicePt(const Vec3 &worldPt) {
		return CanvasPtToDevicePt(ViewportPtToCanvasPt(WorldPtToViewportPt(worldPt)));
	}



	void Move(Vec3 direction, Vec3 rotation={0,0,0}) {
		Vec3 newPos = direction;
		Vec3::Rotate(newPos, m_rotation + rotation);
		Camera::Position = Camera::Position + newPos * MoveSpeed;
	}

	void MoveLeft() {
		Move({0, 0, 1}, { -m_rotation.x, -M_PI / 2, -m_rotation.z });
	}
	void MoveRight() {
		Move({ 0, 0, 1 }, { -m_rotation.x, M_PI / 2, -m_rotation.z });
	}
	void MoveForward() {
		Move({ 0, 0, 1 }, { -m_rotation.x, 0, -m_rotation.z });
	}
	void MoveBackward() {
		Move({ 0, 0, 1 }, { -m_rotation.x, M_PI, -m_rotation.z });
	}
	void MoveUp() {
		Move({ 0, 1, 0 }, -m_rotation);
	}
	void MoveDown() {
		Move({ 0, -1, 0 }, -m_rotation);
	}
}