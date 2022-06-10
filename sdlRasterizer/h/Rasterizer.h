#pragma once
#include "h/Vec3.h"
#include "h/Camera.h"
#include "h/RGBA.h"
#include "h/OBJParser.h"
#include <SDL.h>
#include <vector>
#include <iostream>

class Rasterizer {
	//The window we'll be rendering to
	SDL_Window* m_Window = nullptr;

	// The renderer tied to the window
	SDL_Renderer* m_Renderer = nullptr;

	//Event handler
	SDL_Event m_Event;

	bool quit = false;

public:
	Rasterizer();
	void Start();
	void DrawPoint(const Vec3 &v);
	void DrawLine(Vec3 v0, Vec3 v1);
	std::vector<double> Interpolate(int i0, double d0, int i1, double d1);
	void DrawWireFrameTriangle(Vec3 &v0, Vec3 &v1, Vec3 &v2);
	void DrawFilledTriangle(Vec3& v0, Vec3& v1, Vec3& v2);
	void DrawShadedTriangle(Vec3& v0, Vec3& v1, Vec3& v2, RGBA &color, double h0 = 1, double h1 = 1, double h2 = 1);
	void DrawTextureMappedTriangle(Vec3& v0, Vec3& v1, Vec3& v2, Vec3& t0, Vec3& t1, Vec3& t2, RGBA& color, double h0, double h1, double h2);
	Uint8* copySurfacePixels(  // https://stackoverflow.com/questions/23367098/getting-the-sdl-color-of-a-single-pixel-in-a-sdl-texture
		SDL_Surface* surface,  // surface to take pixels from
		Uint32 pixelFormat,    // usually SDL_GetWindowPixelFormat(window)
		SDL_Renderer* renderer,// main SDL2 renderer
		int* width,            // stores result width
		int* height,           // stores result height
		int* pitch);            // stores result pitch
	double Illuminate(const Vec3& intersectPt, const Vec3& normal);
	~Rasterizer();
};