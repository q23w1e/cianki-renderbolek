#include <iostream>
#include <algorithm>
#include <utility>

#include "TGAImage/tgaimage.h"
#include "Model/model.h"

const TGAColor black {0, 0, 0, 255};
const TGAColor white {255, 255, 255, 255};
const TGAColor red   {255, 0, 0, 255};
const TGAColor green {0, 255, 0, 255};
const TGAColor blue {0, 0, 255, 255};

int lerp(int a, int b, float t) {
	return (1 - t) * a + t * b;
}

void dda(int x1, int y1, int x2, int y2, const TGAColor& color, TGAImage& canvas) {
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	int dx = x2 - x1;
	int dy = std::abs(y2 - y1);

	int steps = dx > dy ? dx : dy;
	float xi = dx / (float)(steps);
	float yi = dy / (float)(steps);

	for(auto i = 0; i < steps; i++) {
		int x = x1 + (xi * i);
		int y = y1 + (yi * i);
		canvas.set(x, y, color);
	}
}

void line(int x1, int y1, int x2, int y2, const TGAColor& color, TGAImage& canvas) {
	bool steep = false;
	
	if (std::abs(y2 - y1) > std::abs(x2 - x1)) {
		std::swap(x1, y1);
		std::swap(x2, y2);
		steep = true;
	}
	
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	int dx = x2 - x1;
	int dy = std::abs(y2 - y1);
	int derr = dy * 2;
	int err = 0;
	int y = y1;
	
	for (auto x = x1; x <= x2; x++) {
		if (steep) { canvas.set(y, x, color); }
		else { canvas.set(x, y, color); }

		err += derr;
		if (err > dx) {
			y += (y2 > y1) ? 1 : -1;
			err -= dx * 2;
		}
	}
}

void lineMidPoint(int x1, int y1, int x2, int y2, const TGAColor& color, TGAImage& canvas) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	int e = 2 * dy - dx; // e = 2f in order to use only integer arithmetic

	int midX = x1 + dx / 2;
	bool mid_is_odd = midX % 2;
	int midY = dy / 2;
	
	int incrX = x1, incrY = y1, 
		decrX = x2, decrY = y2;

	while (incrX < midX) {
		canvas.set(incrX++, incrY, white);
		canvas.set(decrX--, decrY, red);

		if (e > 0) { e += 2 * (dy - dx); incrY++; decrY--; }
		else { e += 2 * dy; }
	}
	canvas.set(incrX, incrY, green);
	if (mid_is_odd) { canvas.set(decrX, decrY, blue); }
}

void arc8(int r, const TGAColor& color, TGAImage& canvas) {
	int x = 0, 
		y = r, 
		u = 1, // diff between to successive points on x (2*x + 1)
		v = 2 * y - 1, // diff between to successive points on y (2*y - 1)
		E = 0; // error (x^2 + y^2 - r^2)

	while (x <= y) {
		canvas.set(x, y, color);
		
		x += 1; E += u; u += 2;
	
		if (v < 2 * E) { y -= 1; E -= v; v -= 2; }
	}
}


void circle(int Cx, int Cy, int r, const TGAColor& color, TGAImage& canvas) {
	int x = 0, 
		y = r, 
		u = 1, // diff between to successive points on x (2*x + 1)
		v = 2 * y - 1, // diff between to successive points on y (2*y - 1)
		E = 0; // error (x^2 + y^2 - r^2)

	while (x <= y) {
		canvas.set(Cx + x, Cy + y, color);
		canvas.set(Cx - x, Cy + y, color);
		canvas.set(Cx + x, Cy - y, color);
		canvas.set(Cx - x, Cy - y, color);
		
		if (x > y) {
			std::cout << "Stop" << std::endl;
			break;
		}
		canvas.set(Cy + y, Cx + x, color);
		canvas.set(Cy - y, Cx + x, color);
		canvas.set(Cy + y, Cx - x, color);
		canvas.set(Cy - y, Cx - x, color);

		x += 1; E += u; u += 2;
	
		if (v < 2 * E) { y -= 1; E -= v; v -= 2; }
	}
}

int main(int argc, char *argv[]) {
	TGAImage canvas {500, 500, TGAImage::RGB};
	int width = canvas.get_width();
	int height = canvas.get_height();
	
	canvas.flip_vertically();
	canvas.write_tga_file("result.tga");
}