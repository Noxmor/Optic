#include <Optic.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	Optic::Image img;
	Optic::LoadImage(img, "img/image.ppm");
	Optic::SaveImageAsPPM(img, "img/test.ppm", true);

	return 0;
}