#include <Optic.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	Optic::Image img;
	if (!Optic::LoadImage(img, "img/star_field.ascii.ppm"))
	{
		std::cout << "Error while reading image!\n";
		return 1;
	}

	Optic::GrayScaleAverage(img);
	Optic::ThresholdFilter(img, 0.5f);

	Optic::SaveImage(img, "img/test.ppm");

	return 0;
}