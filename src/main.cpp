#include <iostream>
#include "TGAImage/tgaimage.h"

const TGAColor black = TGAColor(0, 0, 0, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

int main(int argc, char *argv[]) {
	auto image = TGAImage(300, 300, TGAImage::RGB);
	
	size_t size = 100;
	for(size_t y = 0; y < size; y++)
		for(size_t x = 0; x < size; x++) {
			image.set(x, y, red);
		}
	
	image.write_tga_file("result.tga");
}