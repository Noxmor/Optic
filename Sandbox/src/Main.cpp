#include <Optic.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	Optic::Image img0;
	Optic::Image img1;
	Optic::LoadImage(img0, "img/image.ppm");
	Optic::LoadImage(img1, "img/image.ppm");
	Optic::Image result = Optic::DiffMap(img0, img1);
	Optic::SaveImageAsPPM(result, "img/test.ppm", true);

	return 0;
}