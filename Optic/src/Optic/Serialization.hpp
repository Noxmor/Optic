#pragma once

#include <string>
#include <fstream>

#include "Optic/Image.hpp"

namespace Optic {

	bool LoadImage(Image& img, const std::string& filepath)
	{
		std::ifstream file(filepath, std::ios::binary);
		if (!file.is_open())
		{
			file.close();
			return false;
		}

		const std::string fileExtension = filepath.substr(filepath.find_last_of(".") + 1);
		const ImageFormat format = StringToImageFormat(fileExtension);

		switch (format)
		{
			case ImageFormat::PPM:
			{
				std::string version;
				std::string maxRGB;

				file >> version >> img.Width >> img.Height >> maxRGB;

				const float max = std::stoi(maxRGB);
				img.Channels = 3;
				img.Data = new float[img.Width * img.Height * img.Channels];

				if (version == "P3")
				{
					std::string temp;
					for (size_t i = 0; i < img.Width * img.Height * img.Channels; i++)
					{
						file >> temp;
						img.Data[i] = std::stoi(temp) / max;
					}

					file.close();
					return true;
				}

				if (version == "P6")
				{
					char temp = 0;
					file.read(&temp, sizeof(char));
					for (size_t i = 0; i < img.Width * img.Height * img.Channels; i++)
					{
						file.read(&temp, sizeof(char));
						img.Data[i] = uint8_t(temp) / max;
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

	bool SaveImageAsPPM(const Image& img, const std::string& filepath, const bool binary)
	{
		if (img.Channels != 3)
			return false;
		
		std::ofstream file(filepath, std::ios::binary);
		if (!file.is_open())
		{
			file.close();
			return false;
		}

		if (binary)
		{
			file << "P6\n";
			file << std::to_string(img.Width) + " " + std::to_string(img.Height) + "\n";
			file << "255\r";

			for (size_t i = 0; i < img.Width * img.Height * img.Channels; i++)
			{
				file << uint8_t(img.Data[i] * 255.0f);
			}

			file.close();
			return true;
		}

		file << "P3\n";
		file << std::to_string(img.Width) + " " + std::to_string(img.Height) + "\n";
		file << "255\n";

		for (size_t i = 0; i < img.Width * img.Height * img.Channels; i++)
		{
			file << std::to_string(img.Data[i] * 255.0f);

			if ((i + 1) % 3 == 0)
				file << '\n';
			else
				file << ' ';
		}

		file.close();
		return true;
	}

}