#include <iostream>
#include <utility>

#include "TGAImage/tgaimage.h"

const TGAColor black {0, 0, 0, 255};
const TGAColor white {255, 255, 255, 255};
const TGAColor red   {255, 0, 0, 255};
const TGAColor green {0, 255, 0, 255};

TGAImage canvas {500, 500, TGAImage::RGB};

struct Point { 
	int x; 
	int y;
	TGAColor color;
};

int lerp(int a, int b, float t) {
	return (1 - t) * a + t * b;
}

void dda(int x1, int y1, int x2, int y2, const TGAColor& color) {
	if (x1 > x2 || y1 > y2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	int dx = x2 - x1;
	int dy = y2 - y1;

	int dp = dx > dy ? dx : dy;
	if (dp == 0) { canvas.set(x1, x2, color); return; }

	float step = 1.0 / dp;
	for(size_t i = 0; i < dp; i++) {
		int x = lerp(x1, x2, i * step);
		int y = lerp(y1, y2, i * step);
		canvas.set(x, y, color);
	}
}

int main(int argc, char *argv[]) {
	Point p1 {100, 150, red};
	Point p2 {300, 250, red};
	dda(p1.x, p1.y, p2.x, p2.y, p1.color);
	
	Point p3 {400, 0, white};
	Point p4 {450, 500, white};
	dda(p3.x, p3.y, p4.x, p4.y, p3.color);

	canvas.flip_vertically();
	canvas.write_tga_file("result.tga");
}