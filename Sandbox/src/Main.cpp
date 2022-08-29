#include <Optic.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	Optic::Image img;
	Optic::LoadImage(img, "img/blackbuck.ascii.ppm");
	Optic::FlipHorizontal(img);
	Optic::FlipVertical(img);
	Optic::SaveImage(img, "img/test.ppm");
	return 0;
}