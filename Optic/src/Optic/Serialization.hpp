#pragma once

#include <string>
#include <fstream>

#include "Optic/Image.hpp"

namespace Optic {

	bool LoadImage(Image& img, const std::string& filepath)
	{
		std::ifstream file(filepath);
		if (!file.is_open())
		{
			file.close();
			return false;
		}

		const std::string fileExtension = filepath.substr(filepath.find_last_of(".") + 1);
		img.Format = StringToImageFormat(fileExtension);

		switch (img.Format)
		{
			case ImageFormat::PPM:
			{
				std::string version;
				std::string maxRGB;

				file >> version;
				if (file.get() == '#')
					while (file.get() != '\n');

				file >> img.Width >> img.Height >> maxRGB;

				if (version == "P2")
				{
					img.Channels = 1;
					img.Data = new float[img.Width * img.Height];

					std::string temp;
					for (size_t i = 0; i < img.Width * img.Height; i++)
					{
						file >> temp;
						img.Data[i] = std::stoi(temp) / 255.0f;
					}

					file.close();
					return true;
				}

				if (version == "P3")
				{
					img.Channels = 3;
					img.Data = new float[img.Width * img.Height * img.Channels];

					std::string temp;
					for (size_t i = 0; i < img.Width * img.Height * img.Channels; i++)
					{
						file >> temp;
						img.Data[i] = std::stoi(temp) / 255.0f;
					}

					file.close();
					return true;
				}
				
				return false;
			}
		}

		file.close();
		return false;
	}

	bool SaveImage(const Image& img, const std::string& filepath)
	{
		switch (img.Format)
		{
			case ImageFormat::PPM:
			{
				std::ofstream file(filepath);
				if (!file.is_open())
				{
					file.close();
					return false;
				}

				file << "P3\n";
				file << std::to_string(img.Width) + " " + std::to_string(img.Height) + "\n";
				file << "255\n";

				for (size_t i = 0; i < img.Width * img.Height * img.Channels; i++)
				{
					file << std::to_string(img.Data[i] * 255.0f);
					
					if ((i + 1) % 3 == 0)
						file << "\n";
					else
						file << " ";
				}

				file.close();
				return true;
			}
		}

		return false;
	}

}