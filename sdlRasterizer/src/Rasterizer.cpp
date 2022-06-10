#include "h/Rasterizer.h"
#include "h/Object.h"
#include <h/Cube.h>
#include <h/Teapot.h>
#include <h/Cow.h>

Rasterizer::Rasterizer() 
{
	SDL_CreateWindowAndRenderer(Camera::canvas_width, Camera::canvas_height, 0, &m_Window, &m_Renderer);
	SDL_RenderPresent(m_Renderer);
}

std::ostream& operator<<(std::ostream& cout, const Vec3& vec) {
	cout << vec.x << ", " << vec.y << ", " << vec.z;
	return cout;
}

static Uint8* pixels;
static int tW = 0, tH = 0, tP = 0;
void Rasterizer::Start() {
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);


	//// testing area
	//Vec3 v1{ 0,0,0 };
	//Vec3 v2{ -50,50,0 };
	//DrawLine(v1, v2);
	//SDL_RenderPresent(m_Renderer);

	//int mouseX, mouseY;
	//while (!quit) {
	//	while (SDL_PollEvent(&m_Event) != 0) {
	//		if (m_Event.type == SDL_MOUSEMOTION) {
	//			
	//			SDL_GetMouseState(&mouseX, &mouseY);

	//			// transform device point to cartesian coordinates
	//			double newX = (double)mouseX - Camera::canvas_width / 2;
	//			double newY = -(mouseY - (Camera::canvas_height / 2 + 1));

	//			v2 = { newX, newY };

	//			SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	//			SDL_RenderClear(m_Renderer);

	//			SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
	//			DrawLine(v1, v2);

	//			SDL_RenderPresent(m_Renderer);
	//		}
	//		

	//	}
	//}
	//return;
	//// testing area done

	// load model and textures
	Teapot::LoadModel(".\\res\\teapot.obj");
	Cow::LoadModel(".\\res\\cow-nonormals.obj");

	SDL_Surface* surface = SDL_LoadBMP(".\\res\\crate-texture.bmp");
	Uint32 pf = SDL_GetWindowPixelFormat(m_Window);
	pixels = copySurfacePixels(surface, pf, m_Renderer, &tW, &tH, &tP);
	if (pixels)
	{
		printf("width=%d, height=%d, pitch=%d\n", tW, tH, tP);

		// Print color at (1,1)
		int x = tW-1, y = tH-1;

		// Assuming BGRA format
		int b = pixels[4 * (y * tW + x) + 0]; // Blue
		int g = pixels[4 * (y * tW + x) + 1]; // Green
		int r = pixels[4 * (y * tW + x) + 2]; // Red
		int a = pixels[4 * (y * tW + x) + 3]; // Alpha
		printf("Pixel at (%d,%d) has RGBA color (%d,%d,%d,%d)\n", x, y, r, g, b, a);
	}
	

	std::vector<Object*> objects;
	/*Cube c1(Vec3{ -7,2,7 });
	c1.m_scale = 1.5;
	Cube c2(Vec3{ 0, 0, 7 });
	Cube c3(Vec3{ 0, 2, 7 });
	Cube c4(Vec3{ 8,2,9 });
	c4.m_rotation = Vec3{ M_PI / 3, M_PI };
	c4.m_scale = 2.5;

	objects.push_back(&c1);
	objects.push_back(&c2);
	objects.push_back(&c3);
	objects.push_back(&c4);*/
	/*Camera::MoveSpeed = .5;
	Cow c1(Vec3{ 0,0,15 });

	objects.push_back(&c1);*/

	/*Camera::MoveSpeed = .5;
	Teapot c1(Vec3{ 0,-1.5, 8 });

	objects.push_back(&c1);*/

	Camera::MoveSpeed = .4;
	Cube c1(Vec3{ 3,-2, 10 });
	c1.m_scale = 2;
	Cube c2(Vec3{ 2.8, 1.2, 10.8 });
	c2.m_rotation = Vec3{0, M_PI / 5 };
	c2.m_scale = 1.3;
	Cube c3(Vec3{ 4.5, .5, 8.5 });
	c3.m_rotation = Vec3{ 0, -M_PI / 7 };
	c3.m_scale = .5;



	Teapot t1(Vec3{ -.5, -4, 10 });
	t1.m_rotation = Vec3{ 0, M_PI / 4};
	t1.m_scale = .5;

	Cow co1(Vec3{ -.5, -1, 15 });
	co1.m_rotation = Vec3{ 0, -M_PI/ 4 + M_PI };
	co1.m_scale = .8;

	objects.push_back(&c1);
	objects.push_back(&c2);
	objects.push_back(&c3);
	objects.push_back(&t1);
	objects.push_back(&co1);

	SDL_RenderPresent(m_Renderer);
	
	// states
	bool panning = false;
	bool movingLeft = false;
	bool movingRight = false;
	bool movingForward = false;
	bool movingBackward = false;
	bool movingUp = false;
	bool movingDown = false;

	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (!quit) {
		Uint32 startTick = SDL_GetTicks();

		while (SDL_PollEvent(&m_Event) != 0) {
			if (m_Event.type == SDL_QUIT) {
				quit = true;
			}
			if (m_Event.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				DrawPoint(Vec3{(double)x, (double)y});
				SDL_RenderPresent(m_Renderer);
			}

			if (m_Event.type == SDL_KEYDOWN) {
				if (m_Event.key.keysym.sym == SDLK_a)
					movingLeft = true;
				if (m_Event.key.keysym.sym == SDLK_d)
					movingRight = true;
				if (m_Event.key.keysym.sym == SDLK_w)
					movingForward = true;
				if (m_Event.key.keysym.sym == SDLK_s)
					movingBackward = true;
				if (m_Event.key.keysym.sym == SDLK_SPACE)
					movingUp = true;
				if (m_Event.key.keysym.sym == SDLK_LSHIFT)
					movingDown = true;
			}

			if (m_Event.type == SDL_KEYUP) {
				if (m_Event.key.keysym.sym == SDLK_a)
					movingLeft = false;
				if (m_Event.key.keysym.sym == SDLK_d)
					movingRight = false;
				if (m_Event.key.keysym.sym == SDLK_w)
					movingForward = false;
				if (m_Event.key.keysym.sym == SDLK_s)
					movingBackward = false;
				if (m_Event.key.keysym.sym == SDLK_SPACE)
					movingUp = false;
				if (m_Event.key.keysym.sym == SDLK_LSHIFT)
					movingDown = false;
			}

			if (m_Event.type == SDL_MOUSEMOTION) {
				Vec3 screenRelOffset{ m_Event.motion.xrel, m_Event.motion.yrel };

				Camera::m_rotation.x += screenRelOffset.y / Camera::canvas_height * M_PI / 3;
				if (Camera::m_rotation.x > M_PI/2)
					Camera::m_rotation.x = M_PI/2;
				if (Camera::m_rotation.x < -M_PI/2)
					Camera::m_rotation.x = -M_PI/2;
				Camera::m_rotation.y += screenRelOffset.x / Camera::canvas_width * M_PI / 3;
			}
		}

	
		if (movingLeft) Camera::MoveLeft();
		if (movingRight) Camera::MoveRight();
		if (movingForward) Camera::MoveForward();
		if (movingBackward) Camera::MoveBackward();
		if (movingUp) Camera::MoveUp();
		if (movingDown) Camera::MoveDown();

		// START RENDER

		// reset depth buffer
		Camera::depth_buffer = std::vector<std::vector<double>>(
			Camera::canvas_height,
			std::vector<double>(Camera::canvas_width, 0)
			);

		// clear current renderer
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
		SDL_RenderClear(m_Renderer);

		// draw all objects
		for (Object*& obj : objects) {
			//obj->m_rotation.x += .001 * obj->m_scale;
			//obj->m_rotation.y += .04 * obj->m_scale;

			std::vector<Vec3> objVertices = obj->GetVertices();
			Sphere boundSphere = obj->GetBoundingShpere();

			// transform vertex to camera space
			Vec3 centerCamSpace = Camera::WorldPtToCameraPt(boundSphere.center);
			double distToNearPlane = Vec3::Dot(Camera::Near, centerCamSpace);
			double distToLeftPlane = Vec3::Dot(Camera::Left, centerCamSpace);
			double distToRightPlane = Vec3::Dot(Camera::Right, centerCamSpace);
			double distToTopPlane = Vec3::Dot(Camera::Top, centerCamSpace);
			double distToBottomPlane = Vec3::Dot(Camera::Bottom, centerCamSpace);
			
			// check if object is inside the planes defined in camera namespace
			if (distToNearPlane < boundSphere.radius || distToLeftPlane < boundSphere.radius || distToRightPlane < boundSphere.radius
				|| distToTopPlane < boundSphere.radius || distToBottomPlane < boundSphere.radius) {
				std::cout << "not fully inside the camera " << std::endl;
				continue;
			}
			

			std::vector<Triangle> objTriangles = obj->GetTriangles();

			for (int i = 0; i < objTriangles.size(); i++) {
				Triangle triDef = objTriangles[i];

				
				Vec3 worldPtTriangleV1 = objVertices[triDef.V0];
				Vec3 worldPtTriangleV2 = objVertices[triDef.V1];
				Vec3 worldPtTriangleV3 = objVertices[triDef.V2];


				// check if triangle is back-facing
				Vec3 cameraPtTriangleV1 = Camera::WorldPtToCameraPt(worldPtTriangleV1);
				Vec3 cameraPtTriangleV2 = Camera::WorldPtToCameraPt(worldPtTriangleV2);
				Vec3 cameraPtTriangleV3 = Camera::WorldPtToCameraPt(worldPtTriangleV3);

				Vec3 triangleVec1 = cameraPtTriangleV2 - cameraPtTriangleV1;
				Vec3 triangleVec2 = cameraPtTriangleV3 - cameraPtTriangleV2;

				Vec3 triangleSurfaceNormal = Vec3::Cross(triangleVec2, triangleVec1);

				if (Vec3::Dot(cameraPtTriangleV1, triangleSurfaceNormal) <= 0) // is back-facing, skip this triangle
					continue;

				Vec3 v0 = Camera::WorldPtToDevicePt(worldPtTriangleV1);
				Vec3 v1 = Camera::WorldPtToDevicePt(worldPtTriangleV2);
				Vec3 v2 = Camera::WorldPtToDevicePt(worldPtTriangleV3);


				// calculate illumination at vertex point
				double h0 = Illuminate(cameraPtTriangleV1, triangleSurfaceNormal);
				double h1 = Illuminate(cameraPtTriangleV2, triangleSurfaceNormal);
				double h2 = Illuminate(cameraPtTriangleV3, triangleSurfaceNormal);

				//// wireframe rendering
				//SDL_SetRenderDrawColor(m_Renderer, triDef.Color.R, triDef.Color.G, triDef.Color.B, 255);
				//DrawWireFrameTriangle(v0, v1, v2);

				// shaded rendering
				if (!(triDef.UV0.x == triDef.UV1.x && triDef.UV1.x == triDef.UV2.x)) {
					DrawTextureMappedTriangle(v0, v1, v2, triDef.UV0, triDef.UV1, triDef.UV2, triDef.Color, h0, h1, h2);
				}
				else
					DrawShadedTriangle(v0, v1, v2, triDef.Color, h0, h1, h2);
			}
		}

		// draw each pixels defined in renderer
		SDL_RenderPresent(m_Renderer);

		// END RENDER


		//// see how fast can sdl put all pixels
		//SDL_RenderClear(m_Renderer);
		//while (SDL_PollEvent(&m_Event) != 0) {

		//}
		//for (int i = 0; i < Camera::canvas_width; i++){
		//	for (int j = 0; j < Camera::canvas_height; j++) {
		//		SDL_SetRenderDrawColor(m_Renderer, (i+j) % 255, (i*j) % 255, (i+j*i*j) % 255, 0);
		//		SDL_RenderDrawPoint(m_Renderer, i, j);
		//	}
		//}
		//SDL_RenderPresent(m_Renderer);
		//// result is about ~20 fps ~50 ms

		Uint32 endTick = SDL_GetTicks();

		float msElapsed = (endTick - startTick);
		int fps = 1000 / msElapsed;
		std::cout << "render took: " << msElapsed << " ms | " << fps << " fps" << std::endl;
	}

	free(pixels);
}

std::vector<double> Rasterizer::Interpolate(int i0, double d0, int i1, double d1) {
	if (i0 == i1){
		return { d0 };
	}

	std::vector<double> values;
	double slope = (d1 - d0) / (double)(i1 - i0);
	double d = d0;

	for (int i = i0; i <= i1; i++){
		values.push_back(d);
		d = d + slope;
	}
	return values;
}

double Rasterizer::Illuminate(const Vec3& intersectPt, const Vec3& normal) {
	Vec3 lightRay = intersectPt;
	double intensity = .9;
	double total_intensity = 0;

	// diffuse reflection
	double n_dot_l = Vec3::Dot(normal, lightRay);
	if (n_dot_l > 0)
		total_intensity += intensity * n_dot_l / (Vec3::Length(normal) * Vec3::Length(intersectPt));
	return total_intensity;
}

void Rasterizer::DrawPoint(const Vec3 &v) {
	SDL_RenderDrawPoint(m_Renderer, v.x, v.y);
}

void Rasterizer::DrawLine(Vec3 v0, Vec3 v1) {
	if (abs(v1.x - v0.x) > abs(v1.y - v0.y)) {
		// Line is horizontal-ish, means there will be always a unique x value for each pixel in the line
		// Make sure x0 < x1
		if (v0.x > v1.x){
			Vec3::Swap(v0, v1);
		}

		// get y values for each x
		std::vector<double> yVals = Interpolate(v0.x, v0.y, v1.x, v1.y);


		for (int x = v0.x; x <= v1.x; x++) {
			Vec3 pixel(x, yVals[x - v0.x]);
			DrawPoint(pixel);
		}
	}
	else {
		// Line is vertical-ish
		// Make sure y0 < y1
		if (v0.y > v1.y) {
			Vec3::Swap(v0, v1);
		}

		// get y values for each x
		std::vector<double> xVals = Interpolate(v0.y, v0.x, v1.y, v1.x);


		for (int y = v0.y; y <= v1.y; y++) {
			Vec3 pixel(xVals[y - v0.y], y);
			DrawPoint(pixel);
		}
	}
}

void Rasterizer::DrawWireFrameTriangle(Vec3& v0, Vec3& v1, Vec3& v2) {
	DrawLine(v0, v1);
	DrawLine(v1, v2);
	DrawLine(v2, v0);
}

void Rasterizer::DrawFilledTriangle(Vec3& v0, Vec3& v1, Vec3& v2) {
	// sort y in ascending order
	if (v0.y > v1.y) Vec3::Swap(v0, v1);
	if (v0.y > v2.y) Vec3::Swap(v0, v2);
	if (v1.y > v2.y) Vec3::Swap(v1, v2);
	

	// get x-values
	std::vector<double> x02 = Interpolate(v0.y, v0.x, v2.y, v2.x);
	std::vector<double> x01 = Interpolate(v0.y, v0.x, v1.y, v1.x);
	std::vector<double> x12 = Interpolate(v1.y, v1.x, v2.y, v2.x);

	x01.pop_back();
	x01.insert(x01.end(), x12.begin(), x12.end());

	// Determine which is left and which is right
	std::vector<double>* xLeft;
	std::vector<double>* xRight;
	int i = floor(x01.size() / 2);
	if (x02[i] < x01[i]){
		xLeft = &x02;
		xRight = &x01;
	}
	else {
		xLeft = &x01;
		xRight = &x02;
	}



	// get z-values
	std::vector<double> z02 = Interpolate(v0.y, 1 / v0.z, v2.y, 1 / v2.z);
	std::vector<double> z01 = Interpolate(v0.y, 1 / v0.z, v1.y, 1 / v1.z);
	std::vector<double> z12 = Interpolate(v1.y, 1 / v1.z, v2.y, 1 / v2.z);

	z01.pop_back();
	z01.insert(z01.end(), z12.begin(), z12.end());

	// Determine which is left and which is right
	std::vector<double>* zLeft;
	std::vector<double>* zRight;
	int i2 = floor(z01.size() / 2);
	if (z02[i2] < z01[i2]) {
		zLeft = &z02;
		zRight = &z01;
	}
	else {
		zLeft = &z01;
		zRight = &z02;
	}


	// Draw the horizontal segments
	for (int y = v0.y; y <= v2.y; y++){
		int startX = (*xLeft)[y - v0.y];
		int endX = (*xRight)[y - v0.y];

		std::vector<double> zSegment = Interpolate(startX, (*zLeft)[y - v0.y], endX, (*zRight)[y - v0.y]);

		for (int x = startX; x <= endX; x++) {
			if (x >= 0 && x < Camera::canvas_width && y >= 0 && y < Camera::canvas_height) {
				double z = zSegment[x - startX];

				if (z > Camera::depth_buffer[y][x]) {
					Vec3 pixel(x, y);
					DrawPoint(pixel);
					Camera::depth_buffer[y][x] = z;
				}
			}
		}
	}

}

void Rasterizer::DrawShadedTriangle(Vec3& v0, Vec3& v1, Vec3& v2, RGBA& color, double h0, double h1, double h2) {
	// sort y in ascending order
	if (v0.y > v1.y) Vec3::Swap(v0, v1);
	if (v0.y > v2.y) Vec3::Swap(v0, v2);
	if (v1.y > v2.y) Vec3::Swap(v1, v2);


	// get x-values
	std::vector<double> x02 = Interpolate(v0.y, v0.x, v2.y, v2.x);
	std::vector<double> x01 = Interpolate(v0.y, v0.x, v1.y, v1.x);
	std::vector<double> x12 = Interpolate(v1.y, v1.x, v2.y, v2.x);

	x01.pop_back();
	x01.insert(x01.end(), x12.begin(), x12.end());


	// get h-values (light intensity of each vertex interpolation)
	std::vector<double> h02 = Interpolate(v0.y, h0, v2.y, h2);
	std::vector<double> h01 = Interpolate(v0.y, h0, v2.y, h1);
	std::vector<double> h12 = Interpolate(v0.y, h1, v2.y, h2);

	h01.pop_back();
	h01.insert(h01.end(), h12.begin(), h12.end());

	// Determine which is left and which is right
	std::vector<double>* xLeft;
	std::vector<double>* xRight;
	std::vector<double>* hLeft;
	std::vector<double>* hRight;
	int i = floor(x01.size() / 2);
	if (x02[i] < x01[i]) {
		xLeft = &x02;
		xRight = &x01;
		hLeft = &h02;
		hRight = &h01;
	}
	else {
		xLeft = &x01;
		xRight = &x02;
		hLeft = &h01;
		hRight = &h02;
	}



	// get z-values
	std::vector<double> z02 = Interpolate(v0.y, 1 / v0.z, v2.y, 1 / v2.z);
	std::vector<double> z01 = Interpolate(v0.y, 1 / v0.z, v1.y, 1 / v1.z);
	std::vector<double> z12 = Interpolate(v1.y, 1 / v1.z, v2.y, 1 / v2.z);

	z01.pop_back();
	z01.insert(z01.end(), z12.begin(), z12.end());

	// Determine which is left and which is right
	std::vector<double>* zLeft;
	std::vector<double>* zRight;
	int i2 = floor(z01.size() / 2);
	if (z02[i2] < z01[i2]) {
		zLeft = &z02;
		zRight = &z01;
	}
	else {
		zLeft = &z01;
		zRight = &z02;
	}


	// Draw the horizontal segments
	for (int y = v0.y; y <= v2.y; y++) {
		int startX = (*xLeft)[y - v0.y];
		int endX = (*xRight)[y - v0.y];

		std::vector<double> zSegment = Interpolate(startX, (*zLeft)[y - v0.y], endX, (*zRight)[y - v0.y]);
		std::vector<double> hSegment = Interpolate(startX, (*hLeft)[y - v0.y], endX, (*hRight)[y - v0.y]);

		for (int x = startX; x <= endX; x++) {
			if (x >= 0 && x < Camera::canvas_width && y >= 0 && y < Camera::canvas_height) {
				double z = zSegment[x - startX];

				if (z > Camera::depth_buffer[y][x]) {
					Vec3 pixel(x, y);
					double h = hSegment[x - startX];

					RGBA shadedColor = color * h;

					SDL_SetRenderDrawColor(m_Renderer, shadedColor.R, shadedColor.G, shadedColor.B, shadedColor.A);

					DrawPoint(pixel);
					Camera::depth_buffer[y][x] = z;
				}
			}
		}
	}

}

void Rasterizer::DrawTextureMappedTriangle(Vec3& v0, Vec3& v1, Vec3& v2, Vec3& t0, Vec3& t1, Vec3& t2, RGBA& color, double h0, double h1, double h2) {
	// sort y in ascending order
	if (v0.y > v1.y) Vec3::Swap(v0, v1);
	if (v0.y > v2.y) Vec3::Swap(v0, v2);
	if (v1.y > v2.y) Vec3::Swap(v1, v2);


	// get x-values
	std::vector<double> x02 = Interpolate(v0.y, v0.x, v2.y, v2.x);
	std::vector<double> x01 = Interpolate(v0.y, v0.x, v1.y, v1.x);
	std::vector<double> x12 = Interpolate(v1.y, v1.x, v2.y, v2.x);

	x01.pop_back();
	x01.insert(x01.end(), x12.begin(), x12.end());


	// get h-values (light intensity of each vertex interpolation)
	std::vector<double> h02 = Interpolate(v0.y, h0, v2.y, h2);
	std::vector<double> h01 = Interpolate(v0.y, h0, v2.y, h1);
	std::vector<double> h12 = Interpolate(v0.y, h1, v2.y, h2);

	h01.pop_back();
	h01.insert(h01.end(), h12.begin(), h12.end());

	// Determine which is left and which is right
	std::vector<double>* xLeft;
	std::vector<double>* xRight;
	std::vector<double>* hLeft;
	std::vector<double>* hRight;
	int i = floor(x01.size() / 2);
	if (x02[i] < x01[i]) {
		xLeft = &x02;
		xRight = &x01;
		hLeft = &h02;
		hRight = &h01;
	}
	else {
		xLeft = &x01;
		xRight = &x02;
		hLeft = &h01;
		hRight = &h02;
	}



	// get z-values
	std::vector<double> z02 = Interpolate(v0.y, 1 / v0.z, v2.y, 1 / v2.z);
	std::vector<double> z01 = Interpolate(v0.y, 1 / v0.z, v1.y, 1 / v1.z);
	std::vector<double> z12 = Interpolate(v1.y, 1 / v1.z, v2.y, 1 / v2.z);

	z01.pop_back();
	z01.insert(z01.end(), z12.begin(), z12.end());

	// Determine which is left and which is right
	std::vector<double>* zLeft;
	std::vector<double>* zRight;
	int i2 = floor(z01.size() / 2);
	if (z02[i2] < z01[i2]) {
		zLeft = &z02;
		zRight = &z01;
	}
	else {
		zLeft = &z01;
		zRight = &z02;
	}


	// get u-values
	std::vector<double> u02 = Interpolate(v0.y, t0.x / v0.z, v2.y, t2.x / v2.z);
	std::vector<double> u01 = Interpolate(v0.y, t0.x / v0.z, v1.y, t1.x / v1.z);
	std::vector<double> u12 = Interpolate(v1.y, t1.x / v1.z, v2.y, t2.x / v2.z);

	u01.pop_back();
	u01.insert(u01.end(), u12.begin(), u12.end());

	// Determine which is left and which is right
	std::vector<double>* uLeft;
	std::vector<double>* uRight;
	int i3 = floor(u01.size() / 2);
	if (u02[i3] < u01[i3]) {
		uLeft = &u02;
		uRight = &u01;
	}
	else {
		uLeft = &u01;
		uRight = &u02;
	}



	// Draw the horizontal segments
	for (int y = v0.y; y <= v2.y; y++) {
		int startX = (*xLeft)[y - v0.y];
		int endX = (*xRight)[y - v0.y];

		std::vector<double> zSegment = Interpolate(startX, (*zLeft)[y - v0.y], endX, (*zRight)[y - v0.y]);
		std::vector<double> hSegment = Interpolate(startX, (*hLeft)[y - v0.y], endX, (*hRight)[y - v0.y]);
		std::vector<double> uSegment = Interpolate(startX, (*uLeft)[y - v0.y], endX, (*uRight)[y - v0.y]);
		
		double v = abs(y - v0.y) / (double)abs((v2.y - v0.y));

		for (int x = startX; x <= endX; x++) {
			if (x >= 0 && x < Camera::canvas_width && y >= 0 && y < Camera::canvas_height) {
				double z = zSegment[x - startX];
				double u = uSegment[x - startX];
				
				if (z > Camera::depth_buffer[y][x]) {
					Vec3 pixel(x, y);
					Vec3 texel(u, v);
					int u = abs(texel.x / z * tW - 1);
					int v = abs(texel.y * tH - 1);

					if (v >= tH)
						v = tH - 1;

					//std::cout << u << ", " << v << std::endl;

					double h = hSegment[x - startX];

					// get texel color at (u,v)
					// Assuming BGRA format
					int b = pixels[4 * (v * tW + u) + 0]; // Blue
					int g = pixels[4 * (v * tW + u) + 1]; // Green
					int r = pixels[4 * (v * tW + u) + 2]; // Red
					int a = pixels[4 * (v * tW + u) + 3]; // Alpha


					RGBA shadedColor = RGBA(r, g, b, 255) * h;

					SDL_SetRenderDrawColor(m_Renderer, shadedColor.R, shadedColor.G, shadedColor.B, shadedColor.A);

					DrawPoint(pixel);
					Camera::depth_buffer[y][x] = z;
				}
			}
		}
	}

}

Uint8* Rasterizer::copySurfacePixels(
	SDL_Surface* surface,  // surface to take pixels from
	Uint32 pixelFormat,    // usually SDL_GetWindowPixelFormat(window)
	SDL_Renderer* renderer,// main SDL2 renderer
	int* width,            // stores result width
	int* height,           // stores result height
	int* pitch)            // stores result pitch
{
	Uint8* pixels = 0;
	SDL_Surface* tmpSurface = 0;
	SDL_Texture* texture = 0;
	int sizeInBytes = 0;
	void* tmpPixels = 0;
	int tmpPitch = 0;

	tmpSurface = SDL_ConvertSurfaceFormat(surface, pixelFormat, 0);
	if (tmpSurface) {
		texture = SDL_CreateTexture(renderer, pixelFormat,
			SDL_TEXTUREACCESS_STREAMING,
			tmpSurface->w, tmpSurface->h);
	}

	if (texture) {
		if (width) {
			*width = tmpSurface->w;
		}
		if (height) {
			*height = tmpSurface->h;
		}
		if (pitch) {
			*pitch = tmpSurface->pitch;
		}
		sizeInBytes = tmpSurface->pitch * tmpSurface->h;
		pixels = (Uint8*)malloc(sizeInBytes);
		SDL_LockTexture(texture, 0, &tmpPixels, &tmpPitch);
		memcpy(pixels, tmpSurface->pixels, sizeInBytes);
		SDL_UnlockTexture(texture);
	}

	// Cleanup
	if (texture) {
		SDL_DestroyTexture(texture);
	}
	if (tmpSurface) {
		SDL_FreeSurface(tmpSurface);
	}

	return pixels;
}

Rasterizer::~Rasterizer() {
	//Destroy window
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}