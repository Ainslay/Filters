#include "Filter.h"

double Filter::brightness = 0.0;
double Filter::red_filter = 0.0;
double Filter::green_filter = 0.0;
double Filter::blue_filter = 0.0;
double Filter::gamma = 1.0;

Filter::Filter()
	: mask({1,1,1,1,1,1,1,1,1})
{ }

Filter::Filter(std::vector<double> mask)
	: mask(mask)
{ }

void Filter::Apply(Picture& picture)
{
	ChangeRedFilter(picture);
	ChangeGreenFilter(picture);
	ChangeBlueFilter(picture);
}

void Filter::ChangeRedChannel(const int& value)
{
	if (red_filter >= 0 && red_filter <= 255)
		red_filter += value;
	if (red_filter < 0) red_filter = 0;
	if (red_filter > 255) red_filter = 255;
}

void Filter::ChangeGreenChannel(const int& value)
{
	if (green_filter >= 0 && green_filter <= 255)
		green_filter += value;
	if (green_filter < 0) green_filter = 0;
	if (green_filter > 255) green_filter = 255;
}

void Filter::ChangeBlueChannel(const int& value)
{
	if (blue_filter >= 0 && blue_filter <= 255)
		blue_filter += value;
	if (blue_filter < 0) blue_filter = 0;
	if (blue_filter > 255) blue_filter = 255;
}

void Filter::ChangeBrightness(const double& value)
{
	if (brightness >= -1.0 && brightness <= 1.0)
		brightness += value;
	if (brightness < -1.0) brightness = -1.0;
	if (brightness > 1.0) brightness = 1.0;
}

void Filter::ChangeGamma(const double& value)
{
	if (gamma >= 0.0 && gamma <= 1.0)
		gamma += value;
	if (gamma < 0.0) gamma = 0.0;
	if (gamma > 1.0) gamma = 1.0;
}

void Filter::ClearFilters(Picture& picture)
{
	auto freshPicture = Picture("res/zd3.txt");

	for (int x = 0; x < freshPicture.resolution.width; x++)
	{
		for (int y = 0; y < freshPicture.resolution.height; y++)
		{
			picture.pointsColors[x][y].red = freshPicture.pointsColors[x][y].red;
			picture.pointsColors[x][y].green = freshPicture.pointsColors[x][y].green;
			picture.pointsColors[x][y].blue = freshPicture.pointsColors[x][y].blue;
		}
	}

	brightness = 0;
	red_filter = 0;
	green_filter = 0;
	blue_filter = 0;
	gamma = 1.0;
}

void Filter::ChangeRedFilter(Picture& picture)
{
	double maskSum = 0;
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		maskSum += mask[i];
	}

	for (int x = 1; x < picture.resolution.width - 1; x++)
	{
		for (int y = 1; y < picture.resolution.height - 1; y++)
		{
			sum = mask[0] * picture.pointsColors[x - 1][y - 1].red + mask[1] * picture.pointsColors[x][y - 1].red + mask[2] * picture.pointsColors[x + 1][y - 1].red +
				mask[3] * picture.pointsColors[x - 1][y].red + mask[4] * picture.pointsColors[x][y].red + mask[5] * picture.pointsColors[x + 1][y].red +
				mask[6] * picture.pointsColors[x - 1][y + 1].red + mask[7] * picture.pointsColors[x][y + 1].red + mask[8] * picture.pointsColors[x + 1][y + 1].red;

			if (maskSum == 0)
			{
				picture.pointsColors[x][y].red = abs(sum);
			}
			else
			{
				picture.pointsColors[x][y].red = abs(sum / maskSum);
			}
		}
	}
}

void Filter::ChangeGreenFilter(Picture& picture)
{
	double maskSum = 0;
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		maskSum += mask[i];
	}

	for (int x = 1; x < picture.resolution.width - 1; x++)
	{
		for (int y = 1; y < picture.resolution.height - 1; y++)
		{
			sum = mask[0] * picture.pointsColors[x - 1][y - 1].green + mask[1] * picture.pointsColors[x][y - 1].green + mask[2] * picture.pointsColors[x + 1][y - 1].green +
				mask[3] * picture.pointsColors[x - 1][y].green + mask[4] * picture.pointsColors[x][y].green + mask[5] * picture.pointsColors[x + 1][y].green +
				mask[6] * picture.pointsColors[x - 1][y + 1].green + mask[7] * picture.pointsColors[x][y + 1].green + mask[8] * picture.pointsColors[x + 1][y + 1].green;

			if (maskSum == 0)
			{
				picture.pointsColors[x][y].green = abs(sum);
			}
			else
			{
				picture.pointsColors[x][y].green = abs(sum / maskSum);
			}
		}
	}
}

void Filter::ChangeBlueFilter(Picture& picture)
{
	double maskSum = 0;
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		maskSum += mask[i];
	}

	for (int x = 1; x < picture.resolution.width - 1; x++)
	{
		for (int y = 1; y < picture.resolution.height - 1; y++)
		{
			sum = mask[0] * picture.pointsColors[x - 1][y - 1].blue + mask[1] * picture.pointsColors[x][y - 1].blue + mask[2] * picture.pointsColors[x + 1][y - 1].blue +
				mask[3] * picture.pointsColors[x - 1][y].blue + mask[4] * picture.pointsColors[x][y].blue + mask[5] * picture.pointsColors[x + 1][y].blue +
				mask[6] * picture.pointsColors[x - 1][y + 1].blue + mask[7] * picture.pointsColors[x][y + 1].blue + mask[8] * picture.pointsColors[x + 1][y + 1].blue;

			if (maskSum == 0)
			{
				picture.pointsColors[x][y].blue = abs(sum);
			}
			else
			{
				picture.pointsColors[x][y].blue = abs(sum / maskSum);
			}
		}
	}
}