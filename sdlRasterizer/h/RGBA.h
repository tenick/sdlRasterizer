#ifndef RGBA_H
#define RGBA_H
#pragma once
struct RGBA {
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;

	RGBA();
	RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	RGBA operator+(const RGBA& color) const;
	RGBA operator*(double i);
};
#endif