#pragma once

#include <algorithm>

#include "Optic/Image.hpp"

namespace Optic {

	void GrayScaleAverage(Image& img)
	{
		if (img.Channels < 3)
			return;

		for (size_t i = 0; i < img.Width * img.Height * img.Channels; i += img.Channels)
		{
			const float grayScaleAvg = (img.Data[i] + img.Data[i + 1] + img.Data[i + 2]) / 3.0f;
			img.Data[i] = grayScaleAvg;
			img.Data[i + 1] = grayScaleAvg;
			img.Data[i + 2] = grayScaleAvg;
		}
	}

	void GrayScaleLuminance(Image& img)
	{
		if (img.Channels < 3)
			return;

		for (size_t i = 0; i < img.Width * img.Height * img.Channels; i += img.Channels)
		{
			const float grayScaleAvg = (0.2126f * img.Data[i] + 0.7152f * img.Data[i + 1] + 0.0722f * img.Data[i + 2]) / 3.0f;
			img.Data[i] = grayScaleAvg;
			img.Data[i + 1] = grayScaleAvg;
			img.Data[i + 2] = grayScaleAvg;
		}
	}

	void RedFilter(Image& img, const float percentage)
	{
		if (img.Channels < 1)
			return;
		
		for (size_t i = 0; i < img.Width * img.Height * img.Channels; i += img.Channels)
		{
			img.Data[i] = std::min(img.Data[i] * percentage, 255.0f);
		}
	}

	void GreenFilter(Image& img, const float percentage)
	{
		if (img.Channels < 2)
			return;
		
		for (size_t i = 0; i < img.Width * img.Height * img.Channels; i += img.Channels)
		{
			img.Data[i + 1] = std::min(img.Data[i + 1] * percentage, 255.0f);
		}
	}

	void BlueFilter(Image& img, const float percentage)
	{
		if (img.Channels < 3)
			return;
		
		for (size_t i = 0; i < img.Width * img.Height * img.Channels; i += img.Channels)
		{
			img.Data[i + 2] = std::min(img.Data[i + 2] * percentage, 255.0f);
		}
	}

}