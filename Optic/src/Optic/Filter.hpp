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

	void ThresholdFilter(Image& img, const float threshold)
	{
		for (size_t i = 0; i < img.Width * img.Height * img.Channels; i++)
		{
			img.Data[i] = img.Data[i] >= threshold ? 1.0f : 0.0f;
		}
	}

	void FlipHorizontal(Image& img)
	{
		float* start = &img.Data[0];
		float* end = &img.Data[img.Width * img.Channels - img.Channels];

		for (size_t y = 0; y < img.Height; y++)
		{
			for (size_t x = 0; x < img.Width / 2; x++)
			{
				const float tempRed = *start;
				const float tempGreen = *(start + 1);
				const float tempBlue = *(start + 2);

				*start = *end;
				*(start + 1) = *(end + 1);
				*(start + 2) = *(end + 2);


				*end = tempRed;
				*(end + 1) = tempGreen;
				*(end + 2) = tempBlue;

				start += 3;
				end -= 3;
			}

			start -= (img.Width / 2) * img.Channels;
			start += img.Width * img.Channels;

			end += (img.Width / 2) * img.Channels;
			end += img.Width * img.Channels;
		}
	}

	void FlipVertical(Image& img)
	{
		float* start = &img.Data[0];
		float* end = &img.Data[img.Width * img.Height * img.Channels - img.Width * img.Channels];

		for (size_t y = 0; y < img.Height / 2; y++)
		{
			for (size_t x = 0; x < img.Width; x++)
			{
				const float tempRed = *start;
				const float tempGreen = *(start + 1);
				const float tempBlue = *(start + 2);

				*start = *end;
				*(start + 1) = *(end + 1);
				*(start + 2) = *(end + 2);


				*end = tempRed;
				*(end + 1) = tempGreen;
				*(end + 2) = tempBlue;

				start += 3;
				end += 3;
			}

			end -= img.Width * img.Channels;
			end -= img.Width * img.Channels;
		}
	}

}