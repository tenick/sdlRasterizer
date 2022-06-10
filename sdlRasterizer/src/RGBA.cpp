#include <h/RGBA.h>

RGBA::RGBA() {
	R = 0; G = 0; B = 0; A = 0;
}
RGBA::RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	R = r; G = g; B = b; A = a;
}

RGBA RGBA::operator+(const RGBA& color) const {
	return RGBA(this->R + color.R, this->G + color.G, this->B + color.B, this->A);
}
RGBA RGBA::operator*(double i) {
	return RGBA(this->R * i, this->G * i, this->B * i, this->A);
}