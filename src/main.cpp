#include <iostream>
#include "TGAImage/tgaimage.h"

const TGAColor black {0, 0, 0, 255};
const TGAColor white {255, 255, 255, 255};
const TGAColor red   {255, 0, 0, 255};
const TGAColor green {0, 255, 0, 255};

struct Point { 
	int x; 
	int y;
	TGAColor color;
};

void drawLineSegment(TGAImage& image, const Point& p1, const Point& p2) {
	const Point* begin;
	const Point* end; 

	if (p1.x > p2.x || p1.y > p2.y) {
		begin = &p2;
		end = &p1;
	} else {
		begin = &p1;
		end = &p2;
	}

	int dx = end->x - begin->x;
	int dy = end->y - begin->y;

	int dp = dx > dy ? dx : dy;
	if (dp == 0) {
		image.set(begin->x, begin->y, p1.color);
		return;
	}

	float step = 1.0 / dp;
	for(size_t i = 0; i < dp; i++) {
		int x = begin->x * (1 - i * step) + (i * step) * end->x;
		int y = begin->y * (1 - i * step) + (i * step) * end->y;
		image.set(x, y, p1.color);
	}
}

int main(int argc, char *argv[]) {
	TGAImage image {500, 500, TGAImage::RGB};

	Point p1 {100, 150, red};
	Point p2 {300, 250, red};
	drawLineSegment(image, p1, p2);
	
	Point p3 {400, 200, white};
	Point p4 {200, 100, white};
	drawLineSegment(image, p3, p4);

	Point p5 {499, 499, green};
	Point p6 {499, 499, green};
	drawLineSegment(image, p5, p6);


	image.flip_vertically();
	image.write_tga_file("result.tga");
}