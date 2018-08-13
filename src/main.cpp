#include <iostream>
#include <algorithm>
#include <utility>

#include "TGAImage/tgaimage.h"
#include "Model/model.h"

const TGAColor black {0, 0, 0, 255};
const TGAColor white {255, 255, 255, 255};
const TGAColor red   {255, 0, 0, 255};
const TGAColor green {0, 255, 0, 255};

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

int main(int argc, char *argv[]) {
	TGAImage canvas {500, 500, TGAImage::RGB};
	int width = canvas.get_width();
	int height = canvas.get_height();
	
	auto model = Model("../obj/african_head.obj");

	for (auto i = 0; i < model.nfaces(); i++) {
		std::vector<int> face = model.face(i);

		for (auto j = 0; j < face.size(); j++) {
			auto v1 = model.vert(face[j]);
			auto v2 = model.vert(face[(j + 1) % face.size()]);

			int x1 = (v1.x + 1.0) * width / 2.0;
			int y1 = (v1.y + 1.0) * height / 2.0;
			int x2 = (v2.x + 1.0) * width / 2.0;
			int y2 = (v2.y + 1.0) * height / 2.0;
			line(x1, y1, x2, y2, white, canvas);
		}
	}

	canvas.flip_vertically();
	canvas.write_tga_file("result.tga");
}