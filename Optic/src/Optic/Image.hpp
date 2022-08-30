#pragma once

#include <unordered_map>

namespace Optic {

	enum class ImageFormat
	{
		None = 0,
		PPM,
		PNG,
		JPEG
	};

	struct Image
	{
		size_t Width = 0;
		size_t Height = 0;

		uint8_t Channels = 0;
		float* Data = nullptr;
	};

	static ImageFormat StringToImageFormat(const std::string& str)
	{
		static std::unordered_map<std::string, ImageFormat> map;
		map["ppm"] = ImageFormat::PPM;
		map["png"] = ImageFormat::PNG;
		map["jpeg"] = ImageFormat::JPEG;

		if (map.find(str) != map.end())
			return map[str];

		return ImageFormat::None;
	}

}