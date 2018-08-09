#include <iostream>
#include "TGAImage/tgaimage.h"


struct Color {
	TGAColor black = TGAColor(0, 0, 0, 1);
	TGAColor white = TGAColor(1, 1, 1, 1);
	TGAColor red = TGAColor(1, 1, 1, 1);
};


int main(int argc, char *argv[]) {
	auto image = TGAImage(300, 300, 1);
	std::cout << "Hello Easy C++ project!" << std::endl;
	std::cout << image.get_height() << ", " << image.get_width() << std::endl;
}