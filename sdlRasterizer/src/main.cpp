#include "h/Rasterizer.h"

int main(int argc, char* args[]) {
	Rasterizer r{};
	r.Start();
	r.~Rasterizer();

	return 0;
}